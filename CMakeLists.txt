cmake_minimum_required(VERSION 3.22.1)

project(AdventOfCode2024 LANGUAGES CXX VERSION 1.0)

set(CMAKE_CXX_COMPILER "g++-12")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # Needed for proper nvim lsp functioning

set(DAY "day_2" CACHE STRING "Day to compile")

# Include custom CMake functions
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
include(AddAdventDay)

add_subdirectory(solutions)

