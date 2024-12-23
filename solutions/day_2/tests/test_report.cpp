#include <boost/ut.hpp>
#include <report.hpp>

using namespace boost::ut;
using namespace boost::ut::bdd;

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
    };
}
