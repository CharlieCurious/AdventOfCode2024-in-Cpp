#define BOOST_UT_ENABLE_REPORTING

#include <boost/ut.hpp>
#include <disk.hpp>
#include <string_view>

using namespace boost::ut;
using namespace boost::ut::bdd;

constexpr std::string_view test_map = "12345";

int main() {
    "creates_correct_number_of_files"_test = [] {
        given("a disk map") = [] {
            when("constructing a Disk instance") = [] {
                Disk disk(test_map);

                then("expect to have 3 Files with correct index and size") = [&disk] {
                    expect(disk.m_files.size() == 3);

                    expect(disk.m_files[0].m_head == 0);
                    expect(disk.m_files[0].m_length == 1);

                    expect(disk.m_files[1].m_head == 3);
                    expect(disk.m_files[1].m_length == 3);

                    expect(disk.m_files[2].m_head == 10);
                    expect(disk.m_files[2].m_length == 5);
                };
            };
        };
    };

    "creates_correct_number_of_free_space"_test = [] {
        given("a disk map") = [] {
            when("constructing a Disk instance") = [] {
                Disk disk(test_map);

                then("expect to have 2 empty spaces with correct indexes") = [&disk] {
                    expect(disk.m_free.size() == 2);

                    expect(disk.m_free[0].first == 1);
                    expect(disk.m_free[0].second == 2);

                    expect(disk.m_free[1].first == 6);
                    expect(disk.m_free[1].second == 9);
                };
            };
        };
    };

    "creates_correct_number_of_blocks_with_correct_value"_test = [] {
        given("a disk map") = [] {
            when("constructing a Disk instance") = [] {
                Disk disk(test_map);
                std::string string_representation = disk.to_string();

                then("expect to have correct number of blocks and correct values for each block") = [&string_representation] {
                    expect(string_representation == "0..111....22222");
                };
            };
        };
    };

    "calculates_checksum_correctly"_test = [] {
        given("a disk") = [] {
            Disk disk(test_map);

            when("calculating the checksum") = [&disk] {
                disk.m_blocks =  std::vector<std::optional<size_t>> {
                    0, 0, 9, 9, 8, 1, 1, 1, 8, 8,
                    8, 2, 7, 7, 7, 3, 3, 3, 6, 4,
                    4, 6, 5, 5, 5, 5, 6, 6,
                    std::nullopt, std::nullopt, std::nullopt, std::nullopt,
                    std::nullopt, std::nullopt, std::nullopt, std::nullopt,
                    std::nullopt, std::nullopt, std::nullopt, std::nullopt
                };
                size_t checksum = disk.checksum();

                then("expect the checksum to be correct") = [&checksum] {
                    expect(checksum == 1928) << "expected 1928, got " << checksum;
                };
            };
        };
    };
}
