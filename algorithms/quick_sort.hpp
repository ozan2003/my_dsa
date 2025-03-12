#pragma once

#include <algorithm>
#include <concepts>
#include <ranges>

namespace impl
{
    enum class Partition
    {
        Lomuto,
        Hoare
    };

    /**
     * Partitions the given sequence so that elements <= pivot are on the left
     * side and elements > pivot are on the right side.
     *
     * This function uses the Lomuto partition scheme.
     *
     * @param seq The range to be partitioned.
     * @param low The starting index of the partition.
     * @param high The ending index of the partition.
     * @return The index of the pivot element.
     */
    template <std::ranges::random_access_range R,
              typename T = std::ranges::range_value_t<R>>
        requires std::totally_ordered<T>
    int partition_index_lomuto(R& seq, int low, const int high)
    {
        // Using Lomuto partition scheme.
        // Pivot is usually chosen as the last element.
        T& pivot = seq[high];

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

    /**
     * Partitions the given sequence so that elements <= pivot are on the left
     * side and elements > pivot are on the right side.
     *
     * This function uses the Hoare partition scheme.
     *
     * @param seq The range to be partitioned.
     * @param low The starting index of the partition.
     * @param high The ending index of the partition.
     * @return The index of the pivot element.
     */
    template <std::ranges::random_access_range R,
              typename T = std::ranges::range_value_t<R>>
        requires std::totally_ordered<T>
    int partition_index_hoare(R& seq, const int low, const int high)
    {
        T pivot = seq[low]; // Pivot doesn't have to be the last element.

        int lower_boundary  = low - 1;  // index of element <= pivot.
        int higher_boundary = high + 1; // index of element > pivot.

        while (true)
        {
            // Find the first element >= pivot from the left.
            do
            {
                ++lower_boundary;
            } while (seq[lower_boundary] < pivot);

            // Find the first element <= pivot from the right.
            do
            {
                --higher_boundary;
            } while (seq[higher_boundary] > pivot);

            // If the boundaries meet, return higher_boundary as
            // the index of the pivot-value element or
            // the index of the closest lower than the pivot element.
            if (lower_boundary >= higher_boundary)
            {
                return higher_boundary;
            }
            else
            {
                std::swap(seq[lower_boundary], seq[higher_boundary]);
            }
        }
    }
} // namespace impl

using namespace impl;

/**
 * Sort an range using the quicksort algorithm.
 *
 * @param seq The range to be sorted.
 * @param low The starting index of the range.
 * @param high The ending index of the range.
 * @param partition The partition scheme to be used. Default is Hoare.
 */
template <std::ranges::random_access_range R,
          typename T = std::ranges::range_value_t<R>>
    requires std::totally_ordered<T>
void quick_sort(R&                    seq,
                const int             low,
                const int             high,
                const Partition partition = Partition::Hoare)
{
    // Check the indices.
    if (low >= high)
    {
        return;
    }

    // Partition the range into two parts.
    // const int pivot_index = partition_index_hoare(seq, low, high);
    const int pivot_index = (partition == Partition::Lomuto)
                                ? partition_index_lomuto(seq, low, high)
                                : partition_index_hoare(seq, low, high);

    // Seperately sort both parts.
    quick_sort(seq, low, pivot_index);
    quick_sort(seq, pivot_index + 1, high);
}

// A convenient overload for the whole range.
/**
 * Sort an range using the quicksort algorithm.
 *
 * @param seq The range to be sorted.
 * @param partition The partition scheme to be used. Default is Hoare.
 */
template <std::ranges::random_access_range R>
void quick_sort(R&                    seq,
                const Partition partition = Partition::Hoare)
{
    if (!std::ranges::empty(seq))
    {
        quick_sort(seq, 0, static_cast<int>(std::size(seq) - 1), partition);
    }
}
