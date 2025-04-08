#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>

#define BLOCKSIZE 1024

int main() {

    std::ifstream file("input_files/day_9.txt");
    if (!file.is_open()) {
        throw std::runtime_error("Could not open input file");
    }

    std::vector<std::string> blocks;
    blocks.reserve(BLOCKSIZE);

    bool isSpace = false;
    char ch;
    uint32_t index = 0;
    while (file.get(ch)) {

        size_t value = ch - '0';

        if (isSpace) {
            blocks.insert(blocks.end(), value, ".");
        } else {
            blocks.insert(blocks.end(), value, std::to_string(index));
            index++;
        }

        isSpace = !isSpace;
    }

    size_t left = 0;
    size_t right = blocks.size() - 1;

    while (right > left && right > 0 && left < blocks.size()) {
        if (blocks[right] == ".") {
            right--;
            continue;
        }
        if (blocks[left] != ".") {
            left++;
            continue;
        }

        std::swap(blocks[left], blocks[right]);
        left++;
        right--;
    }


    uint64_t checksum = 0;

    for (size_t i = 0; i < blocks.size(); i++) {
        if (blocks[i] == ".") {
            break;
        }

        checksum += i * std::stoull(blocks[i]);
    }

    std::cout << "Part 1: " << checksum << '\n';
}
