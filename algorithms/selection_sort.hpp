#pragma once

#include <algorithm> // std::min_element, std::iter_swap
#include <concepts>  // std::totally_ordered, std::predicate
#include <ranges>  // std::ranges::contiguous_range, std::ranges::range_value_t
#include <utility> // std::forward

/**
 * Sorts the elements in-place using the selection sort algorithm.
 * Note that since it has O(n^2) time complexity, it's not suitable for large
 * containers.
 *
 * @param seq The sequence to be sorted.
 */
template <std::ranges::contiguous_range R,
          typename T                = std::ranges::range_value_t<R>,
          std::predicate<T, T> Pred = std::less<T>>
void selection_sort(R& seq, Pred&& pred = Pred{})
{
    // 1. Start from the beginning of the sequence.
    // 2. Find the smallest element in the range [front, seq.end()).
    // 3. Swap the smallest element with the first element in the range.
    // 4. Move the front pointer to the next element.
    // 5. Repeat the process until the front pointer reaches the end of the
    //    sequence.
    // There's no need to look at the last element since the last comparison
    // always with itself.
    for (auto front = seq.begin(); front < seq.end() - 1; ++front)
    {
        // Find the smallest element in the range [front++, seq.end()).
        auto min_item = std::ranges::min_element(front,
                                                 seq.end(),
                                                 std::forward<Pred>(pred));
        // Swap the smallest element with the first element in the range
        // [front++, seq.end()) through iterators.
        std::iter_swap(min_item, front);
    }
}
