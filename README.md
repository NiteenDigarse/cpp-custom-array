# CustomArray

A fixed-size, STL-style array container implemented from scratch in **modern C++17**.

CustomArray is designed to understand how fixed-size containers work internally, with a focus on **contiguous memory, templates, iterators, const-correctness, bounds checking, object lifetime, and generic programming**.

---

## Overview

`CustomArray<T, N>` provides a fixed-size contiguous container similar in concept to `std::array`.

Unlike a dynamic container such as `std::vector`, the size of `CustomArray` is part of its type and is known at compile time.

```cpp
CustomArray<int, 5> numbers;
```

The underlying storage is embedded directly inside the object:

```cpp
T data_[N];
```

This makes the container simple, predictable, and useful for understanding low-level C++ container design.

---

## Key Features

* Fixed-size compile-time storage
* Contiguous memory layout
* Generic programming using class templates
* `operator[]` for unchecked access
* `at()` for bounds-checked access
* `front()` and `back()`
* `data()` for direct pointer access
* `begin()` / `end()` iterators
* `cbegin()` / `cend()` const iterators
* Range-based `for` loop support
* `fill()`
* `swap()`
* Equality and inequality comparison
* Const-correct API
* `constexpr` capacity information
* Zero dynamic memory allocation
* Rule of Zero
* Copy and move semantics through compiler-generated operations
* Edge-case testing
* Custom object lifetime testing
* CMake build system
* Automated testing with CTest
* Performance benchmarking against `std::array`

---

## Example

```cpp
#include "CustomArray.h"
#include <iostream>

int main()
{
    CustomArray<int, 5> numbers;

    numbers.fill(10);

    numbers[2] = 50;

    for (const auto& value : numbers)
    {
        std::cout << value << ' ';
    }

    std::cout << '\n';

    std::cout << "Size: " << numbers.size() << '\n';
    std::cout << "Front: " << numbers.front() << '\n';
    std::cout << "Back: " << numbers.back() << '\n';

    return 0;
}
```

Output:

```text
10 10 50 10 10
Size: 5
Front: 10
Back: 10
```

---

## API

### Element Access

| Function     | Description                   |
| ------------ | ----------------------------- |
| `operator[]` | Unchecked element access      |
| `at()`       | Bounds-checked element access |
| `front()`    | Access first element          |
| `back()`     | Access last element           |
| `data()`     | Pointer to underlying storage |

Example:

```cpp
numbers[0] = 100;
numbers.at(1) = 200;
```

`operator[]` does not perform bounds checking.

```cpp
numbers[100];   // Undefined behavior
```

`at()` checks the index and throws `std::out_of_range` when invalid.

```cpp
numbers.at(100);   // throws std::out_of_range
```

---

## Capacity

```cpp
numbers.size();
numbers.empty();
```

Because `N` is a template parameter, the size is known at compile time.

```cpp
CustomArray<int, 10> numbers;

static_assert(numbers.size() == 10);
```

---

## Iterators

CustomArray supports standard iterator-style access:

```cpp
for (auto it = numbers.begin(); it != numbers.end(); ++it)
{
    std::cout << *it << ' ';
}
```

It also supports range-based loops:

```cpp
for (const auto& value : numbers)
{
    std::cout << value << ' ';
}
```

Const iteration is available through:

```cpp
numbers.cbegin();
numbers.cend();
```

---

## Modifiers

### `fill()`

Assigns the same value to every element.

```cpp
CustomArray<int, 5> numbers;

numbers.fill(42);
```

Result:

```text
42 42 42 42 42
```

### `swap()`

Exchanges the contents of two arrays.

```cpp
CustomArray<int, 3> a;
CustomArray<int, 3> b;

a.fill(10);
b.fill(20);

a.swap(b);
```

---

## Comparison

Arrays of the same type can be compared:

```cpp
CustomArray<int, 3> a;
CustomArray<int, 3> b;

a.fill(10);
b.fill(10);

if (a == b)
{
    std::cout << "Arrays are equal\n";
}
```

Supported operators:

```cpp
==
!=
```

---

## Memory Model

The core storage is:

```cpp
T data_[N];
```

For:

```cpp
CustomArray<int, 5> arr;
```

memory conceptually looks like:

```text
CustomArray object
┌──────────────────────────────┐
│ data_[0]                     │
├──────────────────────────────┤
│ data_[1]                     │
├──────────────────────────────┤
│ data_[2]                     │
├──────────────────────────────┤
│ data_[3]                     │
├──────────────────────────────┤
│ data_[4]                     │
└──────────────────────────────┘
```

The elements are stored **contiguously**.

Therefore:

```cpp
arr.data()
```

returns a pointer to the first element, and:

```cpp
arr.data() + 1
```

points to the next element.

The address relationship is equivalent to:

```text
&arr[0]
&arr[1]
&arr[2]
&arr[3]
&arr[4]
```

with each element positioned according to `sizeof(T)`.

---

## Fixed Size vs Dynamic Size

CustomArray:

```cpp
CustomArray<int, 100>
```

The `100` is part of the type.

Therefore:

```cpp
CustomArray<int, 100>
```

and:

```cpp
CustomArray<int, 200>
```

are different C++ types.

This is fundamentally different from a dynamic container such as:

