#pragma once

#include <algorithm>
#include <concepts>
#include <vector>

template <std::ranges::random_access_range R,
          typename T = std::ranges::range_value_t<R>>
    requires std::totally_ordered<T>
int partition_index(R& seq, int low, const int high);

/**
 * Sort an range using the quicksort algorithm.
 *
 * @param seq The range to be sorted.
 * @param low The starting index of the range.
 * @param high The ending index of the range.
 */
template <std::ranges::random_access_range R,
          typename T = std::ranges::range_value_t<R>>
    requires std::totally_ordered<T>
void quick_sort(R& seq, const int low, const int high)
{
    // Check the indices.
    if (low >= high)
    {
        return;
    }

    // Partition the vector into two parts.
    const int pivot_index = partition_index(seq, low, high);

    // Seperately sort both parts.
    quick_sort(seq, low, pivot_index - 1);
    quick_sort(seq, pivot_index + 1, high);
}

// A convenient overload for the whole range.
/**
 * Sort an range using the quicksort algorithm.
 *
 * @param vec The range to be sorted.
 */
template <std::ranges::random_access_range R>
void quick_sort(R& seq)
{
    if (!std::ranges::empty(seq))
    {
        quick_sort(seq, 0, static_cast<int>(std::size(seq) - 1));
    }
}

/**
 * Partitions the given sequence so that elements <= pivot are on the left side
 * and elements > pivot are on the right side.
 *
 * @param seq The vector to be partitioned.
 * @param low The starting index of the partition.
 * @param high The ending index of the partition.
 * @return The index of the pivot element.
 */
template <std::ranges::random_access_range R, typename T>
    requires std::totally_ordered<T>
int partition_index(R& seq, int low, const int high)
{
    // Using Lomuto partition scheme.
    // Pivot is usually chosen as the last element.
    T pivot = seq[high];

    // Pivot index.
    int boundary = low - 1;

    for (; low < high; ++low)
    {
        // Move elements <= pivot to the left side.
        if (seq[low] <= pivot)
        {
            ++boundary; // Expand the boundary.
            std::swap(seq[boundary], seq[low]);
        }
    }
    // Place the pivot between two partitions.
    std::swap(seq[boundary + 1], pivot);
    return boundary + 1;
}
