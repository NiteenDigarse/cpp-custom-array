#include "../include/CustomArray.h"

#include <cassert>
#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <utility>

// ============================================================
// Custom Test Object
// ============================================================

class TestObject
{
public:
    int value;

    TestObject(int v = 0)
        : value(v)
    {
    }

    bool operator==(const TestObject& other) const
    {
        return value == other.value;
    }

    bool operator!=(const TestObject& other) const
    {
        return !(*this == other);
    }
};

// ============================================================
// Test Helper
// ============================================================

void printTestPassed(const char* testName)
{
    std::cout << "[PASS] " << testName << '\n';
}

// ============================================================
// 1. Basic Indexing
// ============================================================

void testBasicIndexing()
{
    CustomArray<int, 5> arr;

    arr[0] = 10;
    arr[1] = 20;
    arr[2] = 30;
    arr[3] = 40;
    arr[4] = 50;

    assert(arr[0] == 10);
    assert(arr[1] == 20);
    assert(arr[2] == 30);
    assert(arr[3] == 40);
    assert(arr[4] == 50);

    printTestPassed("Basic indexing");
}

// ============================================================
// 2. data()
// ============================================================

void testData()
{
    CustomArray<int, 3> arr;

    arr[0] = 10;
    arr[1] = 20;
    arr[2] = 30;

    int* ptr = arr.data();

    assert(ptr != nullptr);
    assert(ptr[0] == 10);
    assert(ptr[1] == 20);
    assert(ptr[2] == 30);

    printTestPassed("data()");
}

// ============================================================
// 3. size() / empty()
// ============================================================

void testSizeAndEmpty()
{
    CustomArray<int, 5> arr;
    CustomArray<int, 0> emptyArray;

    assert(arr.size() == 5);
    assert(!arr.empty());

    assert(emptyArray.size() == 0);
    assert(emptyArray.empty());

    printTestPassed("size() / empty()");
}

// ============================================================
// 4. front() / back()
// ============================================================

void testFrontBack()
{
    CustomArray<int, 5> arr;

    arr[0] = 10;
    arr[4] = 50;

    assert(arr.front() == 10);
    assert(arr.back() == 50);

    arr.front() = 100;
    arr.back() = 500;

    assert(arr[0] == 100);
    assert(arr[4] == 500);

    printTestPassed("front() / back()");
}

// ============================================================
// 5. Const Access
// ============================================================

void testConstAccess()
{
    CustomArray<int, 3> arr;

    arr[0] = 10;
    arr[1] = 20;
    arr[2] = 30;

    const CustomArray<int, 3>& constArr = arr;

    assert(constArr[0] == 10);
    assert(constArr[1] == 20);
    assert(constArr[2] == 30);

    assert(constArr.front() == 10);
    assert(constArr.back() == 30);

    const int* ptr = constArr.data();

    assert(ptr[0] == 10);
    assert(ptr[2] == 30);

    printTestPassed("Const access");
}

// ============================================================
// 6. begin() / end()
// ============================================================

void testIterators()
{
    CustomArray<int, 5> arr;

    arr[0] = 10;
    arr[1] = 20;
    arr[2] = 30;
    arr[3] = 40;
    arr[4] = 50;

    int expected = 10;

    for (auto it = arr.begin(); it != arr.end(); ++it)
    {
        assert(*it == expected);
        expected += 10;
    }

    printTestPassed("begin() / end()");
}

// ============================================================
// 7. cbegin() / cend()
// ============================================================

void testConstIterators()
{
    CustomArray<int, 5> arr;

    arr[0] = 10;
    arr[1] = 20;
    arr[2] = 30;
    arr[3] = 40;
    arr[4] = 50;

    int expected = 10;

    for (auto it = arr.cbegin(); it != arr.cend(); ++it)
    {
        assert(*it == expected);
        expected += 10;
    }

    printTestPassed("cbegin() / cend()");
}

// ============================================================
// 8. Range-Based For
// ============================================================

void testRangeBasedFor()
{
    CustomArray<int, 5> arr;

    arr[0] = 1;
    arr[1] = 2;
    arr[2] = 3;
    arr[3] = 4;
    arr[4] = 5;

    int expected = 1;

    for (const auto& value : arr)
    {
        assert(value == expected);
        ++expected;
    }

    printTestPassed("Range-based for");
}

// ============================================================
// 9. Mutable Range-Based For
// ============================================================

