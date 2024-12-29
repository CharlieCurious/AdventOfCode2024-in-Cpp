#include <cmath>
#include <permutations.hpp>
#include <vector>

void permutationsHelper(std::vector<std::string> &permutations, std::string &slots, uint8_t r, uint8_t index, bool part2) {
    if (index == r) {
        permutations.push_back(slots);
        return;
    }
    
    slots[index] = '+';
    permutationsHelper(permutations, slots, r, index+1, part2);

    slots[index] = '*';
    permutationsHelper(permutations, slots, r, index+1, part2);

    if (part2) {
        slots[index] = '|';
        permutationsHelper(permutations, slots, r, index+1, part2);
    }
}

// r == length of permutation
std::vector<std::string> getPermutationsForR(std::unordered_map<uint8_t, std::vector<std::string>> &permutationsCache, uint8_t r, bool part2) {
    if (permutationsCache.contains(r)) {
        return permutationsCache[r];
    }

    std::vector<std::string> permutations;
    permutations.reserve(part2 ? std::pow(3, r) : std::pow(2, r));

    std::string slots(r, ' ');

    permutationsHelper(permutations, slots, r, 0, part2);  

    permutationsCache[r] = permutations;

    return permutations;
}
