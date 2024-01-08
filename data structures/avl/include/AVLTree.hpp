#ifndef AVLTREE_HPP
#define AVLTREE_HPP

/*
 *  AVL Trees are a specialized for of Binary Search Trees.
 *
 *  AVL Trees require the following:
 *
 *  The heights of left and right children of every node
 *  has to differ by at most +-1.
 *
 *  abs(height(rightchild) - height(leftchild)) <= 1
 *  for every node.
 *
 */

#include "Node.hpp"

#include <algorithm> // std::max
#include <iostream>
#include <utility>

template <typename T>
class AVLTree
{
private:
    Node<T>* m_root{nullptr}; // The root node of the AVL tree.
    int      m_count{};       // The number of elements in the AVL tree.

    // Helper functions.
    auto height(Node<T>* node) -> int;

    auto balance_factor(Node<T>* node) -> int;
    auto rotate_right(Node<T>* y) -> Node<T>*;
    auto rotate_left(Node<T>* x) -> Node<T>*;
    auto balance(Node<T>* root) -> Node<T>*;

    auto insert_helper(Node<T>* root, const T& item) -> Node<T>*;
    auto remove_helper(Node<T>* root, const T& item) -> Node<T>*;
    auto print_helper(Node<T>* root, std::ostream& os) const -> void;
    auto clear_helper(Node<T>* root) -> void;
    auto find_helper(Node<T>* root, const T& item) const -> T*;
    auto sum_helper(Node<T>* root, int& accumulator) const -> void;

    auto min(Node<T>* root) -> Node<T>*;

public:
    // Constructors.
    AVLTree() = default;

    // Destructor.
    ~AVLTree()
    {
        clear_helper(m_root); // Clear the children.
    }

    // Copy constructor.
    AVLTree(const AVLTree& other)
    {
        // Member-wise copy.
        m_root  = other.m_root;
        m_count = other.m_count;
    }

    // Copy assignment operator.
    AVLTree& operator=(const AVLTree& other)
    {
        if (this != &other)
        {
            clear_helper(m_root); // Clear the current tree.

            // Member-wise copy.
            m_root  = other.m_root;
            m_count = other.m_count;
        }

        return *this;
    }

    // Move constructor.
    AVLTree(AVLTree&& other) noexcept
        : m_root{std::exchange(other.m_root, nullptr)}, m_count{std::exchange(other.m_count, 0)}
    {
    }

    // Move assignment operator.
    AVLTree& operator=(AVLTree&& other) noexcept
    {
        if (this != &other)
        {
            clear_helper(m_root); // Clear the current tree.

            // Member-wise move.
            m_root  = std::exchange(other.m_root, nullptr); // Exchange the root nodes.
            m_count = std::exchange(other.m_count, 0);      // Exchange the number of elements.
        }

        return *this;
    }

    /**
     * @brief Clears the AVL tree, removing all nodes.
     *
     * This function removes all nodes from the AVL tree, effectively clearing it.
     * After calling this function, the tree will be empty.
     */
    void clear()
    {
        clear_helper(m_root);

        m_root  = nullptr;
        m_count = 0;
    }

    /**
     * Inserts a new item into the AVL tree.
     *
     * @param item The item to be inserted.
     */
    void insert(const T& item)
    {
        m_root = insert_helper(m_root, item);
        m_count++;
    }

    /**
     * @brief Removes an item from the AVL tree.
     *
     * @tparam T The type of the items stored in the AVL tree.
     * @param item The item to be removed.
     * @return The removed item if found, otherwise a default-constructed item.
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
     * @brief Finds the specified item in the AVL tree.
     *
     * @tparam T The type of the item to find.
     * @param item The item to find.
     * @return A reference to the found item.
     */
    T& find(const T& item) const
    {
        return find_helper(m_root, item);
    }

    /**
     * @brief Returns the number of elements in the AVL tree.
     *
     * @return The number of elements in the AVL tree.
     */
    int size() const
    {
        return m_count;
    }

    /**
     * Prints the elements of the AVL tree in ascending order.
     *
     * @param os The output stream to print the elements to. Default is std::cout.
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

    /**
     * Calculates the sum of all elements in the AVL tree.
     *
     * @return The sum of all elements in the AVL tree.
     */
    T sum() const
    {
        T result{};

        sum_helper(m_root, result);
        return result;
    }
};

/**
 * Calculates the sum of all elements in the AVL tree.
 *
 * @param root The root node of the AVL tree.
 * @param accumulator The variable to store the sum of elements.
 */
