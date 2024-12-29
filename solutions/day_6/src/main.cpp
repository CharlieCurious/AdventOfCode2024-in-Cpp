#include <algorithm>
#include <array>
#include <bitset>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>

constexpr int16_t GRID_SIDE_SIZE = 130; 
constexpr char OBSTACLE = '#';
constexpr char GUARD = '^';

enum Direction : int16_t {
    NORTH,
    EAST,
    WEST,
    SOUTH
};

struct Position {
    int16_t x;
    int16_t y;
    Direction direction;

    Position() : x{0}, y{0}, direction{NORTH} {}

    Position(int16_t x, int16_t y, Direction direction) : 
        x{x}, y{y}, direction{direction} {}

    Position(const Position&) = default;
    Position& operator=(const Position&) = default;

    Position(Position&&) noexcept = default;
    Position& operator=(Position&&) noexcept = default;

    bool operator==(const Position &other) const {
        return this->x == other.x && 
            this->y == other.y &&
            this->direction == other.direction;
    }

    Position nextPosition(Direction direction) const {
        switch(direction) {
            case NORTH:
                return Position(this->x-1, this->y, NORTH);
            case EAST:
                return Position(this->x, this->y+1, EAST);
            case WEST:
                return Position(this->x, this->y-1, WEST);
            default:
                return Position(this->x+1, this->y, SOUTH);
        }
    }

    bool isOutOfGrid() const {
        return this->x < 0 || this->x > GRID_SIDE_SIZE-1 ||
            this->y < 0 || this->y > GRID_SIDE_SIZE-1;
    }
};

static void walk(
        std::array<std::array<char, GRID_SIDE_SIZE>, GRID_SIDE_SIZE> &grid, 
        std::vector<std::array<std::bitset<GRID_SIDE_SIZE>, 4>> &visitedCache,
        Position &currentPosition,
        uint16_t *cyclesDetected);

static inline bool isObstruction(const std::array<std::array<char, GRID_SIDE_SIZE>, GRID_SIDE_SIZE> &grid, const Position &position);
static Position getNextPosition(const std::array<std::array<char, GRID_SIDE_SIZE>, GRID_SIDE_SIZE> &grid, const Position &currentPosition);

static inline bool isVisitedSameDirection(const std::vector<std::array<std::bitset<GRID_SIDE_SIZE>, 4>> &visitedCache, int16_t x, int16_t y, Direction direction) {
    return visitedCache[x][direction].test(y);
}

static uint16_t getTotalVisitedCount(const std::vector<std::array<std::bitset<GRID_SIDE_SIZE>, 4>> &visitedCache) {
    uint16_t visitedCount = 0;

    for (int16_t x = 0; x < GRID_SIDE_SIZE; x++) {
        for (int16_t y = 0; y < GRID_SIDE_SIZE; y++) {
            bool isVisitedInAnyDirection = false;
            for (int dir = 0; dir < 4; dir++) {
                if (visitedCache[x][dir].test(y)) {
                    isVisitedInAnyDirection = true;
                    break;
                }
            }
            if (isVisitedInAnyDirection) {
                visitedCount++;
            }
        }
    }

    return visitedCount;
}

