#pragma once

#include "utils.h"

namespace containers
{
    template<typename T, std::size_t S>
    struct array
    {
    private:

        T data[S];

    public:
        array() = default;

        T& operator[](const std::size_t& ix)
        {
            check_bounds(ix, S);
            return data[ix];
        }

        const T& operator[](const std::size_t& ix) const
        {
            check_bounds(ix, S);
            return data[ix];
        }
    };
}