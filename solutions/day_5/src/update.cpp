#include <algorithm>
#include <update.hpp>

bool isUpdateOrdered(const std::vector<uint8_t> &pages, const std::array<std::array<bool, NUM_PAGES>, NUM_PAGES> &rules) {
    for (uint8_t i = 0; i < pages.size()-1; i++) {
        if (rules[pages[i+1]][pages[i]]) {
            return false;
        }
    }
    return true;
}

uint8_t getMiddlePage(const std::vector<uint8_t> &pages) {
    return pages[pages.size() / 2];
}

void reorderPages(std::vector<uint8_t> &pages, const std::array<std::array<bool, NUM_PAGES>, NUM_PAGES> &rules) {
    std::sort(pages.begin(), pages.end(), [&rules](uint8_t a, uint8_t b) {
        return rules[a][b];
    });
}
