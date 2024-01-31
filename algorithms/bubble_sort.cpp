#include "fmt/ranges.h"

#include <algorithm>
#include <vector>

/**
 * The bubble sort algorithm.
 * The container will be sorted in-place.
 * 
 * @param vec The vector to be sorted.
 */
void bubble_sort(std::vector<int>& vec)
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
    std::vector<int> vec{6, 5, 3, 1, 8, 2, 4, 7};
    bubble_sort(vec);
    fmt::println("{}", vec);
}