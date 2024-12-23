cmake_minimum_required(VERSION 3.22.1)

project(AdventOfCode2024 LANGUAGES CXX VERSION 1.0)

set(CMAKE_CXX_COMPILER "g++-12" CACHE STRING "C++ compiler to use") # Cache so other libraries don't try to resolve it again and use this one.

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # Needed for proper nvim lsp functioning.

set(DAY "day_3" CACHE STRING "Day to compile")

# Include custom CMake functions
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
include(AddAdventDay)

option(ENABLE_TESTS "Enable building tests" ON)
if (ENABLE_TESTS)
    enable_testing()
endif()

add_subdirectory(solutions)