int main() {

    FILE *file = fopen("input_files/day_6.txt", "r");
    if (!file) {
        std::cerr << "Failed to open input file." << std::endl;
        return EXIT_FAILURE;
    }

    std::array<std::array<char, GRID_SIDE_SIZE>, GRID_SIDE_SIZE> grid = {}; 

    int16_t lineIndex = 0;
    char buffer[GRID_SIDE_SIZE+2]; // account for newline and '\0'
    Position guardPos;

    // TIL: fgets reads sizeof(buffer) - 1 chars but at the next iterations it does not start
    // at the next line, it starts where it left off.
    while (lineIndex < GRID_SIDE_SIZE && fgets(buffer, sizeof(buffer), file)) {
        buffer[GRID_SIDE_SIZE] = '\0';

        std::copy_n(buffer, GRID_SIDE_SIZE, grid[lineIndex].begin());

        char *guard = strchr(buffer, GUARD);
        if (guard) {
            guardPos = Position(lineIndex, guard - buffer, NORTH);
        }

        lineIndex++;
    }

    fclose(file);

    std::vector<std::array<std::bitset<GRID_SIDE_SIZE>, 4>> visitedCache(GRID_SIDE_SIZE);
    walk(grid, visitedCache, guardPos, nullptr);

    uint16_t totalVisitedCount = getTotalVisitedCount(visitedCache);
    
    uint16_t cyclesDetected = 0;
    std::vector<std::array<std::bitset<GRID_SIDE_SIZE>, 4>> visitedCachePart2(GRID_SIDE_SIZE);
    for (int16_t x = 0; x < GRID_SIDE_SIZE; ++x) {
        for (int16_t y = 0; y < GRID_SIDE_SIZE; ++y) {

            bool visitedInAnyDirection = false;

            for (int dir = 0; dir < 4; ++dir) {  // Check for all 4 directions
                if (visitedCache[x][dir].test(y)) {
                    visitedInAnyDirection = true;
                    break;                
                }
            }

            if (visitedInAnyDirection) {
                char tmp = grid[x][y];
                if (tmp == GUARD) {
                    continue;                }

                grid[x][y] = OBSTACLE;

                walk(grid, visitedCachePart2, guardPos, &cyclesDetected);
                grid[x][y] = tmp;

                std::fill(visitedCachePart2.begin(), visitedCachePart2.end(), std::array<std::bitset<GRID_SIDE_SIZE>, 4>{});
            }
        }
    }

    std::cout << "Part 1: " << totalVisitedCount << '\n';
    std::cout << "Part 2: " << cyclesDetected << '\n';

    return EXIT_SUCCESS;
}

static inline bool isObstruction(const std::array<std::array<char, GRID_SIDE_SIZE>, GRID_SIDE_SIZE> &grid, const Position &position) {
    if (position.x < 0 || position.x >= GRID_SIDE_SIZE ||
            position.y < 0 || position.y >= GRID_SIDE_SIZE)
        return false;

    return grid[position.x][position.y] == OBSTACLE;
}

static Position getNextPosition(const std::array<std::array<char, GRID_SIDE_SIZE>, GRID_SIDE_SIZE> &grid, const Position &currentPosition) {
    Position next;
    switch (currentPosition.direction) {
        case NORTH:
            next = currentPosition.nextPosition(NORTH);
            if (isObstruction(grid, next)) {
                next = currentPosition.nextPosition(EAST);
                if (isObstruction(grid, next)) {
                    next = currentPosition.nextPosition(SOUTH);
                }
            }
            break;
        case EAST:
            next = currentPosition.nextPosition(EAST);
            if (isObstruction(grid, next)) {
                next = currentPosition.nextPosition(SOUTH);
                if (isObstruction(grid, next)) {
                    next = currentPosition.nextPosition(WEST);
                }
            }
            break;
        case WEST:
            next = currentPosition.nextPosition(WEST);
            if (isObstruction(grid, next)) {
                next = currentPosition.nextPosition(NORTH);
                if (isObstruction(grid, next)) {
                    next = currentPosition.nextPosition(EAST);
                }
            }
            break;
        case SOUTH:
            next = currentPosition.nextPosition(SOUTH);
            if (isObstruction(grid, next)) {
                next = currentPosition.nextPosition(WEST);
                if (isObstruction(grid, next)) {
                    next = currentPosition.nextPosition(NORTH);
                }
            }
            break;
    }
    return next;
}

void walk(
        std::array<std::array<char, GRID_SIDE_SIZE>, GRID_SIDE_SIZE> &grid, 
        std::vector<std::array<std::bitset<GRID_SIDE_SIZE>, 4>> &visitedCache,
        Position &startPosition,
        uint16_t *cyclesDetected) {

    Position current = startPosition;
    while (true) {
        if (current.isOutOfGrid()) {
            return;
        }

        if (cyclesDetected != nullptr && isVisitedSameDirection(visitedCache, current.x, current.y, current.direction)) {
            (*cyclesDetected)++;
            return;
        }

        visitedCache[current.x][current.direction].set(current.y);

        current = getNextPosition(grid, current);
    }
}
