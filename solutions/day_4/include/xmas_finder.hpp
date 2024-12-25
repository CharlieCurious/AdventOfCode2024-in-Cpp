#pragma once

#include <cstddef>
#include <cstdint>

template<size_t Rows, size_t Cols>
bool matchesPatternXmas(const char (&grid)[Rows][Cols], uint8_t x, uint8_t y, int8_t dx, int8_t dy) {
    return grid[x][y] == 'M' &&
        grid[x + dx][y + dy] == 'A' &&
        grid[x + 2 * dx][y + 2 * dy] == 'S';
}

template<size_t Rows, size_t Cols>
bool matchesPatternX_MAS(const char (&grid)[Rows][Cols], uint8_t x, uint8_t y) {
    char northWest = grid[x-1][y-1];
    char southEast = grid[x+1][y+1];
    bool makesBackSlash = (northWest == 'M' && southEast == 'S') || 
        (northWest == 'S' && southEast == 'M');

    if (makesBackSlash) {
        char northEast = grid[x-1][y+1];
        char southWest = grid[x+1][y-1];

        return (northEast == 'M' && southWest == 'S') ||
            (northEast == 'S' && southWest == 'M');
    }

    return false;
}

template<size_t Rows, size_t Cols>
uint8_t findXmasNorth(const char (&grid)[Rows][Cols], uint8_t gridSideSize, uint8_t x, uint8_t y) {
    uint8_t count = 0;
    if (x < 3 ) {
        return count;
    }

    if (matchesPatternXmas(grid, x-1, y, -1, 0)) {
        count++;
    }

    if (y-3 >= 0 && matchesPatternXmas(grid, x-1, y-1, -1, -1)) {
       count++; 
    }

    if (y+3 < gridSideSize && matchesPatternXmas(grid, x-1, y+1, -1, 1)) {
        count++;
    }

    return count;
}

template<size_t Rows, size_t Cols>
uint8_t findXmasEastWest(const char (&grid)[Rows][Cols], uint8_t gridSideSize, uint8_t x, uint8_t y) {
    uint8_t count = 0;

    if (y-3 >= 0 && matchesPatternXmas(grid, x, y-1, 0, -1)) {
        count++;
    }

    if (y+3 < gridSideSize && matchesPatternXmas(grid, x, y+1, 0, 1)) {
        count++;
    }

    return count;
}

template<size_t Rows, size_t Cols>
uint8_t findXmasSouth(const char (&grid)[Rows][Cols], uint8_t gridSideSize, uint8_t x, uint8_t y) {
    uint8_t count = 0;
    if (x+3 >= gridSideSize) {
        return count;
    }
    if (matchesPatternXmas(grid, x+1, y, 1, 0)) {
        count++;
    }

    if (y-3 >= 0 && matchesPatternXmas(grid, x+1, y-1, 1, -1)) {
       count++; 
    }

    if (y+3 < gridSideSize && matchesPatternXmas(grid, x+1, y+1, 1, 1)) {
        count++;
    }

    return count;
}

template<size_t Rows, size_t Cols>
uint8_t findXmas(const char (&grid)[Rows][Cols], uint8_t gridSideSize, uint8_t x, uint8_t y) {
    uint8_t xmasCount = 0;

    xmasCount += findXmasNorth(grid, gridSideSize, x, y);
    xmasCount += findXmasEastWest(grid, gridSideSize, x, y);
    xmasCount += findXmasSouth(grid, gridSideSize, x, y);

    return xmasCount;
}

