#ifndef BINSEARCHTREE_HPP
#define BINSEARCHTREE_HPP

#include "Node.hpp"

#include <iostream> // std::cout

template <typename T>
class BinSearchTree
{
private:
    Node<T>* m_root{nullptr}; // The root of the BST.
    int m_count{};            // Number of the nodes in the BST.

    // Helper functions.
    void     clear_helper(Node<T>*);
    Node<T>* insert_helper(Node<T>*, const T&);
    T        find_helper(Node<T>*, const T&) const;
    Node<T>* remove_helper(Node<T>*, const T&);
    void     print_helper(Node<T>*, int) const;
    Node<T>* remove_min(Node<T>*);
    Node<T>* min(Node<T>*);


public:
    BinSearchTree() = default;

    ~BinSearchTree()
    {
        clear_helper(m_root);
    }

    // Reinitialize tree.
    void clear()
    {
        clear_helper(m_root);

        m_root = nullptr;
        m_count = 0;
    }

    // Insert a record into the tree.
    void insert(const T& item)
    {
        m_root = insert_helper(m_root, item);
        m_count++;
    }

    // Remove an item from the tree.
    // Returns the item removed, or 0 if there is none.
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

    T find(const T& item) const
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
            print_helper(m_root, 0);
        }
        
    }
};

template <typename T>
T BinSearchTree<T>::find_helper(Node<T>* root, const T& item) const
{
    if (root == nullptr)
    {
        return NULL; // Empty tree or leaf.
    }
    
    if (item < root->data) // Check left if item is smaller than root.
    {
        return find_helper(root->leftchild, item);
    }
    else if (item > root->data) // Check right if item is greater than root.
    {
        return find_helper(root->rightchild, item);
    }
    else
    {
        return root->data; // Found it.
    }
}

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

template <typename T>
Node<T>* BinSearchTree<T>::remove_helper(Node<T>* root, const T& item)
{
    if (root == nullptr) // item is not in tree
    {
        return nullptr;//return NULL;
    }
    else if (item < root->data)
    {
        root->leftchild = remove_helper(root->leftchild, item);
    }
    else if (item > root->data)
    {
        root->rightchild = remove_helper(root->rightchild, item);
    }
    else // Found, remove it.
    {
        Node<T>* temp = root;

        if (root->leftchild == nullptr) // Only a right child.
        {
            root = root->rightchild;    // so point to right.
            delete temp;
        }
        else if (root->rightchild == nullptr) // Only a left child.
        {
            root = root->leftchild;    // so point to right.
            delete temp;
        }
        else // Both children are non-empty.
        {
            temp = min(root->rightchild);//Node<T>* temp = min(root->rightchild);

            root->data = temp->data;//root = temp->data;
            root->rightchild = remove_min(root->rightchild);

            delete temp;
        }
    }

    return root;
}

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

template <typename T>
void BinSearchTree<T>::print_helper(Node<T>* root, int level) const
{
    if (root == nullptr)
    {
        return;
    }

    print_helper(root->leftchild, level + 1);

    for (int i{}; i < level; ++i)
    {
        std::cout << ' ';
    }
    std::cout << root->data << '\n';

    print_helper(root->rightchild, level + 1);
}

#endif // BINSEARCHTREE_HPP
