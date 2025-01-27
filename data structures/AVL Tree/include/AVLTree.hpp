#ifndef AVLTREE_HPP
#define AVLTREE_HPP

#include "Node.hpp"

#include <algorithm> // std::max
#include <iostream>  // std::cout, std::ostream
#include <utility>   // std::exchange

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

template <typename T>
class AVLTree
{
private:
    Node<T>* m_root{nullptr}; // The node node of the AVL tree.
    int      m_count{};       // The number of elements in the AVL tree.

    // Helper functions.
    auto height(Node<T>* node) -> int;

    auto balance_factor(Node<T>* node) -> int;
    auto rotate_right(Node<T>* y) -> Node<T>*;
    auto rotate_left(Node<T>* x) -> Node<T>*;
    auto balance(Node<T>* node) -> Node<T>*;

    auto insert_helper(Node<T>* node, const T& item) -> Node<T>*;
    auto remove_helper(Node<T>* node, const T& item) -> Node<T>*;
    auto print_helper(Node<T>* node, std::ostream& out) const -> void;
    auto clear_helper(Node<T>* node) -> void;
    auto find_helper(Node<T>* node, const T& item) const -> T*;
    auto sum_helper(Node<T>* node, T& accumulator) const -> void;

    auto deep_copy(Node<T>* node) -> Node<T>*;

    /**
     * @brief Verifies if the AVL tree maintains its balance property.
     *
     * This function recursively checks if each node in the tree satisfies the
     * AVL balance property, which requires that the difference in height
     * between left and right subtrees of any node must not exceed 1.
     *
     * @param node The root node of the subtree to verify.
     * @return true if the subtree rooted at node maintains AVL balance
     * property, false otherwise.
     */
    bool verify_balance(Node<T>* node) const;
    int  count_nodes(Node<T>* node) const;
    bool verify_count() const;

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
        : m_root{deep_copy(other.m_root)}, m_count{other.m_count}
    {
    }

    // Copy assignment operator.
    AVLTree& operator=(const AVLTree& other)
    {
        if (this != &other)
        {
            clear_helper(m_root); // Clear the current tree.

            // Member-wise copy.
            m_root  = deep_copy(other.m_root); // Copy the node nodes.
            m_count = other.m_count;
        }

        return *this;
    }

    // Move constructor.
    AVLTree(AVLTree&& other) noexcept
        : m_root{std::exchange(other.m_root, nullptr)},
          m_count{std::exchange(other.m_count, 0)}
    {
    }

    // Move assignment operator.
    AVLTree& operator=(AVLTree&& other) noexcept
    {
        if (this != &other)
        {
            clear_helper(m_root); // Clear the current tree.

            // Member-wise move.
            m_root  = std::exchange(other.m_root,
                                   nullptr); // Exchange the node nodes.
            m_count = std::exchange(other.m_count,
                                    0); // Exchange the number of elements.
        }

        return *this;
    }

