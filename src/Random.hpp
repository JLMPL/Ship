#pragma once
#include <random>

namespace rando
{
    extern std::mt19937 randomEngine;

    template <typename T = float>
    static T inRange(T min, T max)
    {
        std::uniform_real_distribution<T> range(min, max);
        return range(randomEngine);
    }

    template <typename T = int>
    static T inRangei(T min, T max)
    {
        std::uniform_int_distribution<T> range(min, max);
        return range(randomEngine);
    }
}