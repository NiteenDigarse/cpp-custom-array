cmake_minimum_required(VERSION 3.20)

project(CustomArray
VERSION 1.0
LANGUAGES CXX)
enable_testing()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


add_executable(CustomArrayExample examples/basic_example.cpp)

target_include_directories(CustomArrayExample
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_executable(CustomArrayTests
    tests/test.cpp
)

target_include_directories(CustomArrayTests
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
add_test(
    NAME CustomArrayTest
    COMMAND CustomArrayTests
)

# ============================================================
# Benchmarks
# ============================================================

add_executable(CustomArrayBenchmark
    benchmarks/benchmark.cpp
)

target_include_directories(CustomArrayBenchmark
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)