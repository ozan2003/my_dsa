#ifndef HEAPTREE_HPP
#define HEAPTREE_HPP

#include <initializer_list> // std::initializer_list
#include <iostream>         // operator<<
#include <ranges>           // std::ranges::range
#include <stdexcept>        // std::out_of_range
#include <utility>          // std::move
#include <vector>           // std::vector

/*
 * For any element at index i:
 * 1. The parent is at index i / 2.
 * 2. The left child is at index 2 * i.
 * 3. The right child is at index 2 * i + 1.
 * 4. The last parent is at index n / 2.
 */

namespace
{
    // The initial capacity of the array.
    constexpr std::size_t INITIAL_CAPACITY{10};
} // namespace

// Implemented as a min-heap.
template <typename T>
class HeapTree
{
public:
    using value_type      = T;
    using size_type       = std::size_t;
    using reference       = T&;
    using const_reference = const T&;
    using pointer         = T*;
    using const_pointer   = const T*;

private:
    size_type               m_size{}; // The number of items in the heap.
    std::vector<value_type> m_data;   // The array that stores the items.

    /**
     * @brief Returns the parent of the given index.
     *
     * @param i The index of the element.
     * @return The parent of the given index.
     */
    [[nodiscard]]
    constexpr size_type parent(const size_type i) const noexcept
    {
        return i / 2;
    }

    /**
     * @brief Returns the left child of the given index.
     *
     * @param i The index of the element.
     * @return The left child of the given index.
     */
    [[nodiscard]]
    constexpr size_type left(const size_type i) const noexcept
    {
        return 2 * i;
    }

    /**
     * @brief Returns the right child of the given index.
     *
     * @param i The index of the element.
     * @return The right child of the given index.
     */
    [[nodiscard]]
    constexpr size_type right(const size_type i) const noexcept
    {
        return 2 * i + 1;
    }

    /**
     * @brief Builds the heap by percolating down the parent nodes.
     *
     * This function starts from the last parent node and percolates down each
     * parent node to maintain the heap property.
     *
     * @note This function assumes that the heap is already initialized.
     */
    void build_heap() noexcept
    {
        // Start from the last parent.
        for (size_type i{parent(m_size)}; i > 0; --i)
        {
            percolate_down(i); // Percolate down the parent.
        }
    }

    /**
     * @brief Moves down the item at the given hole index until the heap
     * property is restored.
     *
     * @param hole The index of the hole to percolate down from.
     *
     * @note Also called "sift down" and "bubble down".
     */
    void percolate_down(size_type hole) noexcept
    {
        size_type child{}; // The index of the child of the hole.
        // The item that will be percolated down.
        value_type percolating_value = std::move(m_data[hole]);

        // Percolate down the hole.
        while (left(hole) <= m_size)
        {
            child = left(hole); // The index of the left child.

            // If the right child exists and is smaller than the left child,
            // then use the right child.
            if (child < m_size && (m_data[right(hole)] < m_data[child]))
            {
                child = right(hole);
            }

            // If the child is smaller than the item that is percolated down,
            // then move the child up.
            if (m_data[child] < percolating_value)
            {
                m_data[hole] = std::move(m_data[child]);
            }
            else
            {
                break;
            }

            hole = child; // Move to the child.
        }
        // Move the item into the hole.
        m_data[hole] = std::move(percolating_value);
    }

public:
    /**
     * @brief Constructs an empty heap with the given initial capacity.
     *
     * @param capacity The initial capacity of the heap.
     */
    explicit HeapTree(const size_type capacity = INITIAL_CAPACITY)
        : m_size{}, m_data(capacity + 1) // +1 to accommodate 1-based indexing
    {
    }

    /**
     * @brief Constructs a heap from an initializer list of items.
     *
     * @param items Initializer list of items to build the heap from.
     */
    explicit HeapTree(std::initializer_list<value_type> items)
        : m_size{items.size()}, m_data(items.size() + 1)
    {
        std::size_t index{};
        for (const auto& item : items)
        {
            m_data[++index] = item; // Discard 0th element.
        }

        build_heap(); // Establish heap order property.
    }

    /**
     * @brief Constructs a heap from a range of items.
     *
     * @param items Range of items to build the heap from.
     */
    // clang-format off
    template <std::ranges::range R>
        requires std::ranges::range_value_t<R> == value_type
    // clang-format on
    HeapTree(R&& items)
        : m_size{items.size()}, m_data(items.size() + 1)
    {
        std::ranges::copy(items, m_data.begin() + 1);
        build_heap(); // Establish heap order property.
    }

    /**
     * @brief Checks if the heap tree is empty.
     *
     * @return true if the heap tree is empty, false otherwise.
     */
    [[nodiscard]]
    bool is_empty() const noexcept
    {
        return m_size == 0;
    }

    /**
     * @brief Returns the number of elements in the heap.
     *
     * @return Number of elements in the heap.
     */
    [[nodiscard]]
    size_type size() const noexcept
    {
        return m_size;
    }

    /**
     * @brief Returns the minimum element in the heap.
     *
     * @return The minimum element.
     * @throws std::out_of_range If the heap is empty.
     */
    [[nodiscard]]
    value_type find_min() const
    {
        if (is_empty())
        {
            throw std::out_of_range("Heap underflow.");
        }

        // The smallest item is always in the root.
        return m_data[1];
    }

    /**
     * @brief Inserts an item into the heap tree.
     *
     * @param item The item to be inserted.
     */
    void insert(const_reference item)
    {
        // Double the size of the array if necessary.
        if (m_size == m_data.size() - 1)
        {
            m_data.resize(m_data.size() * 2);
        }

        // Insert a new item to the end of the array.
        size_type hole = ++m_size;

        // Percolate up: Move the hole up until the item is in the correct
        // position
        m_data[0] = item; // Sentinel for the loop termination check

        // Traverse up the tree until the item is not smaller than its parent.
        while (item < m_data[parent(hole)])
        {
            // Move the parent down.
            m_data[hole] = std::move(m_data[parent(hole)]);

            hole = parent(hole); // Move to the parent.
        }

        m_data[hole] = item; // Place the item into the final hole position.
    }

    /**
     * @brief Removes the minimum element from the heap.
     * @throws std::out_of_range exception if the heap is empty.
     */
    void remove_min()
    {
        if (is_empty())
        {
            throw std::out_of_range("Heap underflow.");
        }

        // Move the last item to the root and reduce size
        m_data[1] = std::move(m_data[m_size--]);
        percolate_down(1); // Percolate down the root.
    }

    /**
     * @brief Empties the heap.
     */
    void make_empty() noexcept
    {
        m_size = 0; // Simply ignore the items.
    }

    /**
     * @brief Outputs the heap elements to a stream.
     *
     * @param out The output stream.
     * @param heap The heap to output.
     * @return The output stream.
     */
    friend std::ostream& operator<<(std::ostream&               out,
                                    const HeapTree<value_type>& heap)
    {
        for (size_type i{1}; i <= heap.m_size; ++i)
        {
            out << heap.m_data[i] << ' ';
        }
        return out;
    }
};
#endif // HEAPTREE_HPP
