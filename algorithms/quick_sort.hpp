#pragma once

#include <algorithm>
#include <concepts>
#include <vector>

template <std::totally_ordered T>
int partition_index(std::vector<T>&   vec,
                            const int low,
                            const int high);

/**
 * Sort an array using the quicksort algorithm.
 *
 * @param vec The array to be sorted.
 * @param low The starting index of the range.
 * @param high The ending index of the range.
 */
template <std::totally_ordered T>
void quick_sort(std::vector<T>&   vec,
                const int low,
                const int high)
{
    // Check the indices.
    if (low >= high)
    {
        return;
    }

    // Partition the vector into two parts.
    const auto pivot = partition_index(vec, low, high);

    // Seperately sort elements before and after pivot.
    quick_sort(vec, low, pivot - 1);
    quick_sort(vec, pivot + 1, high);
}

/**
 * Partitions the given sequence so that elements <= pivot are on the left side
 * and elements > pivot are on the right side.
 *
 * @param vec The vector to be partitioned.
 * @param low The starting index of the partition.
 * @param high The ending index of the partition.
 * @return The index of the pivot element after partitioning.
 */
template <std::totally_ordered T>
int partition_index(std::vector<T>&   vec,
                            const int low,
                            const int high)
{
    // Pivot is usually chosen as the last element.
    const T pivot = vec[high];

    // Pivot index.
    int i = low - 1;

    for (int j{low}; j < high; ++j)
    {
        // If the current element is less than or equal to the pivot.
        if (vec[j] <= pivot)
        {
            ++i;
            std::swap(vec[i], vec[j]); // Swap the elements.
        }
    }
    // Move the pivot element to the correct position (between the smaller and
    // the larger elements).
    ++i;
    std::swap(vec[i], vec[high]);

    return i;
}
