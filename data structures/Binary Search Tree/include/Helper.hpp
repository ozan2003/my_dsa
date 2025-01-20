#ifndef HELPER_HPP
#define HELPER_HPP

#include "Node.hpp"

#include <iostream>

namespace helper
{
    /**
     * Finds the minimum value node in the tree.
     *
     * @param node The root node of the tree.
     * @return The node containing the minimum value.
     */
    template <typename T>
    Node<T>* min(Node<T>* node)
    {
        if (node == nullptr || node->leftchild == nullptr)
        {
            return node;
        }
        return min(node->leftchild);
    }

    /**
     * Finds the maximum value node in the tree.
     *
     * @param node The root node of the tree.
     * @return The node containing the maximum value.
     */
    template <typename T>
    Node<T>* max(Node<T>* node)
    {
        if (node == nullptr || node->rightchild == nullptr)
        {
            return node;
        }
        return max(node->leftchild);
    }

    /**
     * Inserts a new item into the tree.
     *
     * @param node The root node of the tree.
     * @param item The item to be inserted.
     * @return The new root after insertion.
     */
    template <typename T>
    Node<T>* insert(Node<T>* node, const T& item)
    {
        if (node == nullptr)
        {
            return new Node<T>{item};
        }

        if (item < node->data)
        {
            node->leftchild = insert(node->leftchild, item);
        }
        else
        {
            node->rightchild = insert(node->rightchild, item);
        }

        return node;
    }

    /**
     * Removes an item from the tree.
     *
     * @param node The root node of the tree.
     * @param item The item to be removed.
     * @return The new root after removal.
     */
    template <typename T>
    Node<T>* remove(Node<T>* node, const T& item)
    {
        if (node == nullptr)
        {
            return nullptr;
        }

        if (item < node->data)
        {
            node->leftchild = remove(node->leftchild, item);
        }
        else if (item > node->data)
        {
            node->rightchild = remove(node->rightchild, item);
        }
        else
        {
            if (node->leftchild == nullptr)
            {
                Node<T>* temp = node->rightchild;
                delete node;
                return temp;
            }

            if (node->rightchild == nullptr)
            {
                Node<T>* temp = node->leftchild;
                delete node;
                return temp;
            }

            Node<T>* temp    = min(node->rightchild);
            node->data       = temp->data;
            node->rightchild = remove_min(node->rightchild);
        }

        return node;
    }

    /**
     * Finds an item in the tree.
     *
     * @param node The root node of the tree.
     * @param item The item to find.
     * @return The node containing the item, or nullptr if not found.
     */
    template <typename T>
    Node<T>* find(Node<T>* node, const T& item)
    {
        if (node == nullptr)
        {
            return nullptr;
        }

        if (item < node->data)
        {
            return find(node->leftchild, item);
        }

        if (item > node->data)
        {
            return find(node->rightchild, item);
        }

        return node;
    }

    /**
     * Prints the tree in-order.
     *
     * @param node The root node of the tree.
     * @param os The output stream to print to.
     */
    template <typename T>
    void print(Node<T>* node, std::ostream& os)
    {
        if (node == nullptr)
        {
            return;
        }

        print(node->leftchild, os);
        os << node->data << ' ';
        print(node->rightchild, os);
    }

    /**
     * Clears all nodes in the tree.
     *
     * @param node The root node of the tree.
     */
    template <typename T>
    void clear(Node<T>* node)
    {
        if (node == nullptr)
        {
            return;
        }

        clear(node->leftchild);
        clear(node->rightchild);
        delete node;
    }

    /**
     * Creates a deep copy of the tree.
     *
     * @param node The root node of the tree to copy.
     * @return The root node of the new copy.
     */
    template <typename T>
    Node<T>* deep_copy(Node<T>* node)
    {
        if (node == nullptr)
        {
            return nullptr;
        }

        Node<T>* new_node    = new Node<T>{node->data};
        new_node->leftchild  = deep_copy(node->leftchild);
        new_node->rightchild = deep_copy(node->rightchild);

        return new_node;
    }

} // namespace helper
#endif // HELPER_HPP
