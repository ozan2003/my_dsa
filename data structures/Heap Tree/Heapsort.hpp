#ifndef HEAPSORT_HPP
#define HEAPSORT_HPP

#include <algorithm>
#include <vector>

/*
 * For any element at index i:
 * 1. The parent is at index i / 2 for 1-based indexing, or (i-1) / 2 for
 * 0-based.
 * 2. The left child is at index 2 * i for 1-based, or 2 * i + 1 for 0-based.
 * 3. The right child is at index 2 * i + 1 for 1-based, or 2 * i + 2 for
 * 0-based.
 */

namespace
{
    /**
     * @brief Returns the index of the parent of the element at the given index.
     *
     * @param index The index of the element.
     * @return The index of the parent.
     */
    [[nodiscard]]
    constexpr std::size_t parent(const std::size_t index) noexcept
    {
        return (index - 1) / 2; // 0-based indexing
    }

    /**
     * @brief Returns the index of the left child of the element at the given
     * index.
     *
     * @param index The index of the element.
     * @return The index of the left child.
     */
    [[nodiscard]]
    constexpr std::size_t left(const std::size_t index) noexcept
    {
        return 2 * index + 1; // 0-based indexing
    }

    /**
     * @brief Returns the index of the right child of the element at the given
     * index.
     *
     * @param index The index of the element.
     * @return The index of the right child.
     */
    [[nodiscard]]
    constexpr std::size_t right(const std::size_t index) noexcept
    {
        return left(index) + 1; // 0-based indexing
    }

    /**
     * @brief Moves down the item at the given hole index until the heap
     * property is restored.
     *
     * @param items The vector of elements.
     * @param hole The index of the element to be percolated down.
     * @param end The index of the last element in the vector.
     * @tparam T The type of elements in the vector.
     */
    template <typename T>
    void percolate_down(std::vector<T>&   items,
                        std::size_t       hole,
                        const std::size_t end) noexcept
    {
        // The value being percolated down
        T           percolating_value = std::move(items[hole]);
        std::size_t child{};

        // Percolate down the hole
        while (left(hole) < end)
        {
            child = left(hole); // The index of the left child

            // If the right child exists and is larger than the left child,
            // then use the right child (for max-heap)
            if (right(hole) < end && items[child] < items[right(hole)])
            {
                child = right(hole);
            }

            // If the child is larger than the item being percolated down,
            // then move the child up
            if (items[child] > percolating_value)
            {
                items[hole] = std::move(items[child]);
            }
            else
            {
                break;
            }

            hole = child; // Move to the child
        }

        // Move the item into the final hole position
        items[hole] = std::move(percolating_value);
    }

    /**
     * @brief Builds a max heap from the given vector of elements.
     *
     * @param items The vector of elements to be heapified.
     * @tparam T The type of elements in the vector.
     */
    template <typename T>
    void build_heap(std::vector<T>& items) noexcept
    {
        const std::size_t size = items.size();

        // Handle empty vector case
        if (size == 0)
        {
            return;
        }

        // Start from the last parent
        for (int i = static_cast<int>(parent(size - 1)); i >= 0; --i)
        {
            percolate_down(items, i, size);
        }
    }
} // namespace

/**
 * @brief Sorts the elements in-place using the heap sort algorithm.
 *
 * @param items The vector of elements to be sorted.
 * @tparam T The type of elements in the vector.
 */
template <typename T>
void heap_sort(std::vector<T>& items)
{
    if (items.size() <= 1)
    {
        return; // Already sorted
    }

    // Build a max heap first
    build_heap(items);

    // Sort the elements
    for (std::size_t end = items.size() - 1; end > 0; --end)
    {
        // Move the largest element (root) to the end
        std::swap(items[0], items[end]);

        // Restore heap property for the remaining elements
        percolate_down(items, 0, end);
    }
}

#endif // HEAPSORT_HPP
