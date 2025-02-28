#pragma once

#include <algorithm>
#include <concepts>
#include <vector>

template <std::totally_ordered T>
int partition_index(std::vector<T>& vec, int low, const int high);

/**
 * Sort an array using the quicksort algorithm.
 *
 * @param vec The array to be sorted.
 * @param low The starting index of the range.
 * @param high The ending index of the range.
 */
template <std::totally_ordered T>
void quick_sort(std::vector<T>& vec, const int low, const int high)
{
    // Check the indices.
    if (low >= high)
    {
        return;
    }

    // Partition the vector into two parts.
    const int pivot_index = partition_index(vec, low, high);

    // Seperately sort both parts.
    quick_sort(vec, low, pivot_index - 1);
    quick_sort(vec, pivot_index + 1, high);
}

/**
 * Partitions the given sequence so that elements <= pivot are on the left side
 * and elements > pivot are on the right side.
 *
 * @param vec The vector to be partitioned.
 * @param low The starting index of the partition.
 * @param high The ending index of the partition.
 * @return The index of the pivot element.
 */
template <std::totally_ordered T>
int partition_index(std::vector<T>& vec, int low, const int high)
{
    // Using Lomuto partition scheme.
    // Pivot is usually chosen as the last element.
    T& pivot = vec[high];

    // Pivot index.
    int boundary = low - 1;

    for (; low < high; ++low)
    {
        // Move elements <= pivot to the left side.
        if (vec[low] <= pivot)
        {
            ++boundary; // Expand the boundary.
            std::swap(vec[boundary], vec[low]);
        }
    }
    // Place the pivot between two partitions.
    std::swap(vec[boundary + 1], pivot);
    return boundary + 1;
}
