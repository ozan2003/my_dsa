#ifndef HEAPTREE_HPP
#define HEAPTREE_HPP

#include <array>            // std::array
#include <initializer_list> // std::initializer_list
#include <iostream>         // operator<<
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

constexpr std::size_t INITIAL_CAPACITY{10}; // The initial capacity of the array.

// Implemented as a min-heap.
template <typename T>
class HeapTree
{
public:
    using value_type = T;
    using size_type = std::size_t;
    using reference = T&;
    using const_reference = const T&;
    using pointer = T*;
    using const_pointer = const T*;
    
private:
    size_type m_size; // The number of items in the heap.
    std::vector<value_type> m_data; // The array that stores the items.

    /**
     * @brief Builds the heap by percolating down the parent nodes.
     *
     * This function starts from the last parent node and percolates down each
     * parent node to maintain the heap property.
     *
     * @note This function assumes that the heap is already initialized with
     * elements.
     *
     * @tparam T The type of elements in the heap.
     */
    void build_heap() noexcept
    {
        // Start from the last parent.
        for (size_type i{m_size / 2}; 0 < i; --i)
        {
            percolate_down(i); // Percolate down the parent.
        }
    }

    /**
     * Percolates down the heap from the given hole index.
     *
     * @param hole The index of the hole to percolate down from.
     */
    void percolate_down(size_type hole) noexcept
    {
        size_type child{}; // The index of the child of the hole.
        // The item that will be percolated down.
        value_type tmp = std::move(m_data[hole]);

        // Percolate down the hole.
        for (; hole * 2 < m_size; hole = child)
        {
            child = hole * 2; // The index of the left child.

            // If the left child is not the last element and the right child is
            // smaller than the left child, then use the right child.
            if (child != m_size && (m_data[child + 1] < m_data[child]))
            {
                ++child;
            }

            // If the child is smaller than the item that is percolated down,
            // then move the child up.
            if (m_data[child] < tmp)
            {
                m_data[hole] = std::move(m_data[child]);
            }
            else
            {
                break;
            }
        }
        m_data[hole] = std::move(tmp); // Move the item into the hole.
    }

public:
    // "explicit", prevents implicit conversion such as char to integer.
    explicit HeapTree(const size_type capacity = INITIAL_CAPACITY)
        : m_size{}, m_data(capacity)
    {
    }

    // Construct the heap tree given a vector of items.
    explicit HeapTree(const std::vector<value_type>& items)
        : m_size{items.size()}, m_data(items.size() + 1)
    {
        for (std::size_t i{}; i < items.size(); ++i)
        {
            m_data[i + 1] = items[i];
        }

        build_heap(); // Establish heap order property.
    }

    // Construct the heap tree given an initializer list of items.
    explicit HeapTree(std::initializer_list<value_type> items)
        : m_size{items.size()}, m_data(items.size() + 1)
    {
        for (std::size_t index{}; const auto& item : items)
        {
            m_data[++index] = item; // Discard 0th element.
        }

        build_heap(); // Establish heap order property.
    }

    /**
     * @brief Constructs a HeapTree object from an array of items.
     *
     * @tparam N The size of the array.
     * @param items The array of items.
     */
    template <std::size_t N>
    explicit HeapTree(const std::array<value_type, N>& items)
        : m_size{items.size()}, m_data(items.size() + 1)
    {
        size_type index{};
        for (const auto& item : items)
        {
            m_data[++index] = item; // Discard 0th element.
        }

        build_heap(); // Establish heap order property.
    }

    /**
     * @brief Checks if the heap tree is empty.
     *
     * @return true if the heap tree is empty, false otherwise.
     */
    bool empty() const noexcept
    {
        return m_size == 0;
    }

    /**
     * @brief Returns a reference to the minimum element in the heap.
     *
     * @tparam T The type of elements stored in the heap.
     * @return T& A reference to the minimum element.
     * @throws std::out_of_range If the heap is empty.
     */
    const_reference find_min() const
    {
        if (empty())
        {
            throw std::out_of_range("Heap underflow.");
        }

        // The smallest item is always in the root.
        return m_data[1];
    }

    /**
     * Inserts an item into the heap tree.
     *
     * @param item The item to be inserted.
     */
    void insert(const_reference item) noexcept
    {
        // Double the size of the array if necessary.
        if (m_size == m_data.size() - 1)
        {
            m_data.resize(m_data.size() * 2);
        }

        // Insert a new item to the end of the array.
        size_type hole = ++m_size;

        // Traverse up the tree until the item is not smaller than its parent.
        // Move the hole up until the item is not smaller than its parent.
        for (; item < m_data[hole / 2]; hole /= 2)
        {
            // Move the parent down.
            m_data[hole] = std::move(m_data[hole / 2]);
        }

        m_data[hole] = std::move(item); // Move the item into the hole.
    }

    /**
     * Removes the minimum element from the heap.
     * @throws std::out_of_range exception if the heap is empty.
     */
    void remove_min()
    {
        if (empty())
        {
            throw std::out_of_range("Heap underflow.");
        }

        // The minimum element can be found at the root, which is the first
        // element of the array.
        m_data[1] =
            std::move(m_data[m_size--]); // Move the last item to the root.
        percolate_down(1);               // Percolate down the root.
    }

    void make_empty() noexcept
    {
        m_size = 0; // Simply ignore the items.
    }

    friend std::ostream& operator<<(std::ostream& out, const HeapTree<value_type>& heap)
    {
        for (size_type i{1}; i <= heap.m_size; ++i)
        {
            out << heap.m_data[i] << ' ';
        }
        return out;
    }
};
#endif // HEAPTREE_HPP