    /**
     * @brief Clears the AVL tree, removing all nodes.
     *
     * This function removes all nodes from the AVL tree, effectively clearing
     * it. After calling this function, the tree will be empty.
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
     * @brief Inserts a new item into the AVL tree.
     *
     * @param item The item to be inserted.
     */
    void insert(T&& item)
    {
        m_root = insert_helper(m_root, std::move(item));
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
        if (temp == nullptr)
        {
            throw std::runtime_error("Item not found in tree");
        }

        T value = *temp;
        m_root  = remove_helper(m_root, item);
        m_count--;
        return value;
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
        return *find_helper(m_root, item);
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
     * Calculates the sum of all elements in the tree.
     *
     * @return The sum of all elements in the tree.
     */
    T sum() const
    {
        T result{};

        sum_helper(m_root, result);
        return result;
    }

    // Traversal orders.
    enum class TraversalOrder
    {
        PreOrder,
        InOrder,
        PostOrder
    };

    void print(std::ostream&  os    = std::cout,
               TraversalOrder order = TraversalOrder::InOrder) const
    {
        if (m_root == nullptr)
        {
            return;
        }
        print_helper(m_root, os, order);
    }

    void print_helper(Node<T>*       node,
                      std::ostream&  out,
                      TraversalOrder order) const
    {
        if (node == nullptr)
        {
            return;
        }

        switch (order)
        {
            case TraversalOrder::PreOrder:
                out << node->data << ' ';
                print_helper(node->leftchild, out, order);
                print_helper(node->rightchild, out, order);
                break;
            case TraversalOrder::InOrder:
                print_helper(node->leftchild, out, order);
                out << node->data << ' ';
                print_helper(node->rightchild, out, order);
                break;
            case TraversalOrder::PostOrder:
                print_helper(node->leftchild, out, order);
                print_helper(node->rightchild, out, order);
                out << node->data << ' ';
                break;
        }
    }

    // Get the height of the tree
    int get_height() const
    {
        return height(m_root) + 1;
    }

    // Verify AVL property
    bool is_balanced() const
    {
        return verify_balance(m_root);
    }

    // Get node count in subtree
    int count_nodes(Node<T>* node) const
    {
        if (node == nullptr)
        {
            return 0;
        }
        return 1 + count_nodes(node->leftchild) + count_nodes(node->rightchild);
    }

    // Verify size consistency
    bool verify_count() const
    {
        return m_count == count_nodes(m_root);
    }

    /**
     * Finds the minimum value node in the AVL tree.
     *
     * @param node The node node of the AVL tree.
     * @return The minimum value node in the AVL tree.
     */
    Node<T>* min()
    {
        if (m_root == nullptr)
        {
            return nullptr;
        }

        Node<T>* current = m_root;

        // Find the leftmost node since this is based on BST.
        while (current->leftchild != nullptr)
        {
            current = current->leftchild;
        }
        return current;
    }

    /**
     * Finds the maximum value node in the AVL tree.
     *
     * @param node The node node of the AVL tree.
     * @return The maximum value node in the AVL tree.
     */
    Node<T>* max()
    {
        if (m_root == nullptr)
        {
            return nullptr;
        }

        Node<T>* current = m_root;

        // Find the rightmost node since this is based on BST.
        while (current->rightchild != nullptr)
        {
            current = current->rightchild;
        }
        return current;
    }
};

/**
 * Calculates the sum of all elements in the AVL tree.
 *
 * @param node The node node of the AVL tree.
 * @param accumulator The variable to store the sum of elements.
 */
template <typename T>
void AVLTree<T>::sum_helper(Node<T>* node, T& accumulator) const
{
    if (node == nullptr)
    {
        return;
    }
    accumulator += node->data;
    sum_helper(node->leftchild, accumulator);
    sum_helper(node->rightchild, accumulator);
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
 * @return The new node of the subtree after rotation.
 */
template <typename T>
Node<T>* AVLTree<T>::rotate_right(Node<T>* y)
{
    Node<T>* new_root = y->leftchild;   // y's left child will be the new node.
    Node<T>* T2 = new_root->rightchild; // T2 is the right subtree of new_root.

    new_root->rightchild = y;  // Make y the right child of new_root.
    y->leftchild         = T2; // Make T2 the left child of y.

    // Apply the node height formula.
    y->height = std::max(height(y->leftchild), height(y->rightchild)) + 1;
    new_root->height =
        std::max(height(new_root->leftchild), height(new_root->rightchild)) + 1;

    return new_root; // Return the new node.
}

/**
 * Rotates the given node to the left in the tree.
 *
 * @param x The node to be rotated.
 * @return The new node of the subtree after rotation.
 */
template <typename T>
Node<T>* AVLTree<T>::rotate_left(Node<T>* x)
{
    Node<T>* new_root = x->rightchild; // x's right child will be the new node.
    Node<T>* T2 = new_root->leftchild; // T2 is the left subtree of new_root.

    new_root->leftchild = x;  // Make x the left child of new_root.
    x->rightchild       = T2; // Make T2 the right child of x.

    // Apply the node height formula.
    x->height = std::max(height(x->leftchild), height(x->rightchild)) + 1;
    new_root->height =
        std::max(height(new_root->leftchild), height(new_root->rightchild)) + 1;

    return new_root; // Return the new node.
}

/**
 * Balances the AVL tree by performing necessary rotations on the given node
 * node.
 *
 * @param node The node node of the AVL tree to be balanced.
 * @return The new node node after balancing.
 */
template <typename T>
Node<T>* AVLTree<T>::balance(Node<T>* node)
{
    // Base case.
    if (node == nullptr)
    {
        return node;
    }

    // Apply the node height formula.
    // Update the height of the node node.
    node->height =
        std::max(height(node->leftchild), height(node->rightchild)) + 1;

    // int balance = balance_factor(node);

    // Check for balance factor whether node is left or right-heavy.
    // If the node is left-heavy.
    if (int balance = balance_factor(node); balance > 1)
    {
        // If the node's right child is right-heavy.
        if (balance_factor(node->rightchild) < 0)
        {
            // Double rotation (Right-left rotation).
            node->rightchild = rotate_right(node->rightchild);
        }

        return rotate_left(node); // Single rotation.
    }
    // If the node is right-heavy.
    else if (balance < -1)
    {
        // If the node's left child is left-heavy.
        if (balance_factor(node->leftchild) > 0)
        {
            // Double rotation (Left-right rotation).
            node->leftchild = rotate_left(node->leftchild);
        }

        return rotate_right(node); // Single rotation.
    }

    return node;
}

/**
 * Inserts a new node with the given item into the AVL tree.
 * The node's height is updated within the balance function.
 *
 * @param node The node node of the AVL tree.
 * @param item The item to be inserted.
 * @return The node node of the updated AVL tree.
 */
template <typename T>
Node<T>* AVLTree<T>::insert_helper(Node<T>* node, const T& item)
{
    // First step is the basic BST insertion.
    if (node == nullptr)
    {
        // Done.
        return new Node<T>{item};
    }

    if (item < node->data) // Insert to the left if item is less than node.
    {
        node->leftchild = insert_helper(node->leftchild, item);
    }
    else // Insert to the right if item is less than node.
    {
        node->rightchild = insert_helper(node->rightchild, item);
    }

    // Second step is the fixing the AVL Tree's property from changed node.
    // Node's height is updated within balance.
    return balance(node);
}

/**
 * Removes a node with the specified item from the AVL tree.
 * This function performs two steps:
 * 1. It removes the node using the binary search tree (BST) removal algorithm.
 * 2. It fixes the AVL tree's property from the changed node.
 *
 * @param node The node of the AVL tree.
 * @param item The item to be removed from the AVL tree.
 * @return The node of the AVL tree after the removal.
 */
template <typename T>
Node<T>* AVLTree<T>::remove_helper(Node<T>* node, const T& item)
{
    // First step is BST removal.
    if (node == nullptr)
    {
        return node;
    }

    if (item < node->data)
    {
        node->leftchild = remove_helper(node->leftchild, item);
    }
    else if (item > node->data)
    {
        node->rightchild = remove_helper(node->rightchild, item);
    }
    else // Found, remove it.
    {
        if (node->leftchild == nullptr) // If the node has one child.
        {
            Node<T>* temp = node->rightchild;
            delete node; // Delete the node.
            return temp;
        }
        else if (node->rightchild == nullptr) // If the node has one child.
        {
            Node<T>* temp = node->leftchild;
            delete node; // Delete the node.
            return temp;
        }

        // If the node has two children.
        Node<T>* temp = min(node->rightchild); // Find the inorder successor.
        node->data =
            temp->data; // Copy the inorder successor's data to the node.
        node->rightchild =
            remove_helper(node->rightchild,
                          temp->data); // Delete the inorder successor.
    }

    // Second step is the fixing the AVL Tree's property from changed node.
    return balance(node);
}

/**
 * Recursively prints the elements of the AVL tree in post-order traversal.
 *
 * @param node The node node of the AVL tree.
 * @param os The output stream to print to.
 */
template <typename T>
void AVLTree<T>::print_helper(Node<T>* node, std::ostream& out) const
{
    /*
     *  Pre-order :  <ROOT>  LEFT   RIGHT
     *  In-order  :  LEFT   <ROOT>  RIGHT
     *  Post-order:  LEFT    RIGHT <ROOT>
     */

    if (node == nullptr)
    {
        return;
    }

    print_helper(node->leftchild, out);  // Call left sub-tree.
    print_helper(node->rightchild, out); // Call right sub-tree.
    out << node->data << ' ';
}

/**
 * @brief Recursively clears the AVL tree starting from the given node node.
 *
 * @tparam T The type of elements stored in the AVL tree.
 * @param node The node node of the AVL tree.
 */
template <typename T>
void AVLTree<T>::clear_helper(Node<T>* node)
{
    if (node == nullptr)
    {
        return;
    }

    // This uses post-order.
    clear_helper(node->leftchild);
    clear_helper(node->rightchild);

    delete node; // Delete the node.
}

// Finding items are the same as in BST.
/**
 * @brief Helper function to find an item in the AVL tree.
 *
 * This function recursively searches for the specified item in the AVL tree
 * starting from the given node node.
 *
 * @param node The node node of the AVL tree.
 * @param item The item to be found.
 * @return A reference to the found item if it exists, otherwise a reference to
 * a default-constructed item.
 */
template <typename T>
T* AVLTree<T>::find_helper(Node<T>* node, const T& item) const
{
    while (node != nullptr)
    {
        if (item < node->data)
        {
            node = node->leftchild;
        }
        else if (item > node->data)
        {
            node = node->rightchild;
        }
        else
        {
            return &node->data;
        }
    }
    throw std::runtime_error("Item not found in tree");
}

/**
 * @brief Deep copies the binary search tree starting from the given node.
 *
 * @param node The node node of the binary search tree.
 * @return A pointer to the root node of the copied binary search tree.
 */
template <typename T>
Node<T>* AVLTree<T>::deep_copy(Node<T>* node)
{
    if (node == nullptr)
        return nullptr;

    Node<T>* new_node    = new Node<T>{node->data};
    new_node->height     = node->height; // Copy height
    new_node->leftchild  = deep_copy(node->leftchild);
    new_node->rightchild = deep_copy(node->rightchild);

    return new_node;
}

template <typename T>
bool AVLTree<T>::verify_balance(Node<T>* node) const
{
    if (node == nullptr)
    {
        return true;
    }

    if (int bf = balance_factor(node); bf > 1 || bf < -1)
    {
        return false;
    }

    return verify_balance(node->leftchild) && verify_balance(node->rightchild);
}

template <typename T>
int AVLTree<T>::count_nodes(Node<T>* node) const
{
    if (node == nullptr)
    {
        return 0;
    }

    return 1 + count_nodes(node->leftchild) + count_nodes(node->rightchild);
}

template <typename T>
bool AVLTree<T>::verify_count() const
{
    return m_count == count_nodes(m_root);
}

#endif // AVLTREE_HPP
