#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <permutations.hpp>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

static uint64_t concatenate(uint64_t a, uint16_t b) {
    static const uint16_t factors[] = {1, 10, 100, 1000, 10000};

    // Find the number of digits in b using branchless math
    uint8_t bDigits = 
        (b >= 10000) ? 5 :
        (b >= 1000) ? 4 :
        (b >= 100) ? 3 :
        (b >= 10) ? 2 : 1;

    return a * factors[bDigits] + b;
}

static bool isValidEquation(
        uint64_t result, 
        const std::vector<uint16_t> &numbers, 
        std::unordered_map<uint8_t, std::vector<std::string>> &permutationsCache,
        bool part2) {

    std::vector<std::string> permutations = getPermutationsForR(permutationsCache, numbers.size(), part2);

    for (const auto &permutation : permutations) {
        uint64_t computedResult = numbers[0];
        for (uint8_t i = 1; i < numbers.size(); i++) {
            if (permutation[i] == '+') {
                computedResult += numbers[i];
            } else if (permutation[i] == '*') {
                computedResult *= numbers[i];
            } else {
                computedResult = concatenate(computedResult, numbers[i]);
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
    
    std::unordered_map<uint8_t, std::vector<std::string>> permutationsCachePart1;
    permutationsCachePart1.reserve(12);

    std::unordered_map<uint8_t, std::vector<std::string>> permutationsCachePart2;
    permutationsCachePart2.reserve(12);

    uint64_t part1Sum = 0;
    uint64_t part2Sum = 0;

    std::string buffer;
    while (std::getline(file, buffer)) {
        size_t delimiter = buffer.find(':');

        uint64_t result = std::stoull(buffer.substr(0, delimiter));

        std::istringstream iss(buffer.substr(delimiter + 1));
        std::vector<uint16_t> numbers;
        numbers.reserve(12);

        uint16_t number;
        while (iss >> number) {
            numbers.push_back(number);
        }

        if (isValidEquation(result, numbers, permutationsCachePart1, false)) {
            part1Sum += result;
        }

        if (isValidEquation(result, numbers, permutationsCachePart2, true)) {
            part2Sum += result;
        }
        
    }

    std::cout << "Part 1: "<< part1Sum << '\n';
    std::cout << "Part 2: "<< part2Sum << '\n';
     
    return EXIT_SUCCESS;
}
