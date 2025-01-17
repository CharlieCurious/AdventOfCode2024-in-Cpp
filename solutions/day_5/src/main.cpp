#include <algorithm>
#include <array>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

static constexpr uint8_t NUM_PAGES = 100;
static constexpr uint8_t NUM_UPDATE_LINES = 208;

static bool isUpdateOrdered(const std::vector<uint8_t> &pages, const std::array<std::array<bool, NUM_PAGES>, NUM_PAGES> &rules);
static std::vector<uint8_t> parseRule(char *buffer);
static void processUpdate(
        std::vector<uint8_t> &pages, 
        std::array<std::array<bool, NUM_PAGES>, NUM_PAGES> &rules, 
        uint32_t &part1, 
        uint32_t &part2);

int main() {
    std::ifstream file("input_files/day_5.txt");
    if(!file.is_open()) {
        std::cerr << "Failed to open input file" << '\n';
        return EXIT_FAILURE;
    }

    // 100x100 for all realations between every 2 digit numbers;
    std::array<std::array<bool, NUM_PAGES>, NUM_PAGES> rules = {};

    // There are 208 update lines in my input
    std::array<std::vector<uint8_t>, NUM_UPDATE_LINES> updates = {};

    uint32_t part1 = 0;
    uint32_t part2 = 0;

    std::string buffer;
    buffer.reserve(70);
    bool doubleNewLineReached = false;
    uint8_t updateIndex = 0;
    while (std::getline(file, buffer)) {
        if (doubleNewLineReached) {
            updates[updateIndex] = parseRule(buffer.data()); 

            processUpdate(updates[updateIndex], rules, part1, part2);
            
            updateIndex++;
            continue;
        }

        uint8_t from, to;
        if (sscanf(buffer.data(), "%hhu|%hhu", &from, &to) == 2) {
            rules[from][to] = true;
            continue;
        }
        if (buffer.empty()) {
            doubleNewLineReached = true;
            continue;
        }
    }

    std::cout << "Part 1: " << part1 << '\n';
    std::cout << "Part 2: " << part2 << '\n';

    return EXIT_SUCCESS;
}

static std::vector<uint8_t> parseRule(char *buffer) {
    char *tokenPtr;
    char *number = strtok_r(buffer, ",", &tokenPtr);

    std::vector<uint8_t> pages;
    pages.reserve(23);

    while (number) {
        pages.push_back(std::stoi(number));
        number = strtok_r(NULL, ",", &tokenPtr);
    }

    return pages;
}

bool isUpdateOrdered(const std::vector<uint8_t> &pages, const std::array<std::array<bool, NUM_PAGES>, NUM_PAGES> &rules) {
    for (uint8_t i = 0; i < pages.size()-1; i++) {
        if (rules[pages[i+1]][pages[i]]) {
            return false;
        }
    }
    return true;
}

static void processUpdate(
        std::vector<uint8_t> &pages, 
        std::array<std::array<bool, NUM_PAGES>, NUM_PAGES> &rules,
        uint32_t &part1, 
        uint32_t &part2) {

    if (isUpdateOrdered(pages, rules)) {
        part1 += pages[pages.size() / 2];
    } else {
        std::sort(pages.begin(), pages.end(), [&rules](uint8_t a, uint8_t b) { return rules[a][b]; });
        part2 += pages[pages.size() / 2];
    }
}
