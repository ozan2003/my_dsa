#pragma once

#include <algorithm>
#include <concepts>
#include <iterator>
#include <ranges>

/**
 * The merge sort algorithm.
 * The range will be sorted in-place.
 *
 * @param begin The begin iterator of the range.
 * @param end The end iterator of the range.
 * @param pred The predicate to use for comparison.
 *             Defaults to std::less<>. For custom types, you can provide
 *             your own predicate, its signature should be equivalent to
 *            `bool pred(const T&, const T&)`.
 */
template <std::bidirectional_iterator Iter,
          typename T    = std::iter_value_t<Iter>,
          typename Pred = std::less<T>>
    requires std::predicate<Pred, T, T> && std::totally_ordered<T>
void merge_sort(const Iter& begin, const Iter& end, Pred&& pred = Pred{})
{
    if (std::distance(begin, end) <= 1)
    {
        return;
    }

    // Split the range into two halves.
    const auto         mid = std::next(begin, std::distance(begin, end) / 2);
    const std::ranges::subrange left(begin, mid);
    const std::ranges::subrange right(mid, end);

    // Recursively sort the two halves.
    merge_sort(left.begin(), left.end(), pred);
    merge_sort(right.begin(), right.end(), pred);

    // Merge the halves sorted.
    std::ranges::inplace_merge(left.begin(), mid, right.end(), pred);
}
