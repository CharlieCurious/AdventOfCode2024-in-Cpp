#include <boost/ut.hpp>

constexpr auto sum(auto... values) { return (values + ...); }

int main() {
    {
        boost::ut::expect(sum(1, 2) == 3);
    }
}
