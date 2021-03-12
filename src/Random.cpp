#include "Random.hpp"
#include <ctime>

namespace rng
{
    std::mt19937 randomEngine;

    void randomizeSeed()
    {
        randomEngine.seed(time(NULL));
    }
}