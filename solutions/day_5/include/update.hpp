#pragma once

#include <array>
#include <cstdint>
#include <vector>

static constexpr uint8_t NUM_PAGES = 100;
static constexpr uint8_t NUM_UPDATE_LINES = 208;

bool isUpdateOrdered(const std::vector<uint8_t> &pages, const std::array<std::array<bool, NUM_PAGES>, NUM_PAGES> &rules);

uint8_t getMiddlePage(const std::vector<uint8_t> &pages);

void reorderPages(std::vector<uint8_t> &pages, const std::array<std::array<bool, NUM_PAGES>, NUM_PAGES> &rules);


