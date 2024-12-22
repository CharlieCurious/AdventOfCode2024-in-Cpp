#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <ostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

int main() {
    const string fileName = "input_files/day_1.txt"; 
    ifstream file(fileName);
    if (!file.is_open()) {
        cerr << "Failed to open the file." << endl;
        return EXIT_FAILURE;
    }

    vector<int32_t> leftCol;
    vector<int32_t> rightCol;
    unordered_map<int32_t, int32_t> multipliers;

    string line;
    uint32_t lineCount = 0;
    while (getline(file, line)) {
        istringstream iss(line);
        int32_t leftNum, rightNum;
        if (iss >> leftNum >> rightNum) {
            leftCol.push_back(leftNum);
            rightCol.push_back(rightNum);

            multipliers[rightNum]++;
        } else {
            cerr << "Invalid line format: " << line << endl;
            return EXIT_FAILURE;
        }

        lineCount++;
    }

    sort(leftCol.begin(), leftCol.end());
    sort(rightCol.begin(), rightCol.end());

    int32_t part1Sum = 0;
    int32_t part2Sum = 0;
    for (uint32_t i = 0; i < lineCount; i++) {
        int32_t leftNum = leftCol[i];
        int32_t rightNum = rightCol[i];
        part1Sum += abs(leftNum - rightNum);
        part2Sum += multipliers[leftNum] == 0 ? 0 : leftNum * multipliers[leftNum];
    }

    cout << "Part 1: " << part1Sum << endl;
    cout << "Part 2: " << part2Sum << endl;

    return EXIT_SUCCESS;
}
