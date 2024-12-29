#pragma once

#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

std::vector<std::string> getPermutationsForR(std::unordered_map<uint8_t, std::vector<std::string>> &permutationsCache, uint8_t r, bool par2);

