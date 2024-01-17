#ifndef BINSEARCHTREE_HPP
#define BINSEARCHTREE_HPP

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

    // Helper functions.
    auto clear_helper(Node<T>* node) -> void;
    auto insert_helper(Node<T>* node, const T& item) -> Node<T>*;
    auto find_helper(Node<T>* node, const T& item) const -> T*;
    auto remove_helper(Node<T>* node, const T& item) -> Node<T>*;
    auto print_helper(Node<T>* node, std::ostream& os) const -> void;
    auto remove_min(Node<T>* node) -> Node<T>*;
    auto min(Node<T>* node) -> Node<T>*;
    auto deep_copy(Node<T>* node) -> Node<T>*;

public:
    // Default constructor.
    BinSearchTree() = default;

    // Destructor.
    ~BinSearchTree()
    {
        clear_helper(m_root);
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
            clear_helper(m_root);

            // Deep copy the other tree.
            m_root  = deep_copy(other.m_root);
            m_count = other.m_count;
        }

        return *this;
    }

    // Move constructor.
    BinSearchTree(BinSearchTree&& other) noexcept
        : m_root{std::exchange(other.m_root, nullptr)}, m_count{std::exchange(other.m_count, 0)}
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
     * @brief Clears the binary search tree.
     *
     * Remove all nodes from the binary search tree and resets the node pointer and count of nodes.
     */
    void clear()
    {
        clear_helper(m_root);

        m_root  = nullptr;
        m_count = 0;
    }

    /**
     * Inserts a new item into the binary search tree.
     *
     * @param item The item to be inserted.
     */
    void insert(const T& item)
    {
        m_root = insert_helper(m_root, item);
        m_count++;
    }

    /**
     * @brief Removes an item from the binary search tree.
     *
     * @tparam T The type of the items stored in the binary search tree.
     * @param item The item to be removed.
     * @return The removed item, or 0 if the item was not found in the tree.
     */
    T remove(const T& item)
    {
        T* temp = find_helper(m_root, item);

        if (temp != 0)
        {
            m_root = remove_helper(m_root, item);
            m_count--;
        }

        return temp == nullptr ? T{} : *temp; // Return 0 if item was not found.
    }

    /**
     * @brief Finds the specified item in the binary search tree.
     *
     * @tparam T The type of the item to find.
     * @param item The item to find.
     * @return The found item.
     */
    T find(const T& item) const
    {
        return find_helper(m_root, item);
    }

    /**
     * Returns the number of elements in the binary search tree.
     *
     * @return The number of elements in the binary search tree.
     */
    int size() const
    {
        return m_count;
    }

    /**
     * @brief Prints the elements of the binary search tree in ascending order.
     *
     * This function traverses the binary search tree in an in-order manner and prints
     * the elements in ascending order.
     *
     * @note If the binary search tree is empty, nothing will be printed.
     */
    void print(std::ostream& os = std::cout) const
    {
        if (m_root == nullptr)
        {
            return;
        }
        else
        {
            print_helper(m_root, os);
        }
    }
};

/**
 * @brief Helper function to find an item in the binary search tree.
 *
 * @param node The node node of the binary search tree.
 * @param item The item to be found.
 * @return A pointer to the found item if it exists in the tree, otherwise nullptr.
 */
template <typename T>
T* BinSearchTree<T>::find_helper(Node<T>* node, const T& item) const
{
    while (node != nullptr)
    {
        if (item < node->data) // Check left if item is smaller than node.
        {
            node = node->leftchild;
        }
        else if (item > node->data) // Check right if item is greater than node.
        {
            node = node->rightchild;
        }
        else
        {
            return &(node->data); // Found it.
        }
    }

    return nullptr; // Empty tree or item not found.
}

/**
 * Inserts a new node with the given item into the binary search tree rooted at the specified node.
 * If the node is nullptr, a new node is created with the given item and returned as the new node.
 * If the item is less than the node's data, it is inserted to the left of the node.
 * If the item is greater than or equal to the node's data, it is inserted to the right of the node.
 *
 * @param node The node of the binary search tree.
 * @param item The item to be inserted.
 * @return The node of the modified binary search tree.
 */
