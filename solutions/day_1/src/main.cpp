#include <algorithm>
#include <array>
#include <chrono>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>

#define INPUT_LINE_COUNT 1000

int main() {

    auto startTime = std::chrono::high_resolution_clock::now();

    const std::string fileName = "input_files/day_1.txt"; 
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        return EXIT_FAILURE;
    }

    std::array<int32_t, INPUT_LINE_COUNT> leftCol;
    std::array<int32_t, INPUT_LINE_COUNT> rightCol;
    std::unordered_map<int32_t, int32_t> multipliers;

    std::string line;
    uint32_t lineCount = 0;
    while (getline(file, line) && lineCount < INPUT_LINE_COUNT) {
        std::istringstream iss(line);
        int32_t leftNum, rightNum;
        if (iss >> leftNum >> rightNum) {
            leftCol[lineCount] = leftNum;
            rightCol[lineCount] = (rightNum);

            multipliers[rightNum]++;
            lineCount++;
        } else {
            std::cerr << "Invalid line format: " << line << std::endl;
            return EXIT_FAILURE;
        }

    }

    std::sort(leftCol.begin(), leftCol.end());
    std:: sort(rightCol.begin(), rightCol.end());

    int32_t part1Sum = 0;
    int32_t part2Sum = 0;
    for (uint32_t i = 0; i < lineCount; i++) {
        int32_t leftNum = leftCol[i];
        int32_t rightNum = rightCol[i];
        part1Sum += abs(leftNum - rightNum);
        part2Sum += multipliers[leftNum] == 0 ? 0 : leftNum * multipliers[leftNum];
    }

    auto endTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsedSeconds = endTime - startTime;

    std::cout << "Part 1: " << part1Sum << "\n";
    std::cout << "Part 2: " << part2Sum << "\n";

    std::cout << "Execution time: " << elapsedSeconds.count() << "seconds\n";

    return EXIT_SUCCESS;
}
