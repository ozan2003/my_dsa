#pragma once

#include <algorithm>
#include <concepts>
#include <utility>
#include <vector>

/**
 * Sorts the elements in-place using the insertion sort algorithm.
 *
 * @param vec The vector to be sorted.
 */
template <std::totally_ordered T, std::predicate<T, T> Pred = std::less<T>>
void insertion_sort(std::vector<T>& vec, Pred&& pred = Pred{})
{
    // Create a forwarding reference to prevent repetitve forwarding in loop to
    // reduce overhead.
    auto&& predicate = std::forward<Pred>(pred);

    // Go left to right.
    for (auto curr = std::next(vec.begin()); curr != vec.end(); ++curr)
    {
        // Check each element and compare it to the elements to its left.
        // Track our previous element in case we need to swap.
        for (auto prev = curr; prev != vec.begin(); --prev)
        {
            // Move prev to the left until it satisfies the predicate.
            if (predicate(*prev, *std::prev(prev)))
            {
                std::iter_swap(prev, std::prev(prev));
            }
        }
    }
}
