#include <cstdlib>
#include <report.hpp>

bool isLineSafe(std::vector<int32_t> numbers) {
    bool isIncreasing = numbers[1] > numbers[0];

    for (uint8_t i = 1; i < numbers.size(); i++) {
        int32_t current = numbers[i];
        int32_t previous = numbers[i-1]; 
        uint32_t difference = abs(current - previous);
        if (difference > 3 || difference < 1) {
            return false;
        }
        if (isIncreasing && current < previous) {
            return false;
        }
        if(!isIncreasing && current > previous) {
            return false;
        }
    }

    return true;
}
