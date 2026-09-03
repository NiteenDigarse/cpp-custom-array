
#include <iostream>
#include <stdexcept>
#include <string>

#include <utility>
#include "CustomArray.h"
class Tracker
{
public:
   Tracker()
{
    std::cout << "Tracker: Default Constructor\n";
}

    Tracker(const Tracker&)
    {
        std::cout << "Tracker: Copy Constructor\n";
    }

    Tracker(Tracker&&) noexcept
    {
        std::cout << "Tracker: Move Constructor\n";
    }

    Tracker& operator=(const Tracker&)
    {
        std::cout << "Tracker: Copy Assignment\n";
        return *this;
    }

    Tracker& operator=(Tracker&&) noexcept
    {
        std::cout << "Tracker: Move Assignment\n";
        return *this;
    }
    ~Tracker()
{
    std::cout << "Tracker: Destructor\n";
}
};

int main()
{
    // ============================================================
    // 1. Basic CustomArray Object
    // ============================================================

    CustomArray<int, 5> arr;


    // ============================================================
    // 2. Object Size & Memory Layout
    // ============================================================

    // std::cout << "Size of array object: "
    //           << sizeof(arr) << " bytes\n";

    // std::cout << "Size of one int: "
    //           << sizeof(int) << " bytes\n";


    // ============================================================
    // 3. data() & Array-to-Pointer Decay
    // ============================================================

    // Testing and observing the pointer returned by data()

    // int* ptr = arr.data();

    // std::cout << "Address of first element: "
    //           << ptr << '\n';

    // std::cout << "Address of second element: "
    //           << (ptr + 1) << '\n';

    // std::cout << "Address of third element: "
    //           << (ptr + 2) << '\n';


    // ============================================================
    // 4. operator[] & const operator[]
    // ============================================================

    // arr[2] = 100;

    // const CustomArray<int, 5> const_arr{};

    // std::cout << arr[2] << '\n';
    // std::cout << const_arr[2] << '\n';


    // ============================================================
    // 5. size() & empty()
    // ============================================================

    // std::cout << "Array size: "
    //           << arr.size() << '\n';

    // std::cout << "Array is empty: "
    //           << std::boolalpha
    //           << arr.empty() << '\n';

    // Testing zero-sized CustomArray

    // CustomArray<int, 0> empty_arr;

    // std::cout << "Is empty_arr empty? "
    //           << empty_arr.empty() << '\n';


    // ============================================================
    // 6. Initializing Array Elements
    // ============================================================

    arr[0] = 10;
    arr[1] = 20;
    arr[2] = 100;
    arr[3] = 40;
    arr[4] = 50;

    const CustomArray<int, 5> const_arr{};


    // ============================================================
    // 7. front() & back()
    // ============================================================

    // std::cout << "Front: "
    //           << arr.front() << '\n';

    // std::cout << "Back: "
    //           << arr.back() << '\n';


    // ============================================================
    // 8. const data()
    // ============================================================

    // std::cout << "Const array first element: "
    //           << const_arr.data()[0] << '\n';


    // ============================================================
    // 9. begin() & end() with Iterator-style Loop
    // ============================================================

    std::cout << "Array elements using begin()/end(): ";

    for (auto it = arr.begin(); it != arr.end(); ++it)
    {
        std::cout << *it << ' ';
    }

    std::cout << '\n';


    // ============================================================
    // 10. Range-based for Loop
    // ============================================================

    std::cout << "Array elements using range-based for: ";

    for (const auto& value : arr)
    {
        std::cout << value << ' ';
    }

    std::cout << '\n';


    // ============================================================
    // 11. Modifying Elements through Range-based for
    // ============================================================

    for (auto& value : arr)
    {
        value += 1;
    }

    std::cout << "After modifying each element: ";

    for (const auto& value : arr)
    {
        std::cout << value << ' ';
    }

    std::cout << '\n';


    // ============================================================
    // 12. at() — Bounds-checked Access
    // ============================================================

    try
    {
        // Valid access
        std::cout << "arr.at(2): "
                  << arr.at(2) << '\n';

        // Invalid access — should throw std::out_of_range
        std::cout << "arr.at(5): "
                  << arr.at(5) << '\n';
    }
    catch (const std::out_of_range& e)
    {
        std::cout << "Exception: "
                  << e.what() << '\n';
    }


    // ============================================================
    // 13. fill()
    // ============================================================

    arr.fill(7);

    std::cout << "After fill(7): ";

    for (const auto& value : arr)
    {
        std::cout << value << ' ';
    }

    std::cout << '\n';


    // ============================================================
    // 14. swap()
    // ============================================================

    CustomArray<int, 5> a{};
    CustomArray<int, 5> b{};

    a.fill(10);
    b.fill(20);

    std::cout << "\nBefore swap:\n";

    std::cout << "a: ";
    for (const auto& value : a)
    {
        std::cout << value << ' ';
    }

    std::cout << '\n';

    std::cout << "b: ";
    for (const auto& value : b)
    {
        std::cout << value << ' ';
    }

    std::cout << '\n';

    a.swap(b);

    std::cout << "After swap:\n";

    std::cout << "a: ";
    for (const auto& value : a)
    {
        std::cout << value << ' ';
    }

    std::cout << '\n';

    std::cout << "b: ";
    for (const auto& value : b)
    {
        std::cout << value << ' ';
    }

    std::cout << '\n';


    // ============================================================
    // 15. operator== and operator!=
    // ============================================================

    CustomArray<int, 5> equal_a{};
    CustomArray<int, 5> equal_b{};

    equal_a.fill(10);
    equal_b.fill(10);

    std::cout << std::boolalpha;

    std::cout << "\na == b: "
              << (equal_a == equal_b) << '\n';

    std::cout << "a != b: "
              << (equal_a != equal_b) << '\n';

    // Modify one element
    equal_b[2] = 99;

    std::cout << "\nAfter modifying b:\n";

    std::cout << "a == b: "
              << (equal_a == equal_b) << '\n';

    std::cout << "a != b: "
              << (equal_a != equal_b) << '\n';


    // ============================================================
    // 16. Copy Behavior
    // ============================================================

    CustomArray<int, 5> original{};
    original.fill(10);

    // Compiler-generated copy constructor
    CustomArray<int, 5> copy = original;

    std::cout << "\nBefore modifying copy:\n";

    std::cout << "original[0]: "
              << original[0] << '\n';

    std::cout << "copy[0]: "
              << copy[0] << '\n';

    // Modify copied array
    copy[0] = 99;

    std::cout << "\nAfter modifying copy:\n";

    std::cout << "original[0]: "
              << original[0] << '\n';

    std::cout << "copy[0]: "
              << copy[0] << '\n';


    // ============================================================
    // End
    // ============================================================



    // ============================================================
    // 17. Move Behavior
    // ============================================================

    CustomArray<int, 5> source{};

    source[0] = 10;
    source[1] = 20;
    source[2] = 30;
    source[3] = 40;
    source[4] = 50;

    CustomArray<int, 5> destination = std::move(source);

    std::cout << "\nAfter move:\n";

    std::cout << "source: ";
    for (const auto& value : source)
    {
        std::cout << value << ' ';
    }

    std::cout << '\n';

    std::cout << "destination: ";
    for (const auto& value : destination)
    {
        std::cout << value << ' ';
    }

    std::cout << '\n';


std::cout << "\nSource data address: "
          << static_cast<const void*>(source.data()) << '\n';

std::cout << "Destination data address: "
          << static_cast<const void*>(destination.data()) << '\n';


    // ============================================================
    // 18. Move Behavior with std::string
    // ============================================================

    CustomArray<std::string, 3> string_source{};

    string_source[0] = "Hello";
    string_source[1] = "C++";
    string_source[2] = "Engineering";

    CustomArray<std::string, 3> string_destination =
        std::move(string_source);

    std::cout << "\nAfter moving std::string array:\n";

    std::cout << "Destination: ";

    for (const auto& value : string_destination)
    {
        std::cout << value << ' ';
    }

    std::cout << '\n';

    std::cout << "Source: ";

    for (const auto& value : string_source)
    {
        std::cout << value << ' ';
    }

    std::cout << '\n';


        // ============================================================
    // 19. Copy Constructor — Tracking
    // ============================================================

    CustomArray<Tracker, 3> tracker_source{};

    std::cout << "\nCreating copy:\n";

    CustomArray<Tracker, 3> tracker_copy = tracker_source;

        // ============================================================
    // 20. Move Constructor — Tracking
    // ============================================================

    std::cout << "\nCreating move:\n";

    CustomArray<Tracker, 3> tracker_move =
        std::move(tracker_source);

            // ============================================================
    // 21. Copy Assignment — Tracking
    // ============================================================

    CustomArray<Tracker, 3> assignment_source{};
    CustomArray<Tracker, 3> assignment_destination{};

    std::cout << "\nCopy assignment:\n";

    assignment_destination = assignment_source;

        // ============================================================
    // 22. Move Assignment — Tracking
    // ============================================================

    std::cout << "\nMove assignment:\n";

    assignment_destination = std::move(assignment_source);


    {
    CustomArray<Tracker, 3> lifetime_test;

    std::cout << "\nInside scope\n";
}

std::cout << "Outside scope\n";

    // ============================================================
    // 23. cbegin() / cend()
    // ============================================================

    std::cout << "\nUsing cbegin()/cend(): ";

    for (auto it = arr.cbegin(); it != arr.cend(); ++it)
    {
        std::cout << *it << ' ';
    }

    std::cout << '\n';

    // ============================================================
// 24. constexpr size()
// ============================================================

constexpr CustomArray<int, 5> constexprArr{};

constexpr std::size_t arraySize = constexprArr.size();

static_assert(arraySize == 5);

std::cout << "\nconstexpr size(): " << arraySize << '\n';



// ============================================================
// PHASE 2 — EDGE CASES
// ============================================================

// ------------------------------------------------------------
// 25. Empty CustomArray (N = 0)
// ------------------------------------------------------------

CustomArray<int, 0> emptyArray;

std::cout << "\nEmpty array size: " << emptyArray.size() << '\n';
std::cout << "Empty array empty(): " << std::boolalpha
          << emptyArray.empty() << '\n';

          // ------------------------------------------------------------
// 26. at() on empty array
// ------------------------------------------------------------

try
{
    emptyArray.at(0);
}
catch (const std::out_of_range& error)
{
    std::cout << "Empty array at(0): "
              << error.what() << '\n';
}

// ------------------------------------------------------------
// 27. Iterators on empty array
// ------------------------------------------------------------

std::cout << "Empty array begin == end: "
          << (emptyArray.begin() == emptyArray.end())
          << '\n';

          // ------------------------------------------------------------
// 28. data() on empty array
// ------------------------------------------------------------

auto emptyData = emptyArray.data();

std::cout << "Empty array data(): "
          << static_cast<const void*>(emptyData) << '\n';

          // ------------------------------------------------------------
// 29. Minimum non-empty array (N = 1)
// ------------------------------------------------------------

CustomArray<int, 1> singleArray;

singleArray[0] = 42;

std::cout << "Single element array: "
          << singleArray.front() << ' '
          << singleArray.back() << '\n';

std::cout << "Single element begin == end: "
          << (singleArray.begin() == singleArray.end())
          << '\n';

          // ------------------------------------------------------------
// 30. Boundary index test
// ------------------------------------------------------------

std::cout << "singleArray[0]: "
          << singleArray[0] << '\n';

try
{
    singleArray.at(1);
}
catch (const std::out_of_range& error)
{
    std::cout << "singleArray.at(1): "
              << error.what() << '\n';
}

// ------------------------------------------------------------
// PHASE 3 — TYPE & LIFETIME TESTING
// ------------------------------------------------------------

// 31. Custom objects inside CustomArray

CustomArray<Tracker, 3> trackerArray;

std::cout << "Tracker array created.\n";
trackerArray[0] = Tracker{};
trackerArray[1] = Tracker{};
trackerArray[2] = Tracker{};

// ============================================================
// PHASE 3 — TYPE & LIFETIME TESTING
// ============================================================

// ------------------------------------------------------------
// 31. Custom objects inside CustomArray
// ------------------------------------------------------------

std::cout << "\n===== Phase 3: Type & Lifetime Testing =====\n";

{
    std::cout << "\n[31] Creating CustomArray<Tracker, 3>\n";

    CustomArray<Tracker, 3> trackerArray;

    std::cout << "Tracker array created.\n";
}


// ------------------------------------------------------------
// 32. Individual element access
// ------------------------------------------------------------

{
    std::cout << "\n[32] Individual Tracker element access\n";

    CustomArray<Tracker, 3> trackerArray;

    Tracker& first = trackerArray[0];
    Tracker& second = trackerArray[1];
    Tracker& third = trackerArray[2];

    (void)first;
    (void)second;
    (void)third;

    std::cout << "Three Tracker elements accessed.\n";
}


// ------------------------------------------------------------
// 33. Copy construction
// ------------------------------------------------------------

{
    std::cout << "\n[33] Copy construction\n";

    CustomArray<Tracker, 3> original;

    std::cout << "Creating copy...\n";

    CustomArray<Tracker, 3> copy = original;

    (void)copy;
}


// ------------------------------------------------------------
// 34. Move construction
// ------------------------------------------------------------

{
    std::cout << "\n[34] Move construction\n";

    CustomArray<Tracker, 3> source;

    std::cout << "Creating moved array...\n";

    CustomArray<Tracker, 3> destination = std::move(source);

    (void)destination;
}


// ------------------------------------------------------------
// 35. Copy assignment
// ------------------------------------------------------------

{
    std::cout << "\n[35] Copy assignment\n";

    CustomArray<Tracker, 3> source;
    CustomArray<Tracker, 3> destination;

    std::cout << "Performing copy assignment...\n";

    destination = source;
}


// ------------------------------------------------------------
// 36. Move assignment
// ------------------------------------------------------------

{
    std::cout << "\n[36] Move assignment\n";

    CustomArray<Tracker, 3> source;
    CustomArray<Tracker, 3> destination;

    std::cout << "Performing move assignment...\n";

    destination = std::move(source);
}


// ------------------------------------------------------------
// 37. Object lifetime / destruction
// ------------------------------------------------------------

{
    std::cout << "\n[37] Object lifetime test\n";

    {
        CustomArray<Tracker, 3> scopedArray;

        std::cout << "Inside scope\n";
    }

    std::cout << "Outside scope\n";
}


// ------------------------------------------------------------
// 38. Range-based for with custom objects
// ------------------------------------------------------------

{
    std::cout << "\n[38] Range-based for with Tracker objects\n";

    CustomArray<Tracker, 3> trackerArray;

    for (const auto& tracker : trackerArray)
    {
        (void)tracker;
    }

    std::cout << "Range-based iteration completed.\n";
}


// ------------------------------------------------------------
// 39. Const CustomArray with custom objects
// ------------------------------------------------------------

{
    std::cout << "\n[39] Const CustomArray with Tracker objects\n";

    const CustomArray<Tracker, 3> trackerArray;

    const Tracker& first = trackerArray[0];

    (void)first;

    std::cout << "Const access completed.\n";
}


// ------------------------------------------------------------
// 40. Custom object fill()
// ------------------------------------------------------------

{
    std::cout << "\n[40] fill() with Tracker objects\n";

    CustomArray<Tracker, 3> trackerArray;

    Tracker tracker;

    trackerArray.fill(tracker);

    std::cout << "Tracker array filled.\n";
}


// ------------------------------------------------------------
// 41. Custom object swap()
// ------------------------------------------------------------

{
    std::cout << "\n[41] swap() with Tracker objects\n";

    CustomArray<Tracker, 3> first;
    CustomArray<Tracker, 3> second;

    first.swap(second);

    std::cout << "Tracker arrays swapped.\n";
}
    return 0;
}

