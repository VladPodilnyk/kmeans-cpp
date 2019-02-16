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


#include "xtensor/xarray.hpp"
#include "xtensor/xio.hpp"
#include "xtensor/xrandom.hpp"


#include "kmeans.hpp"

namespace ml {

int kmeans::operator()(int k, double epsilon, utils::matrix<size_t>& data)
{
    auto error = std::numeric_limits<double>::max();
    auto prototypes_indx = xt::random::randint<int>({0, 3});
    //while (error > epsilon) {

    //}
    return 0;
};

auto kmeans::euclidian_distance()
{
    auto sum = 0.0;
    return sum;
}

auto kmeans::rand_int(int low, int high, int size)
{
    return 0;
}

} // ml
