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

#ifndef __KMEANS_CPP__
#define __KMEANS_CPP__

#include "utils.hpp"

#include <iostream>
namespace ml {

class kmeans {
    public:
        kmeans() = default;
        ~kmeans() = default;
        utils::matrix<double> operator()(int k, double epsilon, 
                                        const utils::matrix<double>& data);
    private:
        // functions;
        template <typename Container>
        auto euclidian_distance(const Container& a, const Container& b)
        {
            auto sum = 0.0;
            for (const auto& indx : utils::Generator(0, a.size())) {
                sum += (a[indx] - b[indx]) * (a[indx] - b[indx]);
            }
            return std::sqrt(sum);
        };

        auto euclidian_distance(const utils::matrix<double>& a, 
                                const utils::matrix<double>& b)
        {
            auto sum = 0.0;
            for (const auto& i : utils::Generator(0, a.size())) {
                for (const auto& j : utils::Generator(0, a[0].size())) {
                    sum += (a[i][j] - b[i][j]) * (a[i][j] - b[i][j]);
                }
            }
            return std::sqrt(sum);
        };

        std::valarray<int> rand_int(int low, int high, int size);

        // data
        size_t n_clusters;
};

} // ml

#endif // __KMEANS_CPP__