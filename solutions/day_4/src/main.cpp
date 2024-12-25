#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
#include <ostream>
#include <cstdlib>

#include <xmas_finder.hpp>

#define GRID_SIDE_SZ 140

int main() {
    std::ifstream file("input_files/day_4.txt");
    if (!file.is_open()) {
        std::cerr << "Failed to open input file." << std::endl;
        return EXIT_FAILURE; 
    }

    char grid[GRID_SIDE_SZ][GRID_SIDE_SZ];
    uint8_t lineIndex = 0;

    char buffer[GRID_SIDE_SZ + 1];
    while(file.getline(buffer, sizeof(buffer)) && lineIndex < GRID_SIDE_SZ) {
        std::strncpy(grid[lineIndex++], buffer, GRID_SIDE_SZ);
    }

    uint32_t xmasFound = 0;
    for (uint8_t x = 0; x < GRID_SIDE_SZ; x++) {
        for (uint8_t y = 0; y < GRID_SIDE_SZ; y++) {
            char c = grid[x][y];
            if (c == 'X') {
                xmasFound += findXmas(grid, GRID_SIDE_SZ, x, y);
            }
        }
    }

    std::cout << "Part 1: " << xmasFound << "\n";

    return EXIT_SUCCESS;
}