template <typename T>
void AVLTree<T>::sum_helper(Node<T>* root, int& accumulator) const
{
    // Base case.
    if (root == nullptr)
    {
        return;
    }

    accumulator += root->data; // Add the current node's data to the accumulator.

    sum_helper(root->leftchild, accumulator);  // Call left sub-tree.
    sum_helper(root->rightchild, accumulator); // Call right sub-tree.
}

/**
 * Calculates the height of a given node in the AVL tree.
 * The height of an empty node is defined as -1.
 *
 * @param node The node for which to calculate the height.
 * @return The height of the node.
 */
template <typename T>
int AVLTree<T>::height(Node<T>* node)
{
    if (node == nullptr)
    {
        /*
         *  The reason for empty node's height -1 is that it makes
         *  the node height formula convenient, we don't have to
         *  write special cases.
         *
         *  (-1) + 1 -> 0.
         */
        return -1;
    }

    return node->height;
}

/**
 * Calculates the balance factor of a given node in the AVL tree.
 *
 * @param node The node for which to calculate the balance factor.
 * @return The balance factor of the node.
 */
template <typename T>
int AVLTree<T>::balance_factor(Node<T>* node)
{
    // Empty node's balance factor is 0.
    if (node == nullptr)
    {
        return 0;
    }

    // Balance factor = height(right subtree) - height(left subtree)
    // A node is said to be balanced if its balance factor is -1, 0, or 1.
    return height(node->rightchild) - height(node->leftchild);
}

/**
 * Rotates the given node to the right in the tree.
 *
 * @param y The node to be rotated.
 * @return The new root of the subtree after rotation.
 */
template <typename T>
Node<T>* AVLTree<T>::rotate_right(Node<T>* y)
{
    Node<T>* new_root = y->leftchild;         // y's left child will be the new root.
    Node<T>* T2       = new_root->rightchild; // T2 is the right subtree of new_root.

    new_root->rightchild = y;  // Make y the right child of new_root.
    y->leftchild         = T2; // Make T2 the left child of y.

    // Apply the node height formula.
    y->height        = std::max(height(y->leftchild), height(y->rightchild)) + 1;
    new_root->height = std::max(height(new_root->leftchild), height(new_root->rightchild)) + 1;

    return new_root; // Return the new root.
}

/**
 * Rotates the given node to the left in the tree.
 *
 * @param x The node to be rotated.
 * @return The new root of the subtree after rotation.
 */
template <typename T>
Node<T>* AVLTree<T>::rotate_left(Node<T>* x)
{
    Node<T>* new_root = x->rightchild;       // x's right child will be the new root.
    Node<T>* T2       = new_root->leftchild; // T2 is the left subtree of new_root.

    new_root->leftchild = x;  // Make x the left child of new_root.
    x->rightchild       = T2; // Make T2 the right child of x.

    // Apply the node height formula.
    x->height        = std::max(height(x->leftchild), height(x->rightchild)) + 1;
    new_root->height = std::max(height(new_root->leftchild), height(new_root->rightchild)) + 1;

    return new_root; // Return the new root.
}

/**
 * Balances the AVL tree by performing necessary rotations on the given root node.
 *
 * @param root The root node of the AVL tree to be balanced.
 * @return The new root node after balancing.
 */
template <typename T>
Node<T>* AVLTree<T>::balance(Node<T>* root)
{
    // Base case.
    if (root == nullptr)
    {
        return root;
    }

    // Apply the node height formula.
    // Update the height of the root node.
    root->height = std::max(height(root->leftchild), height(root->rightchild)) + 1;

    // int balance = balance_factor(root);

    // Check for balance factor whether root is left or right-heavy.
    // If the root is left-heavy.
    if (int balance = balance_factor(root); balance > 1)
    {
        // If the root's right child is right-heavy.
        if (balance_factor(root->rightchild) < 0)
        {
            // Double rotation (Right-left rotation).
            root->rightchild = rotate_right(root->rightchild);
        }

        return rotate_left(root); // Single rotation.
    }
    // If the root is right-heavy.
    else if (balance < -1)
    {
        // If the root's left child is left-heavy.
        if (balance_factor(root->leftchild) > 0)
        {
            // Double rotation (Left-right rotation).
            root->leftchild = rotate_left(root->leftchild);
        }

        return rotate_right(root); // Single rotation.
    }

    return root;
}

/**
 * Inserts a new node with the given item into the AVL tree.
 * The node's height is updated within the balance function.
 *
 * @param root The root node of the AVL tree.
 * @param item The item to be inserted.
 * @return The root node of the updated AVL tree.
 */
