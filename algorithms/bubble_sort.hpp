#pragma once

#include <algorithm>
#include <concepts>
#include <utility>
// #include <vector>
#include <ranges>

/**
 * The bubble sort algorithm.
 * The range will be sorted in-place.
 *
 * @param rng The range to be sorted.
 * @param func The comparison function.
 *             The signature should be equivalent to the following:
 *             bool cmp(const T& a, const T& b);
 */
template <std::ranges::contiguous_range R,
          typename T    = std::ranges::range_value_t<R>,
          typename Pred = std::less<T>>
    requires std::totally_ordered<T> && std::predicate<Pred, const T&, const T&>
void bubble_sort(R& rng, Pred&& pred = Pred{})
{
    // The last element will already be in the correct position.
    auto end = rng.end() - 1;

    // Make the predicate usable for move-only types.
    auto&& predicate = std::forward<Pred>(pred);

    // The comparator fails when end is at the beginning of the vector
    // since there is no element in range [begin, end).
    while (rng.begin() != end)
    {
        // Starting from the beginning, compare every adjacent pair.
        for (auto beg = rng.begin(); beg != end; ++beg)
        {
            // Swap them if they are in the wrong order.
            if (auto next = std::next(beg); !predicate(*beg, *next))
            {
                std::iter_swap(beg, next);
            }
        }
        // The last element is now in the correct position, so we don't need to
        // check it again.
        --end;
    }
}
