#ifndef BINSEARCHTREE_HPP
#define BINSEARCHTREE_HPP

#include "Helper.hpp"
#include "Node.hpp"

#include <iostream> // std::cout
#include <utility>  // std::move

/**
 * Pre-order: ROOT, left, right
 * In-order: left, ROOT, right
 * Post-order: left, right, ROOT
 */

template <typename T>
class BinSearchTree
{
private:
    Node<T>* m_root{nullptr}; // The node of the BST.
    int      m_count{};       // Number of the nodes in the BST.

    // Helper function.
    auto deep_copy(Node<T>* node) -> Node<T>*;

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
        : m_root{deep_copy(other.m_root)}, m_count{other.m_count}
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

            // Deep copy the other tree.
            m_root  = deep_copy(other.m_root);
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
            // Member-wise move.
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
        const Node<T>* target_node = find(m_root, item);

        if (target_node != nullptr)
        {
            m_root = helper::remove(m_root, item);
            m_count--;
        }
    }

    /**
     * @brief Finds the specified item in the tree.
     *
     * @tparam T The type of the item.
     * @param item The item to find.
     * @return Pointer to the node containing the item; nullptr if the item
     *         was not found.
     */
    Node<T>* find(const T& item) const
    {
        Node<T>* node = m_root; // Start from the root.
        while (node != nullptr)
        {
            // Check left if item is smaller than node.
            if (item < node->data) 
            {
                node = node->leftchild;
            }
            // Check right if item is greater than node.
            else if (item > node->data) 
            {
                node = node->rightchild;
            }
            else
            {
                return &node; // Found it.
            }
        }

        return nullptr; // Empty tree or item not found.
    }

    /**
     * Returns the number of elements in the tree.
     *
     * @return The number of elements in the tree.
     */
    int size() const
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
        if (m_root == nullptr)
        {
            return;
        }
        else
        {
            helper::print(m_root, os);
        }
    }

    /**
     * Finds the minimum value in a binary search tree starting from the given node
     * node.
     *
     * @param node The node node of the tree.
     * @return The node containing the minimum value.
     */
    template <typename T>
    Node<T>* min(Node<T>* node)
    {
        if (node->leftchild == nullptr)
        {
            return node;
        }
        else
        {
            return min(node->leftchild);
        }
    }
};

/**
 * @brief Deep copies the tree starting from the given node.
 *
 * @param node The node node of the tree.
 * @return A pointer to the root node of the copied binary search tree.
 */
template <typename T>
Node<T>* BinSearchTree<T>::deep_copy(Node<T>* node)
{
    if (node == nullptr)
    {
        return nullptr;
    }

    Node<T>* new_node = new Node<T>{node->data};

    new_node->leftchild  = deep_copy(node->leftchild);
    new_node->rightchild = deep_copy(node->rightchild);

    return new_node;
}
#endif // BINSEARCHTREE_HPP
