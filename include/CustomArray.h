#pragma once

#include <cstddef>
#include <stdexcept>

template <typename T, std::size_t N>
class CustomArray
{
private:
    T data_[N];

public:
    // ========================================================
    // Element Access
    // ========================================================

    // Unchecked element access.
    T& operator[](std::size_t index)
    {
        return data_[index];
    }

    // Const overload of operator[].
    const T& operator[](std::size_t index) const
    {
        return data_[index];
    }

    // Bounds-checked element access.
    T& at(std::size_t index)
    {
        if (index >= N)
        {
            throw std::out_of_range(
                "CustomArray::at() index out of range"
            );
        }

        return data_[index];
    }

    // Const overload of at().
    const T& at(std::size_t index) const
    {
        if (index >= N)
        {
            throw std::out_of_range(
                "CustomArray::at() index out of range"
            );
        }

        return data_[index];
    }

    // Returns pointer to the first element.
    T* data()
    {
        return data_;
    }

    // Const overload of data().
    const T* data() const
    {
        return data_;
    }

    // Returns the first element.
    T& front()
    {
        return data_[0];
    }

    // Returns the last element.
    T& back()
    {
        return data_[N - 1];
    }

    // Const overload of front().
    const T& front() const
    {
        return data_[0];
    }

    // Const overload of back().
    const T& back() const
    {
        return data_[N - 1];
    }

    // ========================================================
    // Capacity
    // ========================================================

    // Returns the compile-time number of elements.
    constexpr std::size_t size() const
    {
        return N;
    }

    // Returns true when the array contains zero elements.
    constexpr bool empty() const
    {
        return N == 0;
    }

    // ========================================================
    // Iterators
    // ========================================================

    // Iterator to the first element.
    T* begin()
    {
        return data_;
    }

    // Iterator one position past the last element.
    T* end()
    {
        return data_ + N;
    }

    // Const iterator to the first element.
    const T* begin() const
    {
        return data_;
    }

    // Const iterator one position past the last element.
    const T* end() const
    {
        return data_ + N;
    }

    // Always returns a const iterator.
    const T* cbegin() const
    {
        return data_;
    }

    // Always returns a const iterator one position past the end.
    const T* cend() const
    {
        return data_ + N;
    }

    // ========================================================
    // Modifiers
    // ========================================================

    // Assigns the same value to every element.
    void fill(const T& value)
    {
        for (std::size_t index = 0; index < N; ++index)
        {
            data_[index] = value;
        }
    }

    // Exchanges elements with another CustomArray.
    void swap(CustomArray& other)
    {
        for (std::size_t index = 0; index < N; ++index)
        {
            T temp = data_[index];

            data_[index] = other.data_[index];
            other.data_[index] = temp;
        }
    }

    // ========================================================
    // Comparison
    // ========================================================

    // Compares two arrays element by element.
    bool operator==(const CustomArray& other) const
    {
        for (std::size_t index = 0; index < N; ++index)
        {
            if (data_[index] != other.data_[index])
            {
                return false;
            }
        }

        return true;
    }

    // Returns true when the arrays are different.
    bool operator!=(const CustomArray& other) const
    {
        return !(*this == other);
    }
};