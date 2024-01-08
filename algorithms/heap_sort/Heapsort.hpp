#ifndef HEAPSORT_HPP
#define HEAPSORT_HPP

#include <algorithm>
#include <vector>

/*
 * For any element at index index:
 * 1. The parent is at index index / 2.
 * 2. The left child is at index 2 * index.
 * 3. The right child is at index 2 * index + 1.
 * 4. The last parent is at index n / 2.
 */

/**
 * @brief Returns the index of the parent of the element at the given index.
 */
constexpr std::size_t parent(const std::size_t index)
{
    return index / 2;
}

/**
 * @brief Returns the index of the left child of the element at the given index.
 */
constexpr std::size_t left_child(const std::size_t index)
{
    return 2 * index;
}

/**
 * @brief Returns the index of the right child of the element at the given index.
 */
constexpr std::size_t right_child(const std::size_t index)
{
    return 2 * index + 1;
}

/**
 * Sifts down the element at the given index in the given vector of elements.
 *
 * @param items The vector of elements.
 * @param index The index of the element to be percolated down.
 * @param end The index of the last element in the vector.
 * @tparam T The type of elements in the vector.
 */
template <typename T>
void sift_down(std::vector<T>& items, const std::size_t index, const std::size_t end)
{
    const auto left{left_child(index)};   // Left child.
    const auto right{right_child(index)}; // Right child.
    auto       largest{index};            // Largest element.

    // Find the largest element among the parent, left child, and right child.
    if (left < end && items[left] > items[largest])
    {
        largest = left;
    }

    if (right < end && items[right] > items[largest])
    {
        largest = right;
    }

    // If the largest element is not the parent itself, swap the parent with the largest element.
    if (largest != index)
    {
        std::swap(items[index], items[largest]);
        sift_down(items, largest, end); // Call recursively on the largest element's index.
    }
}

/**
 * Builds a max heap from the given vector of elements.
 *
 * @param items The vector of elements to be heapified.
 * @tparam T The type of elements in the vector.
 */
template <typename T>
void heapify(std::vector<T>& items)
{
    // Build a max heap first by repeatedly percolating down.
    // Convert index to int to avoid underflow.
    for (int index{static_cast<int>(items.size() / 2)}; 0 <= index; --index)
    {
        sift_down(items, index, items.size()); // Percolate down from the parent.
    }
}

/**
 * Sorts the elements in-place using the heap sort algorithm.
 *
 * @param items The vector of elements to be sorted.
 * @tparam T The type of elements in the vector.
 */
template <typename T>
void heap_sort(std::vector<T>& items)
{
    heapify(items); // Build a max heap first.

    // Sort the elements.
    for (int end{static_cast<int>(items.size() - 1ull)}; 0 <= end; --end)
    {
        std::swap(items[0], items[end]); // Move the largest element to the end.
        // By decreasing the end index, we are effectively removing the last element from the heap,
        // considering it sorted.
        sift_down(items, 0, end); // Heap order is broken, so restore it.
    }
}
#endif // HEAPSORT_HPP