```cpp
std::vector<int>
```

where the size is determined at runtime.

---

## Object Lifetime

CustomArray does not manually allocate or release memory.

For example:

```cpp
CustomArray<Tracker, 3> arr;
```

creates three `Tracker` objects as part of the array's storage.

When `arr` is destroyed, its elements are automatically destroyed.

This allows CustomArray to follow the **Rule of Zero**.

No custom:

```cpp
~CustomArray()
CustomArray(const CustomArray&)
operator=(const CustomArray&)
CustomArray(CustomArray&&)
operator=(CustomArray&&)
```

implementation is required.

The compiler-generated special member functions correctly handle the embedded array.

---

## Template Design

CustomArray is implemented as:

```cpp
template <typename T, std::size_t N>
class CustomArray
```

Where:

* `T` → element type
* `N` → number of elements

Examples:

```cpp
CustomArray<int, 5>
CustomArray<double, 10>
CustomArray<std::string, 3>
```

Because this is a class template, the implementation is kept in the header:

```text
include/CustomArray.h
```

The `.cpp` file is intentionally unused for the template implementation.

---

## Edge Cases

The project includes tests for:

* Empty arrays
* Single-element arrays
* Boundary indexes
* Invalid `at()` access
* Empty-array iterators
* Const access
* Custom object storage
* Copy behavior
* Move behavior
* Object lifetime
* `fill()`
* `swap()`
* Comparisons

### Empty Array

```cpp
CustomArray<int, 0> arr;
```

Conceptually:

```text
size()  → 0
empty() → true
begin() == end()
```

The storage contains no usable elements.

`front()` and `back()` must not be called on an empty array.

---

## Project Structure

```text
cpp-custom-array/
│
├── .gitignore
├── CMakeLists.txt
├── LICENSE
│
├── include/
│   └── CustomArray.h
│
├── src/
│   └── CustomArray.cpp
│
├── tests/
│   └── test.cpp
│
├── examples/
│   └── basic_example.cpp
│
└── benchmarks/
    └── benchmark.cpp
```

---

## Building

### Configure

From the project root:

```bash
cmake -S . -B build -G "MinGW Makefiles"
```

### Build

```bash
cmake --build build
```

For a Release build:

```bash
cmake --build build --config Release
```

---

## Running the Example

```bash
build/CustomArrayExample
```

On Windows with MinGW:

```cmd
build\CustomArrayExample.exe
```

---

## Running Tests

The project uses **CTest**.

```bash
cd build
ctest
```

Expected result:

```text
100% tests passed, 0 tests failed
```

The test suite covers the public API, edge cases, copy/move behavior, const-correctness, and custom object lifetime.

---

## Benchmarking

The project contains a benchmark comparing sequential access performance between:

```text
CustomArray<int, N>
std::array<int, N>
```

The benchmark performs:

```text
100,000 elements
×
1,000 iterations
=
100,000,000 accesses
```

A checksum is used to verify that both implementations perform the same logical workload.

Example benchmark output:

```text
CustomArray
Time: 158203 microseconds
Checksum: 4999950000000

std::array
Time: 199410 microseconds
Checksum: 4999950000000
```

The checksum matching confirms that both benchmark paths produced the same accumulated result.

Benchmark timings can vary between runs depending on CPU state, operating-system scheduling, compiler optimization, and system load. Therefore, a single run should not be treated as a definitive statement about which container is faster.

---

## C++ Concepts Practiced

This project focuses on practical understanding of:

* Class templates
* Non-type template parameters
* Compile-time information
* Contiguous storage
* Arrays and pointers
* Pointer arithmetic
* References
* `const` correctness
* Function overloading
* Operator overloading
* Iterators
* Range-based `for`
* Exception handling
* `std::out_of_range`
* Object lifetime
* Copy semantics
* Move semantics
* Rule of Zero
* `constexpr`
* Generic programming
* CMake
* CTest
* Benchmarking
* STL-style API design

---

## Design Philosophy

The goal of this project is not simply to recreate `std::array`.

The primary objective is to understand **why a fixed-size container works the way it does**.

The implementation focuses on:

```text
Memory
   ↓
Object Lifetime
   ↓
Type System
   ↓
Templates
   ↓
API Design
   ↓
Const Correctness
   ↓
Iterators
   ↓
Testing
   ↓
Performance
   ↓
Engineering Practices
```

---

## Project Status

**Status:** Complete

Implemented and tested:

* Core container API
* Element access
* Bounds checking
* Iterators
* Range-based iteration
* Const correctness
* Modifiers
* Comparisons
* Copy/move behavior
* Lifetime testing
* Edge cases
* CMake build system
* CTest integration
* Benchmarking
* Code cleanup and refactoring

---

## Part of C++ Engineering Projects

CustomArray is part of a long-term **C++ Engineering Projects** journey focused on building containers, utilities, and systems from scratch while developing a deeper understanding of modern C++.

The projects progressively explore:

```text
C++ Fundamentals
        ↓
Object-Oriented Programming
        ↓
Memory Management
        ↓
Templates & Generic Programming
        ↓
STL-style Containers
        ↓
Concurrency
        ↓
Systems Programming
        ↓
Advanced C++ Engineering
```

---

## License

This project is licensed under the terms specified in the repository's `LICENSE` file.
