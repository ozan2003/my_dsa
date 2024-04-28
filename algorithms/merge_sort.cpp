#include <algorithm>
#include <iostream>
#include <list>
#include <ranges>
#include <iterator>

/**
 * The merge sort algorithm.
 * The range will be sorted in-place.
 *
 * @param begin The begin iterator of the range.
 * @param end The end iterator of the range.
 */
template <std::bidirectional_iterator Iter>
void merge_sort(const Iter& begin, const Iter& end)
{
    if (std::distance(begin, end) <= 1)
    {
        return;
    }

    // Split the range into two halves.
    const auto mid = std::next(begin, std::distance(begin, end) / 2);
    const std::ranges::subrange left(begin, mid);
    const std::ranges::subrange right(mid, end);

    // Recursively sort the two halves.
    merge_sort(left.begin(), left.end());
    merge_sort(right.begin(), right.end());

    // Merge the halves sorted.
    std::ranges::inplace_merge(left.begin(), mid, right.end());
}

int main()
{
    std::list nums{3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};

    merge_sort(nums.begin(), nums.end());

    for (const auto& item : nums)
    {
        std::cout << item << ' ';
    }
    std::cout << '\n';
}