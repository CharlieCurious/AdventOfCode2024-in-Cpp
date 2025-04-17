#include <algorithm>
#include <cstdint>
#include <vector>
#include <ranges>
#include <fstream>
#include <iostream>

#define BLOCKSIZE 1024

constexpr int32_t EMPTY_VALUE = -1;

struct Block {
    size_t start;
    size_t end;
    size_t blockSize;
    uint32_t value;
    bool isEmpty;
};

std::vector<int32_t> fragmentPart1(const std::vector<std::vector<int32_t>> &disk) {
    auto flatView = disk | std::views::join;
    std::vector<int32_t> flat(flatView.begin(), flatView.end());

    size_t left = 0;
    size_t right = flat.size() - 1;

    while (left < right) {
        if (flat[right] == EMPTY_VALUE) {
            right--;
            continue;
        }
        if (flat[left] != EMPTY_VALUE) {
            left++;
            continue;
        }

        std::swap(flat[left], flat[right]);
        left++;
        right--;
    }

    return flat;
}

std::vector<int32_t> fragmentPart2(const std::vector<std::vector<int32_t>> &disk) {

    std::vector<std::pair<size_t, size_t>> ranges;
    std::vector<int32_t> flat;

    size_t offset = 0;
    for (const auto &row : disk) {
        size_t start = offset;
        flat.insert(flat.end(), row.begin(), row.end());
        offset += row.size();
        size_t end = offset - 1;

        ranges.emplace_back(start, end);
    }

    for (size_t i = disk.size(); i-- > 0;) {
        size_t requiredSpace = disk[i].size();

        auto it = std::search_n(flat.begin(), flat.begin() + ranges[i].first, requiredSpace, -1);
        if (it != flat.begin() + ranges[i].first) {
            size_t insertPosition = std::distance(flat.begin(), it);

            std::copy(disk[i].begin(), disk[i].end(), flat.begin() + insertPosition);

            for (size_t j = ranges[i].first; j < ranges[i].first + requiredSpace; ++j) {
                flat[j] = -1;
            }
        }
    }

    return flat;
}

uint64_t calculateChecksum(const std::vector<int32_t> &disk) {
    uint64_t checksum = 0;

    for (size_t i = 0; i < disk.size(); i++) {
        if (disk[i] == EMPTY_VALUE) {
            continue;
        }

        checksum += i * disk[i];
    }

    return checksum;
}


int main() {

    std::ifstream file("input_files/day_9.txt");
    if (!file.is_open()) {
        throw std::runtime_error("Could not open input file");
    }

    std::vector<std::vector<int32_t>> blocks;
    blocks.reserve(BLOCKSIZE);

    bool isSpace = false;
    char ch;
    uint32_t index = 0;
    while (file.get(ch)) {

        size_t value = ch - '0';

        if (isSpace) {
            blocks.push_back(std::vector<int32_t>(value, EMPTY_VALUE));
        } else {
            blocks.push_back(std::vector<int32_t>(value, index));
            index++;
        }

        isSpace = !isSpace;
    }

    std::vector<int32_t> part1Disk = fragmentPart1(blocks);
    uint64_t part1Checksum = calculateChecksum(part1Disk);

    std::vector<int32_t> part2Disk = fragmentPart2(blocks);
    uint64_t part2Checksum = calculateChecksum(part2Disk);

    std::cout << "Part 1: " << part1Checksum << '\n';
    std::cout << "Part 2: " << part2Checksum << '\n';
}
