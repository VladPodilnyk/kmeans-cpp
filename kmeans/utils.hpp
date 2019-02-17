/*
MIT License

Copyright (c) 2019 Vladyslav

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef __UTILS_HPP__
#define __UTILS_HPP__

#include <vector>
#include <valarray>
#include <string>
#include <fstream>
#include <sstream>
#include <iterator>

namespace utils {

template <typename T>
using matrix = std::vector<std::valarray<T>>;

class Generator {
    public:
        Generator(int iterator) : iterator_{iterator} {};
        Generator(int begin, int end)
            : begin_{begin}, end_{end}, iterator_{begin} {};
        ~Generator() = default;

        auto operator==(const Generator& gen) const { 
            return iterator_ == gen.iterator_;
        };

        auto operator!=(const Generator& gen) const {
            return !(*this == gen);
        };

        auto& operator*() const { return iterator_; };
        auto& operator++() {
            ++iterator_;
            return *this;
        };

        auto begin() const { return Generator(begin_); };
        auto end() const { return Generator(end_); };

    private:
        int iterator_;
        int begin_;
        int end_;
};

class Parser
{
    public:
        static matrix<double> getDataFromFile(std::string filename)
        {
            std::ifstream inputData(filename);
            std::istringstream tokenStream(filename);

            auto split = [](auto line) {
                std::istringstream iss(line);
                std::vector<std::string> tokens = {std::istream_iterator<std::string> {iss},
                                                    std::istream_iterator<std::string> {}};
                return tokens;
            };

            auto dataset = matrix<double>();
            auto line = std::string{};

            if (inputData.is_open()) {
                while (std::getline(inputData, line)) {
                    auto tokens = split(line);
                    auto processed_data = std::valarray<double>(tokens.size());
                    for (const auto& val : Generator(0, tokens.size())) {
                        processed_data[val] = std::stod(tokens[val]);
                    }
                    dataset.push_back(processed_data);
                }
            } else {
                throw std::ios_base::failure("No file with given name.");
            }

            inputData.close();
            return dataset;
        };
};

} // utils

#endif // __UTILS_HPP__