template <typename T>
Node<T>* BinSearchTree<T>::insert_helper(Node<T>* node, const T& item)
{
    if (node == nullptr) // Done.
    {
        return new Node<T>{item};
    }

    if (item < node->data) // Insert to the right if item is less than node.
    {
        node->leftchild = insert_helper(node->leftchild, item);
    }
    else // Insert to the left if item is less than node.
    {
        node->rightchild = insert_helper(node->rightchild, item);
    }

    return node;
}

/**
 * Removes the minimum value from the binary search tree rooted at the given node.
 *
 * @param node The node node of the binary search tree.
 * @return The updated node node after removing the minimum value.
 */
template <typename T>
Node<T>* BinSearchTree<T>::remove_min(Node<T>* node)
{
    if (node->leftchild == nullptr) // Found min.
    {
        return node->rightchild;
    }
    else
    {
        node->leftchild = remove_min(node->leftchild); // Continue left.

        return node;
    }
}

/**
 * Finds the minimum value in a binary search tree starting from the given node node.
 *
 * @param node The node node of the binary search tree.
 * @return The node containing the minimum value.
 */
template <typename T>
Node<T>* BinSearchTree<T>::min(Node<T>* node)
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

/**
 * Removes the node with the specified item from the binary search tree.
 * If the item is not found, the tree remains unchanged.
 *
 * @param node The node node of the binary search tree.
 * @param item The item to be removed.
 * @return The node node of the modified binary search tree.
 */
template <typename T>
Node<T>* BinSearchTree<T>::remove_helper(Node<T>* node, const T& item)
{
    if (node == nullptr) // item is not in the tree
    {
        return nullptr; // return NULL;
    }
    else if (item < node->data)
    {
        node->leftchild = remove_helper(node->leftchild, item);
    }
    else if (item > node->data)
    {
        node->rightchild = remove_helper(node->rightchild, item);
    }
    else // Found the item, remove it.
    {
        // Maintain the BST property.
        Node<T>* temp = node;

        /**
         * If the node to be removed has only one child, then we can simply replace the node with its child.
         */
        if (node->leftchild == nullptr) // Only a right child.
        {
            node = node->rightchild; // Point to the right child.
            delete temp;
        }
        else if (node->rightchild == nullptr) // Only a left child.
        {
            node = node->leftchild; // Point to the left child.
            delete temp;
        }
        // If the node to be removed has two children, then we replace the node with the minimum value in the right
        // subtree.
        else
        {
            temp = min(node->rightchild); // Find the minimum value in the right subtree.

            node->data       = temp->data;                   // Replace the node's data with the minimum value.
            node->rightchild = remove_min(node->rightchild); // Remove the minimum value from the right subtree.

            delete temp;
        }
    }

    return node;
}

/**
 * @brief Recursively clears the binary search tree starting from the given node.
 *
 * @tparam T The type of elements stored in the binary search tree.
 * @param node The node node of the binary search tree.
 */
template <typename T>
void BinSearchTree<T>::clear_helper(Node<T>* node)
{
    if (node == nullptr)
    {
        return;
    }

    clear_helper(node->leftchild);
    clear_helper(node->rightchild);

    delete node;
}

/**
 * @brief Helper function to print the elements of the binary search tree in in-order traversal.
 *
 * @param node The node node of the binary search tree.
 */
template <typename T>
void BinSearchTree<T>::print_helper(Node<T>* node, std::ostream& os) const
{
    if (node == nullptr)
    {
        return;
    }

    // In-order traversal.
    print_helper(node->leftchild, os);
    os << node->data << ' ';
    print_helper(node->rightchild, os);
}

/**
 * @brief Deep copies the binary search tree starting from the given node.
 *
 * @param node The node node of the binary search tree.
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
