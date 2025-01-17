#include <array>
#include <bitset>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <unordered_map>
#include <vector>

constexpr int32_t GRID_SIDE_SZ = 50;

struct Location {
    int8_t x;
    int8_t y;

    Location() : x{0}, y{0} {}

    Location(int8_t x, int8_t y) : x{x}, y{y} {}
};

static inline bool isAnthena(char c) {
    return (c < ':' && c > '/') || (c < '[' && c > '@') || (c < '{' && c > '`');
}

static inline bool isInBounds(Location location) {
    return location.x < GRID_SIDE_SZ && location.x > -1 && location.y < GRID_SIDE_SZ && location.y > -1;
}

static void markAntinodesPart1(std::array<std::bitset<GRID_SIDE_SZ>, GRID_SIDE_SZ> &markedAntinodes, uint16_t &antinodesCount, Location a, Location b) {
    uint32_t dx = b.x - a.x;
    uint32_t dy = b.y - a.y;

    Location a1(b.x + dx, b.y + dy);
    if (isInBounds(a1) && !markedAntinodes[b.x + dx].test(b.y + dy)) {
        markedAntinodes[b.x + dx].set(b.y + dy);
        antinodesCount++;
    }

    Location a2(a.x - dx, a.y - dy);
    if (isInBounds(a2) && !markedAntinodes[a.x - dx].test(a.y - dy)) {
        markedAntinodes[a.x - dx].set(a.y - dy);
        antinodesCount++;
    }
}

static void markAntinodesPart2(std::array<std::bitset<GRID_SIDE_SZ>, GRID_SIDE_SZ> &markedAntinodes, uint16_t &antinodesCount, Location a, Location b) {
    uint32_t dx = b.x - a.x;
    uint32_t dy = b.y - a.y;
    uint8_t i = 0;

    Location a1{};
    while (true) {
        a1.x = b.x + dx * i;
        a1.y = b.y + dy * i;
        if (isInBounds(a1)) {
            if (!markedAntinodes[b.x + dx * i].test(b.y + dy * i)) {
                markedAntinodes[b.x + dx * i].set(b.y + dy * i);
                antinodesCount++;
            }
        } else {
            break;
        }
        i++;
    }

    i = 0;
    Location a2{};
    while (true) {
        a2.x = a.x - dx * i;
        a2.y = a.y - dy * i;
        if (isInBounds(a2)) {
            if (!markedAntinodes[a.x - dx * i].test(a.y - dy * i)) {
                markedAntinodes[a.x - dx * i].set(a.y - dy * i);
                antinodesCount++;
            }
        } else {
            break;
        }
        i++;
    }
}

int main() {

    std::ifstream file ("input_files/day_8.txt");
    if (!file.is_open()) {
        throw std::runtime_error("Could not open input file");
    }

    std::unordered_map<char, std::vector<Location>> charter;

    std::string lineBuffer;
    lineBuffer.reserve(GRID_SIDE_SZ);
    uint8_t lineIndex = 0;
    while(std::getline(file, lineBuffer)) {
        for (uint8_t i = 0; i < lineBuffer.size(); i++) {
            if (isAnthena(lineBuffer[i])) {
                Location location(lineIndex, i);
                charter[lineBuffer[i]].push_back(location);
            }
        }
        lineIndex++;
    }

    std::array<std::bitset<GRID_SIDE_SZ>, GRID_SIDE_SZ> markedAntinodesPart1{};
    std::array<std::bitset<GRID_SIDE_SZ>, GRID_SIDE_SZ> markedAntinodesPart2{};

    uint16_t part1 = 0;
    uint16_t part2 = 0;
    for (auto kvp : charter) {
        for (uint16_t i = 0; i < kvp.second.size()-1; i++) {
            for (uint16_t j = i + 1; j < kvp.second.size(); j++) {
                markAntinodesPart1(markedAntinodesPart1, part1, kvp.second[i], kvp.second[j]);
                markAntinodesPart2(markedAntinodesPart2, part2, kvp.second[i], kvp.second[j]);
            }
        }
    }

    std::cout << "Part 1: " << part1 << '\n';
    std::cout << "Part 2: " << part2 << '\n';

    return EXIT_SUCCESS;
}
