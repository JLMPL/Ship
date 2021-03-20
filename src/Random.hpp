#pragma once
#include <random>

namespace rng
{
    extern std::mt19937 randomEngine;

    void randomizeSeed();

    // template <typename T = float>
    static float inRange(float min, float max)
    {
        std::uniform_real_distribution<float> range(min, max);
        return range(randomEngine);
    }

    template <typename T = int>
    static T inRangei(T min, T max)
    {
        std::uniform_int_distribution<T> range(min, max);
        return range(randomEngine);
    }
}