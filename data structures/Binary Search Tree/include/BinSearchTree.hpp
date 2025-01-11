#ifndef BINSEARCHTREE_HPP
#define BINSEARCHTREE_HPP

#include "Helper.hpp"
#include "Node.hpp"

#include <iostream>
#include <utility>

/**
 * Pre-order: ROOT, left, right
 * In-order: left, ROOT, right
 * Post-order: left, right, ROOT
 */

template <typename T>
class BinSearchTree
{
private:
    Node<T>* m_root{nullptr}; // The root node of the BST
    int      m_count{};       // Number of nodes in the BST

public:
    // Default constructor.
    BinSearchTree() = default;

    // Destructor.
    ~BinSearchTree()
    {
        helper::clear(m_root);
    }

    // Copy constructor.
    BinSearchTree(const BinSearchTree& other)
        : m_root{helper::deep_copy(other.m_root)}, m_count{other.m_count}
    {
    }

    // Copy assignment operator. This is a deep copy.
    BinSearchTree& operator=(const BinSearchTree& other)
    {
        // Check for self-assignment.
        if (this != &other)
        {
            // Clear the current tree.
            helper::clear(m_root);
            m_root  = helper::deep_copy(other.m_root);
            m_count = other.m_count;
        }

        return *this;
    }

    // Move constructor.
    BinSearchTree(BinSearchTree&& other) noexcept
        : m_root{std::exchange(other.m_root, nullptr)},
          m_count{std::exchange(other.m_count, 0)}
    {
    }

    // Move assignment operator.
    BinSearchTree& operator=(BinSearchTree&& other) noexcept
    {
        // Check for self-assignment.
        if (this != &other)
        {
            helper::clear(m_root);
            m_root  = std::exchange(other.m_root, nullptr);
            m_count = std::exchange(other.m_count, 0);
        }
        return *this;
    }

    /**
     * @brief Clears the tree.
     *
     * Remove all nodes from the tree and resets the node pointer
     * and count of nodes.
     */
    void clear()
    {
        helper::clear(m_root);

        m_root  = nullptr;
        m_count = 0;
    }

    /**
     * Inserts a new item into the tree.
     *
     * @param item The item to be inserted.
     */
    void insert(const T& item)
    {
        m_root = helper::insert(m_root, item);
        m_count++;
    }

    /**
     * @brief Removes an item from the tree.
     *
     * @tparam T The type of the items stored in the tree.
     * @param item The item to be removed.
     */
    void remove(const T& item)
    {
        if (helper::find(m_root, item))
        {
            m_root = helper::remove(m_root, item);
            m_count--;
        }
    }

    auto find(const T& item) const -> const T*
    {
        Node<T>* node = helper::find(m_root, item);
        return node ? &node->data : nullptr;
    }

    auto size() const -> int
    {
        return m_count;
    }

    /**
     * @brief Prints the elements of the tree in ascending order.
     *
     * This function traverses the tree in an in-order manner and
     * prints the elements in ascending order.
     *
     * @note If the tree is empty, nothing will be printed.
     */
    void print(std::ostream& os = std::cout) const
    {
        helper::print(m_root, os);
        os << '\n';
    }
};

#endif // BINSEARCHTREE_HPP
