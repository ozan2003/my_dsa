#include "fmt/ranges.h"

#include <algorithm>
#include <concepts>
#include <vector>

template <typename T>
concept Comparable = requires(T a, T b) {
    {
        a < b
    } -> std::convertible_to<bool>;
};

/**
 * The bubble sort algorithm.
 * The container will be sorted in-place.
 *
 * @param vec The vector to be sorted.
 */
template <Comparable T>
void bubble_sort(std::vector<T>& vec)
{
    // The last element will already in the correct position.
    auto end = vec.end() - 1ull; // - 1 for not getting segfault comparing one next item.

    while (!std::is_sorted(vec.begin(), vec.end()))
    {
        // Starting from the beginning, compare every adjacent pair.
        for (auto beg = vec.begin(); beg != end; ++beg)
        {
            // Swap them if they are in the wrong order.
            if (*beg > *(beg + 1))
            {
                std::iter_swap(beg, beg + 1);
            }
        }
        // The last element is now in the correct position, so we don't need to
        // check it again.
        --end;
    }
}

int main()
{
    std::vector<int> vec{7, 5, 3, 5, 8, 6, 3, 1};
    bubble_sort(vec);
    fmt::println("After bubble sort: {}", vec);
}