void testMutableRangeBasedFor()
{
    CustomArray<int, 5> arr;

    arr[0] = 1;
    arr[1] = 2;
    arr[2] = 3;
    arr[3] = 4;
    arr[4] = 5;

    for (auto& value : arr)
    {
        value *= 2;
    }

    assert(arr[0] == 2);
    assert(arr[1] == 4);
    assert(arr[2] == 6);
    assert(arr[3] == 8);
    assert(arr[4] == 10);

    printTestPassed("Mutable range-based for");
}

// ============================================================
// 10. at() Valid Access
// ============================================================

void testAtValid()
{
    CustomArray<int, 3> arr;

    arr[0] = 10;
    arr[1] = 20;
    arr[2] = 30;

    assert(arr.at(0) == 10);
    assert(arr.at(1) == 20);
    assert(arr.at(2) == 30);

    arr.at(1) = 200;

    assert(arr[1] == 200);

    printTestPassed("at() valid access");
}

// ============================================================
// 11. at() Bounds Checking
// ============================================================

void testAtInvalid()
{
    CustomArray<int, 3> arr;

    bool exceptionThrown = false;

    try
    {
        arr.at(3);
    }
    catch (const std::out_of_range&)
    {
        exceptionThrown = true;
    }

    assert(exceptionThrown);

    printTestPassed("at() bounds checking");
}

// ============================================================
// 12. fill()
// ============================================================

void testFill()
{
    CustomArray<int, 5> arr;

    arr.fill(42);

    for (const auto& value : arr)
    {
        assert(value == 42);
    }

    printTestPassed("fill()");
}

// ============================================================
// 13. swap()
// ============================================================

void testSwap()
{
    CustomArray<int, 3> first;
    CustomArray<int, 3> second;

    first[0] = 1;
    first[1] = 2;
    first[2] = 3;

    second[0] = 10;
    second[1] = 20;
    second[2] = 30;

    first.swap(second);

    assert(first[0] == 10);
    assert(first[1] == 20);
    assert(first[2] == 30);

    assert(second[0] == 1);
    assert(second[1] == 2);
    assert(second[2] == 3);

    printTestPassed("swap()");
}

// ============================================================
// 14. Equality / Inequality
// ============================================================

void testEquality()
{
    CustomArray<int, 3> first;
    CustomArray<int, 3> second;

    first[0] = 1;
    first[1] = 2;
    first[2] = 3;

    second[0] = 1;
    second[1] = 2;
    second[2] = 3;

    assert(first == second);

    second[1] = 100;

    assert(first != second);

    printTestPassed("operator== / operator!=");
}

// ============================================================
// 15. Copy Construction
// ============================================================

void testCopyConstruction()
{
    CustomArray<int, 3> original;

    original[0] = 10;
    original[1] = 20;
    original[2] = 30;

    CustomArray<int, 3> copy = original;

    assert(copy[0] == 10);
    assert(copy[1] == 20);
    assert(copy[2] == 30);

    copy[0] = 999;

    assert(original[0] == 10);
    assert(copy[0] == 999);

    printTestPassed("Copy construction");
}

// ============================================================
// 16. Copy Assignment
// ============================================================

void testCopyAssignment()
{
    CustomArray<int, 3> source;
    CustomArray<int, 3> destination;

    source[0] = 10;
    source[1] = 20;
    source[2] = 30;

    destination[0] = 1;
    destination[1] = 2;
    destination[2] = 3;

    destination = source;

    assert(destination == source);

    destination[0] = 999;

    assert(source[0] == 10);

    printTestPassed("Copy assignment");
}

// ============================================================
// 17. Move Construction
// ============================================================

void testMoveConstruction()
{
    CustomArray<int, 3> source;

    source[0] = 10;
    source[1] = 20;
    source[2] = 30;

    CustomArray<int, 3> destination = std::move(source);

    assert(destination[0] == 10);
    assert(destination[1] == 20);
    assert(destination[2] == 30);

    printTestPassed("Move construction");
}

// ============================================================
// 18. Move Assignment
// ============================================================

void testMoveAssignment()
{
    CustomArray<int, 3> source;
    CustomArray<int, 3> destination;

    source[0] = 10;
    source[1] = 20;
    source[2] = 30;

    destination[0] = 1;
    destination[1] = 2;
    destination[2] = 3;

    destination = std::move(source);

    assert(destination[0] == 10);
    assert(destination[1] == 20);
    assert(destination[2] == 30);

    printTestPassed("Move assignment");
}

// ============================================================
// 19. Empty Array
// ============================================================

void testEmptyArray()
{
    CustomArray<int, 0> arr;

    assert(arr.size() == 0);
    assert(arr.empty());

    printTestPassed("Empty array");
}

// ============================================================
// 20. Empty Array at()
// ============================================================

