#include <algorithm>
#include <array>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>

constexpr int16_t GRID_SIDE_SIZE = 130; 
constexpr char OBSTACLE = '#';
constexpr char GUARD = '^';
constexpr char VISITED = 'X';

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
        uint16_t &visitedCount,
        const Position &currentPosition);

static bool isObstruction(const std::array<std::array<char, GRID_SIDE_SIZE>, GRID_SIDE_SIZE> &grid, const Position &position);
static Position getNextPosition(const std::array<std::array<char, GRID_SIDE_SIZE>, GRID_SIDE_SIZE> &grid, const Position &currentPosition);

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

    uint16_t visitedCount = 0;
    walk(grid, visitedCount, guardPos);
    

    std::cout << "Part 1: " << visitedCount << '\n';

    return EXIT_SUCCESS;
}

static bool isObstruction(const std::array<std::array<char, GRID_SIDE_SIZE>, GRID_SIDE_SIZE> &grid, const Position &position) {
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
        uint16_t &visitedCount,
        const Position &currentPosition) {

    if (currentPosition.isOutOfGrid()) {
        return;
    }

    if(grid[currentPosition.x][currentPosition.y] != VISITED) {
        grid[currentPosition.x][currentPosition.y] = VISITED;
        visitedCount++;
    }

    const Position next = getNextPosition(grid, currentPosition);

    return walk(grid, visitedCount, next);
}
