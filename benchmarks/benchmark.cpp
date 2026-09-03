#include "../include/CustomArray.h"

#include <array>
#include <chrono>
#include <cstddef>
#include <iostream>

// ============================================================
// Benchmark Configuration
// ============================================================

constexpr std::size_t ARRAY_SIZE = 100000;
constexpr std::size_t ITERATIONS = 1000;

// ============================================================
// Benchmark: CustomArray Sequential Access
// ============================================================

void benchmarkCustomArray()
{
    CustomArray<int, ARRAY_SIZE> arr;

    for (std::size_t i = 0; i < ARRAY_SIZE; ++i)
    {
        arr[i] = static_cast<int>(i);
    }

    volatile long long sum = 0;

    auto start = std::chrono::high_resolution_clock::now();

    for (std::size_t iteration = 0; iteration < ITERATIONS; ++iteration)
    {
        for (std::size_t i = 0; i < ARRAY_SIZE; ++i)
        {
            sum += arr[i];
        }
    }

    auto end = std::chrono::high_resolution_clock::now();

    auto duration =
        std::chrono::duration_cast<std::chrono::microseconds>(
            end - start
        );

    std::cout << "CustomArray\n";
    std::cout << "Time: " << duration.count() << " microseconds\n";
    std::cout << "Checksum: " << sum << "\n\n";
}

// ============================================================
// Benchmark: std::array Sequential Access
// ============================================================

void benchmarkStdArray()
{
    std::array<int, ARRAY_SIZE> arr{};

    for (std::size_t i = 0; i < ARRAY_SIZE; ++i)
    {
        arr[i] = static_cast<int>(i);
    }

    volatile long long sum = 0;

    auto start = std::chrono::high_resolution_clock::now();

    for (std::size_t iteration = 0; iteration < ITERATIONS; ++iteration)
    {
        for (std::size_t i = 0; i < ARRAY_SIZE; ++i)
        {
            sum += arr[i];
        }
    }

    auto end = std::chrono::high_resolution_clock::now();

    auto duration =
        std::chrono::duration_cast<std::chrono::microseconds>(
            end - start
        );

    std::cout << "std::array\n";
    std::cout << "Time: " << duration.count() << " microseconds\n";
    std::cout << "Checksum: " << sum << "\n\n";
}

// ============================================================
// Main
// ============================================================

int main()
{
    std::cout << "========================================\n";
    std::cout << "       CustomArray Benchmark\n";
    std::cout << "========================================\n\n";

    std::cout << "Array size: " << ARRAY_SIZE << '\n';
    std::cout << "Iterations: " << ITERATIONS << "\n\n";

    benchmarkCustomArray();
    benchmarkStdArray();

    return 0;
}