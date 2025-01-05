#pragma once

#include <array>
#include <cstdint>
#include <string>
#include <vector>

constexpr uint8_t MAX_PERMUTATION_R = 13;

std::vector<std::string> getPermutationsForR(
        std::array<std::vector<std::string>, MAX_PERMUTATION_R> &permutationsCache, 
        uint8_t r, 
        bool par2);