void testEmptyArrayAt()
{
    CustomArray<int, 0> arr;

    bool exceptionThrown = false;

    try
    {
        arr.at(0);
    }
    catch (const std::out_of_range&)
    {
        exceptionThrown = true;
    }

    assert(exceptionThrown);

    printTestPassed("Empty array at() bounds checking");
}

// ============================================================
// 21. Empty Array Iterators
// ============================================================

void testEmptyArrayIterators()
{
    CustomArray<int, 0> arr;

    assert(arr.begin() == arr.end());
    assert(arr.cbegin() == arr.cend());

    printTestPassed("Empty array iterators");
}

// ============================================================
// 22. Single Element Array
// ============================================================

void testSingleElementArray()
{
    CustomArray<int, 1> arr;

    arr[0] = 42;

    assert(arr.size() == 1);
    assert(!arr.empty());

    assert(arr.front() == 42);
    assert(arr.back() == 42);

    assert(arr.begin() != arr.end());

    printTestPassed("Single element array");
}

// ============================================================
// 23. Custom Object Storage
// ============================================================

void testCustomObjects()
{
    CustomArray<TestObject, 3> arr;

    arr[0].value = 10;
    arr[1].value = 20;
    arr[2].value = 30;

    assert(arr[0].value == 10);
    assert(arr[1].value == 20);
    assert(arr[2].value == 30);

    printTestPassed("Custom object storage");
}

// ============================================================
// 24. Custom Object Copy
// ============================================================

void testCustomObjectCopy()
{
    CustomArray<TestObject, 3> original;

    original[0].value = 10;
    original[1].value = 20;
    original[2].value = 30;

    CustomArray<TestObject, 3> copy = original;

    assert(copy[0].value == 10);
    assert(copy[1].value == 20);
    assert(copy[2].value == 30);

    copy[0].value = 999;

    assert(original[0].value == 10);

    printTestPassed("Custom object copy");
}

// ============================================================
// 25. Custom Object Move
// ============================================================

void testCustomObjectMove()
{
    CustomArray<TestObject, 3> source;

    source[0].value = 10;
    source[1].value = 20;
    source[2].value = 30;

    CustomArray<TestObject, 3> destination = std::move(source);

    assert(destination[0].value == 10);
    assert(destination[1].value == 20);
    assert(destination[2].value == 30);

    printTestPassed("Custom object move");
}

// ============================================================
// 26. Custom Object fill()
// ============================================================

void testCustomObjectFill()
{
    CustomArray<TestObject, 3> arr;

    TestObject object(100);

    arr.fill(object);

    assert(arr[0].value == 100);
    assert(arr[1].value == 100);
    assert(arr[2].value == 100);

    printTestPassed("Custom object fill");
}

// ============================================================
// 27. Custom Object swap()
// ============================================================

void testCustomObjectSwap()
{
    CustomArray<TestObject, 2> first;
    CustomArray<TestObject, 2> second;

    first[0].value = 10;
    first[1].value = 20;

    second[0].value = 100;
    second[1].value = 200;

    first.swap(second);

    assert(first[0].value == 100);
    assert(first[1].value == 200);

    assert(second[0].value == 10);
    assert(second[1].value == 20);

    printTestPassed("Custom object swap");
}

// ============================================================
// 28. constexpr size()
// ============================================================
void testConstexprSize()
{
    constexpr CustomArray<int, 5> arr{};

    constexpr std::size_t size = arr.size();
    constexpr bool empty = arr.empty();

    static_assert(size == 5);
    static_assert(empty == false);

    assert(size == 5);
    assert(empty == false);

    printTestPassed("constexpr size() / empty()");
}

// ============================================================
// Main Test Runner
// ============================================================

int main()
{
    std::cout << "========================================\n";
    std::cout << "       CustomArray Test Suite\n";
    std::cout << "========================================\n\n";

    testBasicIndexing();
    testData();
    testSizeAndEmpty();
    testFrontBack();
    testConstAccess();

    testIterators();
    testConstIterators();
    testRangeBasedFor();
    testMutableRangeBasedFor();

    testAtValid();
    testAtInvalid();
    testFill();
    testSwap();
    testEquality();

    testCopyConstruction();
    testCopyAssignment();
    testMoveConstruction();
    testMoveAssignment();

    testEmptyArray();
    testEmptyArrayAt();
    testEmptyArrayIterators();
    testSingleElementArray();

    testCustomObjects();
    testCustomObjectCopy();
    testCustomObjectMove();
    testCustomObjectFill();
    testCustomObjectSwap();

    testConstexprSize();

    std::cout << "\n========================================\n";
    std::cout << "All tests passed successfully!\n";
    std::cout << "========================================\n";

    return 0;
}