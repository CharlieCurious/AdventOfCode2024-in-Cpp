#include <disk.hpp>
#include <optional>
#include <string>

Disk::Disk(const std::string_view map) {

    size_t file = -1;
    size_t index = 0;

    for (size_t i = 0; map[i] != '\0'; i++) {
        size_t count = map[i] - '0';

        const bool not_empty = i % 2 == 0;

        if (not_empty) {
            this->m_files.push_back(File(index, count));
            file++;
        } else {
            this->m_free.push_back(std::pair<size_t, size_t>(index, index + count - 1));
        }

        for (size_t j = 0; j < count; j++) {
            auto value = not_empty ? std::optional(file) : std::nullopt;
            m_blocks.push_back(value);
            index++;
        }
    }
}

size_t Disk::checksum() {
    size_t checksum = 0;

    for (size_t i = 0; i < m_blocks.size(); i++) {
        checksum += m_blocks[i].value_or(0) * i;
    }

    return checksum;
}

std::string Disk::to_string() {
    std::string result;

    for (const auto& opt : m_blocks) {
        if (opt.has_value()) {
            result += std::to_string(*opt);
        } else {
            result += '.';
        }
    }

    return result;
}
