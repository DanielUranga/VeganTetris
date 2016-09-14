#pragma once

#include <random>

static size_t getRandomBetweenZeroAndLessThan(size_t max)
{
    static std::random_device r;
    static std::default_random_engine generator(r());
    std::uniform_int_distribution<size_t> distribution(0, max - 1);
    return distribution(generator);
}
