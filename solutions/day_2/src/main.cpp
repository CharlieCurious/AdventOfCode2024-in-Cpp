#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

#include<report.hpp>

#define INPUT_LINE_COUNT 1000

int main() {

    const std::string fileName = "input_files/day_2.txt";
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Could not open input file." << std::endl;
    }

    std::string line; 
    uint16_t lineIndex = 0;
    uint16_t part1SafeReportsCount = 0;
    while (getline(file, line) && lineIndex < INPUT_LINE_COUNT) {
        std::vector<int32_t> lineNumbers;
        lineNumbers.reserve(5);

        std::istringstream lineStream(line);
        int32_t number;
        while (lineStream >> number) {
            lineNumbers.push_back(number);
        }

        if (isLineSafe(lineNumbers)) {
            part1SafeReportsCount++;
        }

        lineIndex++;
    }

    std::cout << "Part 1: " << part1SafeReportsCount << "\n";
     
    return EXIT_SUCCESS;
}

