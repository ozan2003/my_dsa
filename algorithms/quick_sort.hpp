#pragma once

#include <algorithm>
#include <vector>
#include <concepts>

template <typename T>
concept Comparable = requires(T a, T b) {
    {
        a < b
    } -> std::convertible_to<bool>;
};

template <Comparable T>
int partition(std::vector<T>& vec, const int low, const int high);

/**
 * Sorts a vector of integers using the quicksort algorithm.
 *
 * @param vec The vector to be sorted.
 * @param low The starting index of the range.
 * @param high The ending index of the range.
 */
template <Comparable T>
void quick_sort(std::vector<T>& vec, const int low, const int high)
{
    // Check the indices.
    if (low >= high)
    {
        return;
    }

    // Partition the vector into two parts.
    const auto pivot = partition(vec, low, high);

    quick_sort(vec, low, pivot - 1);  // Sort the left part.
    quick_sort(vec, pivot + 1, high); // Sort the right part.
}

/**
 * Partitions the given vector around a pivot element.
 *
 * @param vec The vector to be partitioned.
 * @param low The starting index of the partition.
 * @param high The ending index of the partition.
 * @return The index of the pivot element after partitioning.
 */
template <Comparable T>
int partition(std::vector<T>& vec, const int low, const int high)
{
    // Choose the last element as the pivot.
    const int pivot = vec[high];

    // Temporary pivot index.
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
    // Move the pivot element to the correct position (between the smaller and the larger elements).
    ++i;
    std::swap(vec[i], vec[high]);

    return i; // The pivot index.
}
