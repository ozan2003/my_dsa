#include "fmt/ranges.h"

#include <algorithm>
#include <vector>
#include <random>
#include <concepts>

const auto seed = std::random_device{}();

const auto rnd = [gen = std::mt19937{seed}, dist = std::uniform_int_distribution{-40, 40}]() mutable -> int
{
    return dist(gen);
};

template <typename T>
concept Comparable = requires(T a, T b) {
    {
        a < b
    } -> std::convertible_to<bool>;
};

/**
 * Sorts the elements in-place using the insertion sort algorithm.
 *
 * @param vec The vector to be sorted.
 */
template <Comparable T>
void insertion_sort(std::vector<T>& vec)
{
    // Go left to right.
    for (auto curr = std::next(vec.begin()); curr != vec.end(); ++curr)
    {
        // Check each element and compare it to the elements to its left.
        // Track our previous element in case we need to swap.
        for (auto prev = curr; prev != vec.begin(); --prev)
        {
            // Move prev to the left until it's less than the element to its
            // left.
            if (*prev < *(prev - 1))
            {
                std::iter_swap(prev, prev - 1);
            }
        }
    }
}

int main()
{
    std::vector<int> vec(10);
    std::generate(vec.begin(), vec.end(), rnd);

    fmt::println("Before: {}", vec);
    insertion_sort(vec);
    fmt::println("After:  {}", vec);
}