#include <algorithm>
#include <array>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <unordered_set>

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

    bool operator==(const Position &other) const {
        return this->x == other.x && 
            this->y == other.y &&
            this->direction == other.direction;
    }

    Position(Position&&) noexcept = default;
    Position& operator=(Position&&) noexcept = default;

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

struct PositionHash {
    std::size_t operator()(const Position &position) const {
        std::size_t seed = 0;
        std::hash<int16_t> hash{};
        seed ^= hash(position.x) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        seed ^= hash(position.y) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        return seed;
    }
};

struct PositionHashWithDirection {
    std::size_t operator()(const Position &position) const {
        std::size_t seed = 0;
        std::hash<int16_t> hash{};
        seed ^= hash(position.x) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        seed ^= hash(position.y) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        seed ^= hash(static_cast<int16_t>(position.direction)) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        return seed;
    }
};

struct PositionEqual {
    bool operator()(const Position &a, const Position &b) const {
        return a.x == b.x && a.y == b.y && a.direction == b.direction; // Ignore direction
    }
};

struct PositionEqualIgnoreDirection {
    bool operator()(const Position &a, const Position &b) const {
        return a.x == b.x && a.y == b.y; // Ignore direction
    }
};

template<typename Hash, typename Equality>
static void walk(
        std::array<std::array<char, GRID_SIDE_SIZE>, GRID_SIDE_SIZE> &grid, 
        std::unordered_set<Position, Hash, Equality> &visited,
        Position &currentPosition,
        uint16_t *cyclesDetected);

static inline bool isObstruction(const std::array<std::array<char, GRID_SIDE_SIZE>, GRID_SIDE_SIZE> &grid, const Position &position);
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

    std::unordered_set<Position, PositionHash, PositionEqualIgnoreDirection> visited;
    visited.reserve(5000);
    walk(grid, visited, guardPos, nullptr);
    
    uint16_t cyclesDetected = 0;
    std::unordered_set<Position, PositionHashWithDirection> visitedWithDirection;
    visited.reserve(5000);
    for (const auto &position : visited) {
        char tmp = grid[position.x][position.y];
        if (tmp == GUARD)
            continue;

        grid[position.x][position.y] = OBSTACLE; 

        walk(grid, visitedWithDirection, guardPos, &cyclesDetected);

        grid[position.x][position.y] = tmp; 

        visitedWithDirection.clear();
    }

    std::cout << "Part 1: " << visited.size() << '\n';
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

template<typename Hash, typename Equality>
void walk(
        std::array<std::array<char, GRID_SIDE_SIZE>, GRID_SIDE_SIZE> &grid, 
        std::unordered_set<Position, Hash, Equality> &visited,
        Position &startPosition,
        uint16_t *cyclesDetected) {

    Position current = startPosition;
    while (true) {
        if (current.isOutOfGrid()) {
            return;
        }

        if (cyclesDetected != nullptr && visited.contains(current)) {
            (*cyclesDetected)++;
            return;
        }

        visited.insert(current);

        current = getNextPosition(grid, current);
    }
}
