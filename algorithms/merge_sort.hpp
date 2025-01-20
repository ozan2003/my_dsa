#include <algorithm>
#include <concepts>
#include <iostream>
#include <iterator>
#include <list>
#include <ranges>

namespace rs = std::ranges;

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
template <std::bidirectional_iterator Iter, typename Pred = std::less<>>
    requires std::predicate<Pred,
                            std::iter_value_t<Iter>,
                            std::iter_value_t<Iter>>
             && std::totally_ordered<std::iter_value_t<Iter>>
             //&& std::sortable<Iter, Pred>
void merge_sort(const Iter& begin, const Iter& end, Pred&& pred = Pred{})
{
    if (std::distance(begin, end) <= 1)
    {
        return;
    }

    // Split the range into two halves.
    const auto         mid = std::next(begin, std::distance(begin, end) / 2);
    const rs::subrange left(begin, mid);
    const rs::subrange right(mid, end);

    // Recursively sort the two halves.
    merge_sort(left.begin(), left.end(), pred);
    merge_sort(right.begin(), right.end(), pred);

    // Merge the halves sorted.
    rs::inplace_merge(left.begin(), mid, right.end(), pred);
}

