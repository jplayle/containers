#pragma once

#include <utility>

namespace containers
{
    inline void check_bounds(const std::size_t& ix, const std::size_t& r_bound)
    {
        if (ix >= r_bound) throw std::runtime_error("out of bounds");
    }

    template<typename T, typename Y>
    struct pair
    {
        T first;
        Y second;

        pair() :
            first(),
            second()
        {}

        pair(const T& t, const Y& y) :
            first(t),
            second(y)
        {}

        pair(const T&& t, const Y&& y) :
            first(std::move(t)),
            second(std::move(y))
        {}

        pair(const pair&& p) :
            first(std::move(p.first)),
            second(std::move(p.second))
        {}
    };
}

// const bool contains(const T& val) const
// {
//     std::size_t r = size - 1;
//     std::size_t l = 0;

//     while (l <= r)
//     {
//         std::size_t ix = l + ((r - l) / 2);

//         if (_data[ix] == val) return true;
        
//         if (_data[ix] > val) {
//             r = ix - 1;
//         }
//         else {
//             l = ix + 1;
//         }
//     }

//     return false;
// }