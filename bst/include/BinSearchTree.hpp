#ifndef BINSEARCHTREE_HPP
#define BINSEARCHTREE_HPP

#include "Node.hpp"

#include <iostream> // std::cout
#include <utility>  // std::move

template <typename T>
class BinSearchTree
{
private:
    Node<T>* m_root{nullptr}; // The root of the BST.
    int      m_count{};       // Number of the nodes in the BST.

    // Helper functions.
    auto clear_helper(Node<T>*) -> void;
    auto insert_helper(Node<T>*, const T&) -> Node<T>*;
    auto find_helper(Node<T>*, const T&) const -> T*;
    auto remove_helper(Node<T>*, const T&) -> Node<T>*;
    auto print_helper(Node<T>*, std::ostream& os) const -> void;
    auto remove_min(Node<T>*) -> Node<T>*;
    auto min(Node<T>*) -> Node<T>*;

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
    {
        m_root  = other.m_root;
        m_count = other.m_count;
    }

    // Copy assignment operator.
    BinSearchTree& operator=(const BinSearchTree& other)
    {
        // Check for self-assignment.
        if (this != &other)
        {
            // Member-wise copy.
            m_root  = other.m_root;
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
     * Remove all nodes from the binary search tree and resets the root pointer and count of nodes.
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

        return *temp;
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
 * @param root The root node of the binary search tree.
 * @param item The item to be found.
 * @return The found item if it exists in the tree, otherwise NULL.
 */
template <typename T>
T* BinSearchTree<T>::find_helper(Node<T>* root, const T& item) const
{
    while (root != nullptr)
    {
        if (item < root->data) // Check left if item is smaller than root.
        {
            root = root->leftchild;
        }
        else if (item > root->data) // Check right if item is greater than root.
        {
            root = root->rightchild;
        }
        else
        {
            return &(root->data); // Found it.
        }
    }

    return nullptr; // Empty tree or item not found.
}
/**
 * Inserts a new node with the given item into the binary search tree rooted at the specified root.
 * If the root is nullptr, a new node is created with the given item and returned as the new root.
 * If the item is less than the root's data, it is inserted to the left of the root.
 * If the item is greater than or equal to the root's data, it is inserted to the right of the root.
 *
 * @param root The root of the binary search tree.
 * @param item The item to be inserted.
 * @return The root of the modified binary search tree.
 */
template <typename T>
Node<T>* BinSearchTree<T>::insert_helper(Node<T>* root, const T& item)
{
    if (root == nullptr) // Done.
    {
        return new Node<T>{item};
    }

    if (item < root->data) // Insert to the right if item is less than root.
    {
        root->leftchild = insert_helper(root->leftchild, item);
    }
    else // Insert to the left if item is less than root.
    {
        root->rightchild = insert_helper(root->rightchild, item);
    }

    return root;
}

/**
 * Removes the minimum value from the binary search tree rooted at the given node.
 *
 * @param root The root node of the binary search tree.
 * @return The updated root node after removing the minimum value.
 */
template <typename T>
Node<T>* BinSearchTree<T>::remove_min(Node<T>* root)
{
    if (root->leftchild == nullptr) // Found min.
    {
        return root->rightchild;
    }
    else
    {
        root->leftchild = remove_min(root->leftchild); // Continue left.

        return root;
    }
}

/**
 * Finds the minimum value in a binary search tree starting from the given root node.
 *
 * @param root The root node of the binary search tree.
 * @return The node containing the minimum value.
 */
template <typename T>
Node<T>* BinSearchTree<T>::min(Node<T>* root)
{
    if (root->leftchild == nullptr)
    {
        return root;
    }
    else
    {
        return min(root->leftchild);
    }
}

/**
 * Removes the node with the specified item from the binary search tree.
 * If the item is not found, the tree remains unchanged.
 *
 * @param root The root node of the binary search tree.
 * @param item The item to be removed.
 * @return The root node of the modified binary search tree.
 */
template <typename T>
Node<T>* BinSearchTree<T>::remove_helper(Node<T>* root, const T& item)
{
    if (root == nullptr) // item is not in the tree
    {
        return nullptr; // return NULL;
    }
    else if (item < root->data)
    {
        root->leftchild = remove_helper(root->leftchild, item);
    }
    else if (item > root->data)
    {
        root->rightchild = remove_helper(root->rightchild, item);
    }
    else // Found the item, remove it.
    {
        Node<T>* temp = root;

        if (root->leftchild == nullptr) // Only a right child.
        {
            root = root->rightchild; // Point to the right child.
            delete temp;
        }
        else if (root->rightchild == nullptr) // Only a left child.
        {
            root = root->leftchild; // Point to the left child.
            delete temp;
        }
        else // Both children are non-empty.
        {
            temp = min(root->rightchild); // Find the minimum value in the right subtree.

            root->data       = temp->data;                   // Replace the root's data with the minimum value.
            root->rightchild = remove_min(root->rightchild); // Remove the minimum value from the right subtree.

            delete temp;
        }
    }

    return root;
}

/**
 * @brief Recursively clears the binary search tree starting from the given root.
 *
 * @tparam T The type of elements stored in the binary search tree.
 * @param root The root node of the binary search tree.
 */
template <typename T>
void BinSearchTree<T>::clear_helper(Node<T>* root)
{
    if (root == nullptr)
    {
        return;
    }

    clear_helper(root->leftchild);
    clear_helper(root->rightchild);

    delete root;
}

/**
 * @brief Helper function to print the elements of the binary search tree in in-order traversal.
 *
 * @param root The root node of the binary search tree.
 */
template <typename T>
void BinSearchTree<T>::print_helper(Node<T>* root, std::ostream& os) const
{
    if (root == nullptr)
    {
        return;
    }

    // In-order traversal.
    print_helper(root->leftchild, os);
    os << root->data << ' ';
    print_helper(root->rightchild, os);
}

#endif // BINSEARCHTREE_HPP
