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

#include <cmath>
#include <limits>
#include <random>
#include <utility>
#include <algorithm>
#include <vector>
#include <valarray>
#include <unordered_map>

#include "kmeans.hpp"

/**
 * TODO: use xtensor for linear algebra operations
 */

using namespace utils;

namespace ml {

matrix<double> kmeans::operator()(int k, double epsilon, const matrix<double>& data)
{
    auto error = std::numeric_limits<double>::max();
    auto rand_centroids_indx = rand_int(0, data.size() - 1, k);

    auto prototypes = matrix<double>{};
    for (const auto& indx : rand_centroids_indx) {
        prototypes.push_back(data[indx]);
    }

    auto old_centroids = matrix<double>{};
    auto clusters = std::unordered_map<int, std::vector<int>>{};

    while (error > epsilon) {
        auto dict = std::unordered_map<int, std::vector<int>>{};
        for (const auto& val : Generator(0, k)) {
            dict.emplace(val, std::vector<int>{});
        }

        /**
         * Calculate distance from each centroid to the particular
         * data point.
         * 
         * TODO: refactor code (CODE MUST BE SELF_DOCUMENTED)
         *       PERFORMANCE MEASUREMENTS!!!
         */
        for (const auto& record_indx : Generator(0, data.size())) {
            auto dist_vec = std::valarray<double>(k);
            for (const auto& centroid_indx : Generator(0, k)) {
                dist_vec[centroid_indx] = euclidian_distance(
                                            data[record_indx],
                                            prototypes[centroid_indx]
                                        );
            }

            auto min_dist = dist_vec.min();
            auto category = 
                std::find(begin(dist_vec), end(dist_vec), min_dist) - begin(dist_vec);
            dict[category].push_back(record_indx);
        }

        /**
         * Calculate new centroids and find an error.
         * 
         * TODO: refactor code (CODE MUST BE SELF_DOCUMENTED)
         *       PERFORMANCE MEASUREMENTS!!!
         */
        old_centroids = prototypes;
        for (const auto& category : Generator(0, k)) {
            auto sum = std::valarray<double>(0.0, data[0].size());
            for (const auto& record_indx : dict[category]) {
                sum += data[record_indx];
            }

            std::valarray<double> new_centroid = sum / static_cast<double>(dict[category].size());
            prototypes[category] = new_centroid;
        }
        error = euclidian_distance(prototypes, old_centroids);
        clusters = dict;
    }

    return prototypes;
};

std::valarray<int> kmeans::rand_int(int low, int high, int size)
{
    std::random_device seed;
    std::mt19937_64 rand_number_gen(seed());
    std::uniform_int_distribution<> dist{low, high};

    auto container = std::valarray<int>(size);
    std::generate(begin(container), end(container),
                    [&]() { return dist(rand_number_gen); });
    return container;
}

} // ml
