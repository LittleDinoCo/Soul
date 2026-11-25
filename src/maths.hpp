#pragma once
#include <random>

inline bool rollChance(float probability) {
    if (probability <= 0.f) return false;
    if (probability >= 1.f) return true;

    static std::mt19937 rng{std::random_device{}()};
    static std::uniform_real_distribution<float> dist(0.f, 1.f);
    return dist(rng) < probability;
}
