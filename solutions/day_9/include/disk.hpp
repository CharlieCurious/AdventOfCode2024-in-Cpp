#include <cstddef>
#include <optional>
#include <string>
#include <vector>

struct File {
	size_t m_head;
	size_t m_length;

	File (size_t head, size_t length) : m_head{head}, m_length{length} {};
};

class Disk {
public:
	std::vector<std::optional<size_t>> m_blocks;
	std::vector<File> m_files;
	std::vector<std::pair<size_t, size_t>> m_free;

	Disk(const std::string_view map);

	Disk(const Disk&) = delete;
	Disk& operator=(const Disk&) = delete;

	Disk(Disk&& other) = delete;
	Disk& operator=(Disk&&) = delete;

	size_t checksum();

    std::string to_string();
};
