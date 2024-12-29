#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <permutations.hpp>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

static bool isValidEquation(
        uint64_t result, 
        const std::vector<uint16_t> &numbers, 
        std::unordered_map<uint8_t, std::vector<std::string>> &permutationsCache) {

    std::vector<std::string> permutations = getPermutationsForR(permutationsCache, numbers.size());

    for (const auto &permutation : permutations) {
        uint64_t computedResult = numbers[0];
        for (uint8_t i = 1; i < numbers.size(); i++) {
            if (permutation[i] == '+') {
                computedResult += numbers[i];
            } else {
                computedResult *= numbers[i];
            }
            
            if (computedResult > result) {
                break;
            }
        }

        if (computedResult == result) {
            return true;
        }
    }

    return false;
}

int main() {
    std::ifstream file("input_files/day_7.txt");
    if (!file.is_open()) {
        std::cerr << "Failed to open input file." << std::endl;
        return EXIT_FAILURE; 
    }
    
    std::unordered_map<uint8_t, std::vector<std::string>> permutationsCache;
    permutationsCache.reserve(10);

    uint64_t part1Sum = 0;

    std::string buffer;
    while (std::getline(file, buffer)) {
        size_t delimiter = buffer.find(':');

        uint64_t result = std::stoull(buffer.substr(0, delimiter));

        std::istringstream iss(buffer.substr(delimiter + 1));
        std::vector<uint16_t> numbers;
        numbers.reserve(10);

        uint16_t number;
        while (iss >> number) {
            numbers.push_back(number);
        }
        if (isValidEquation(result, numbers, permutationsCache)) {
            part1Sum += result;
        }
        
    }

    std::cout << "Part 1: "<< part1Sum << '\n';
     
    return EXIT_SUCCESS;
}