template <typename T>
Node<T>* AVLTree<T>::insert_helper(Node<T>* root, const T& item)
{
    // First step is the basic BST insertion.
    if (root == nullptr)
    {
        // Done.
        return new Node<T>{item};
    }

    if (item < root->data) // Insert to the left if item is less than root.
    {
        root->leftchild = insert_helper(root->leftchild, item);
    }
    else // Insert to the right if item is less than root.
    {
        root->rightchild = insert_helper(root->rightchild, item);
    }

    // Second step is the fixing the AVL Tree's property from changed node.
    // Node's height is updated within balance.
    return balance(root);
}

/**
 * Removes a node with the specified item from the AVL tree.
 * This function performs two steps:
 * 1. It removes the node using the binary search tree (BST) removal algorithm.
 * 2. It fixes the AVL tree's property from the changed node.
 *
 * @param root The root node of the AVL tree.
 * @param item The item to be removed from the AVL tree.
 * @return The root node of the AVL tree after the removal.
 */
template <typename T>
Node<T>* AVLTree<T>::remove_helper(Node<T>* root, const T& item)
{
    // First step is BST removal.
    if (root == nullptr)
    {
        return root;
    }

    if (item < root->data)
    {
        root->leftchild = remove_helper(root->leftchild, item);
    }
    else if (item > root->data)
    {
        root->rightchild = remove_helper(root->rightchild, item);
    }
    else // Found, remove it.
    {
        if (root->leftchild == nullptr) // If the node has one child.
        {
            Node<T>* temp = root->rightchild;
            delete root; // Delete the node.
            return temp;
        }
        else if (root->rightchild == nullptr) // If the node has one child.
        {
            Node<T>* temp = root->leftchild;
            delete root; // Delete the node.
            return temp;
        }

        // If the node has two children.
        Node<T>* temp    = min(root->rightchild); // Find the inorder successor.
        root->data       = temp->data;            // Copy the inorder successor's data to the node.
        root->rightchild = remove_helper(root->rightchild, temp->data); // Delete the inorder successor.
    }

    // Second step is the fixing the AVL Tree's property from changed node.
    return balance(root);
}

/**
 * Finds the minimum value node in the AVL tree.
 *
 * @param root The root node of the AVL tree.
 * @return The minimum value node in the AVL tree.
 */
template <typename T>
Node<T>* AVLTree<T>::min(Node<T>* root)
{
    // Find the leftmost node since this is based on BST.
    while (root->leftchild != nullptr)
    {
        root = root->leftchild;
    }
    return root;
}

/**
 * Recursively prints the elements of the AVL tree in post-order traversal.
 *
 * @param root The root node of the AVL tree.
 * @param os The output stream to print to.
 */
template <typename T>
void AVLTree<T>::print_helper(Node<T>* root, std::ostream& os) const
{
    /*
     *  Pre-order :  <ROOT>  LEFT   RIGHT
     *  In-order  :  LEFT   <ROOT>  RIGHT
     *  Post-order:  LEFT    RIGHT <ROOT>
     */

    if (root == nullptr)
    {
        return;
    }

    print_helper(root->leftchild, os);  // Call left sub-tree.
    print_helper(root->rightchild, os); // Call right sub-tree.
    os << root->data << ' ';
}

/**
 * @brief Recursively clears the AVL tree starting from the given root node.
 *
 * @tparam T The type of elements stored in the AVL tree.
 * @param root The root node of the AVL tree.
 */
template <typename T>
void AVLTree<T>::clear_helper(Node<T>* root)
{
    if (root == nullptr)
    {
        return;
    }

    // This uses post-order.
    clear_helper(root->leftchild);
    clear_helper(root->rightchild);

    delete root; // Delete the node.
}

// Finding items are the same as in BST.
/**
 * @brief Helper function to find an item in the AVL tree.
 *
 * This function recursively searches for the specified item in the AVL tree starting from the given root node.
 *
 * @param root The root node of the AVL tree.
 * @param item The item to be found.
 * @return A reference to the found item if it exists, otherwise a reference to a default-constructed item.
 */
template <typename T>
T* AVLTree<T>::find_helper(Node<T>* root, const T& item) const
{
    while (root != nullptr)
    {
        if (item < root->data)
        {
            root = root->leftchild;
        }
        else if (item > root->data)
        {
            root = root->rightchild;
        }
        else
        {
            return root->data;
        }
    }

    return nullptr; // Not found.
}
#endif // AVLTREE_HPP
