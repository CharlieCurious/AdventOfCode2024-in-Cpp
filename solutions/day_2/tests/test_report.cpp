#include <boost/ut.hpp>
#include <report.hpp>

using namespace boost::ut;
using namespace boost::ut::bdd;

std::ostream& operator << (std::ostream& os, const std::vector<int32_t>& vec) {
    os << "{ ";
    for (const auto& num : vec) {
        os << num << " ";
    }
    os << " }";
    return os;
}

int main() {
    "isLineSafe"_test = [] {
        given("I have an increasing sequence of numbers within the valid range") = [] {
            std::vector<int32_t> numbers = {1, 2, 3, 4, 5};

            when("I check if the sequence is safe") = [&numbers] {
                bool result = isLineSafe(numbers);

                then("I expect the result to be true") = [&] {
                    expect(result == true);
                };
            };
        };

        given("I have a sequence with a difference greater than 3 between two numbers") = [] {
            std::vector<int32_t> numbers = {1, 5, 7, 8};

            when("I check if the sequence is safe") = [&numbers] {
                bool result = isLineSafe(numbers);

                then("I expect the result to be false") = [&] {
                    expect(result == false);
                };
            };
        };

        given("I have a sequence with difference less than 1 between two numbers") = [] {
            std::vector<int32_t> numbers = {4, 4, 2, 1};

            when("I check if the sequence is safe") = [&numbers] {
                bool result = isLineSafe(numbers);

                then("I expect the result to be false") = [&] {
                    expect(result == false);
                };
            };
        };
    };

    "isLineSafeDampened"_test = [] {
        std::vector<std::pair<std::vector<int32_t>, bool>> testCases = {
            // {report, expected_result}
            {{1, 2, 7, 8, 9}, false},
            {{9, 7, 6, 2, 1}, false},
            {{1, 3, 2, 4, 5}, true},
            {{8, 6, 4, 4, 1}, true},
            {{1, 3, 6, 7, 9}, true}
        };

        for (size_t i = 0; i < testCases.size(); i++) {
            const auto& [numbers, expected] = testCases[i];

            test("isLineSafeDampened case " + std::to_string(i + 1)) = [&] {
                bool result = isLineSafeDampened(numbers);
                expect(result == expected) << " for input: " << numbers;
            };
        }
    };
}
