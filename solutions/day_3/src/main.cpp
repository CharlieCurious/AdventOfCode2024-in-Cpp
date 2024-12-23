#include <cstdlib>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <sstream>

int main() {
    std::ifstream file("input_files/day_3.txt");
    if (!file.is_open()) {
        std::cerr << "Could not open input file." << std::endl; 
        return EXIT_FAILURE;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();

    std::string content = buffer.str();

    std::regex patterns(R"(mul\(\d+,\d+\)|don't\(\)|do\(\))");
    std::smatch match;

    uint32_t part1Sum = 0;
    uint32_t part2Sum = 0;
    bool isDoBlock = true;
    auto searchStart = content.cbegin();
    while (std::regex_search(searchStart, content.cend(), match, patterns)) {
        std::string matchedString = match.str();
        
        if (matchedString == "do()") {
            isDoBlock = true;
            searchStart = match.suffix().first;
            continue;
        } 
        if (matchedString == "don't()") {
            isDoBlock = false;
            searchStart = match.suffix().first;
            continue;
        }

        size_t comma = matchedString.find(',');
        uint16_t firstNumber = std::stoi(matchedString.substr(4, comma - 4));
        uint16_t secondNumber = std::stoi(matchedString.substr(comma + 1, matchedString.length() - comma - 2));

        part1Sum += firstNumber * secondNumber;
        if (isDoBlock) {
            part2Sum += firstNumber * secondNumber;
        }

        searchStart = match.suffix().first;
    }

    std::cout << "Part 1: " << part1Sum << "\n";
    std::cout << "Part 2: " << part2Sum << "\n";

    return EXIT_SUCCESS;
}
