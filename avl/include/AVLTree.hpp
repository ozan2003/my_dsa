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

#include <algorithm>
#include <iostream>

template <typename T>
class AVLTree
{
private:
    Node<T>* m_root{nullptr};
    int      m_count{};

    // Helper functions.
    int      height(Node<T>* node);

    int      balance_factor(Node<T>* node);
    Node<T>* rotate_right(Node<T>* y);
    Node<T>* rotate_left(Node<T>* x);
    Node<T>* balance(Node<T>* root);

    Node<T>* insert_helper(Node<T>* root, const T& item);
    Node<T>* remove_helper(Node<T>* root, const T& item);
    void     print_helper(Node<T>* root) const;
    void     clear_helper(Node<T>* root);
    T&       find_helper(Node<T>* root, const T& item) const;
    void     sum_helper(Node<T>* root, int& sum) const;

    Node<T>* min(Node<T>* root);

public:
    AVLTree() = default;

    ~AVLTree()
    {
        clear_helper(m_root);
    }

    void clear()
    {
        clear_helper(m_root);

        m_root  = nullptr;
        m_count = 0;
    }

    void insert(const T& item)
    {
        m_root = insert_helper(m_root, item);
        m_count++;
    }

    T remove(const T& item)
    {
        T temp = find_helper(m_root, item);

        if (temp != 0)
        {
            m_root = remove_helper(m_root, item);
            m_count--;
        }

        return temp;
    }

    T& find(const T& item) const
    {
        return find_helper(m_root, item);
    }

    int size() const
    {
        return m_count;
    }

    void print() const
    {
        if (m_root == nullptr)
        {
            return;
        }
        else
        {
            print_helper(m_root);
        }
    }

    T sum() const
    {
        T result{};

        sum_helper(m_root, result);
        return result;
    }
};

template <typename T>
void AVLTree<T>::sum_helper(Node<T>* root, int& accumulator) const
{
    if (root == nullptr)
    {
        return;
    }

    // Exclude the leaves.
    if (root->isleaf())
    {
        return;
    }
    accumulator += root->data;

    sum_helper(root->leftchild, accumulator);
    sum_helper(root->rightchild, accumulator);
}

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

template <typename T>
int AVLTree<T>::balance_factor(Node<T>* node)
{
    if (node == nullptr)
    {
        return 0;
    }

    // Balance factor = height(right subtree) - height(left subtree)
    // A node is said to be balanced if its balance factor is -1, 0, or 1.
    return height(node->rightchild) - height(node->leftchild);
}

// Rotate the root to the right.
template <typename T>
Node<T>* AVLTree<T>::rotate_right(Node<T>* y)
{
    Node<T>* x  = y->leftchild;
    Node<T>* T2 = x->rightchild;

    x->rightchild = y;
    y->leftchild  = T2;
    
    // Apply the node height formula.
    y->height = std::max(height(y->leftchild), height(y->rightchild)) + 1;
    x->height = std::max(height(x->leftchild), height(x->rightchild)) + 1;

    return x;
}

// Rotate the root to the left.
template <typename T>
Node<T>* AVLTree<T>::rotate_left(Node<T>* x)
{
    Node<T>* y = x->rightchild;
    Node<T>* T2 = y->leftchild;

    y->leftchild = x;
    x->rightchild = T2;

    // Apply the node height formula.
    x->height = std::max(height(x->leftchild), height(x->rightchild)) + 1;
    y->height = std::max(height(y->leftchild), height(y->rightchild)) + 1;

    return y;
}

template <typename T>
Node<T>* AVLTree<T>::balance(Node<T>* root)
{
    if (root == nullptr)
    {
        return root;
    }

    // Apply the node height formula.
    // Update the root's height.
    root->height = std::max(height(root->leftchild), height(root->rightchild)) + 1;

    // Check for balance factor whether root is left or right-heavy.
    int balance = balance_factor(root);

    // If the root is left-heavy.
    if (balance > 1)
    {
        if (balance_factor(root->rightchild) < 0)
        {
            // Double rotation (Right-left rotation).
            root->rightchild = rotate_right(root->rightchild);
        }

        return rotate_left(root); // Single rotation.
    }

    // If the root is right-heavy.
    if (balance < -1)
    {
        if (balance_factor(root->leftchild) > 0)
        {
            // Double rotation (Left-right rotation).
            root->leftchild = rotate_left(root->leftchild);
        }

        return rotate_right(root); // Single rotation.
    }

    return root;
}

template <typename T>
Node<T>* AVLTree<T>::insert_helper(Node<T>* root, const T& item)
{
    // First step is the basic BST insertion.
    if (root == nullptr) 
    {
        // Done.
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

    // Second step is the fixing the AVL Tree's property from changed node.
    // Node's height is updated within balance.
    return balance(root);
}

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
        if (root->leftchild == nullptr) 
        {
            Node<T>* temp = root->rightchild; 
            delete root;
            return temp;
        }
        else if (root->rightchild == nullptr)
        {
            Node<T>* temp = root->leftchild;
            delete root;
            return temp;
        }

        Node<T>* temp    = min(root->rightchild);
        root->data       = temp->data;
        root->rightchild = remove_helper(root->rightchild, temp->data);
    }

    // Second step is the fixing the AVL Tree's property from changed node.
    return balance(root);
}

template <typename T>
Node<T>* AVLTree<T>::min(Node<T>* root)
{
    while (root->leftchild != nullptr)
    {
        root = root->leftchild;
    }
    return root;
}

// This uses post-order.

/*
 *  Pre-order :  <ROOT>  LEFT   RIGHT
 *  In-order  :  LEFT   <ROOT>  RIGHT
 *  Post-order:  LEFT    RIGHT <ROOT>
*/
template <typename T>
void AVLTree<T>::print_helper(Node<T>* root) const
{
    if (root == nullptr)
    {
        return;
    }

    print_helper(root->leftchild); // Call left sub-tree.
    print_helper(root->rightchild);// Call right sub-tree.
    std::cout << root->data << ' ';
}

template <typename T>
void AVLTree<T>::clear_helper(Node<T>* root)
{
    if (root == nullptr)
    {
        return;
    }

    clear_helper(root->leftchild);
    clear_helper(root->rightchild);

    delete root;
}

// Finding items are the same as in BST.
template <typename T>
T& AVLTree<T>::find_helper(Node<T>* root, const T& item) const
{
    if (root == nullptr)
    {
        T dummy{};
        return dummy;
    }

    if (item < root->data)
    {
        return find_helper(root->leftchild, item);
    }
    else if (item > root->data)
    {
        return find_helper(root->rightchild, item);
    }
    else
    {
        return root->data;
    }
}

#endif // AVLTREE_HPP
