#ifndef HELPER_HPP
#define HELPER_HPP

#include "BinSearchTree.hpp"
#include "Node.hpp"

#include <iostream>

namespace helper
{
    /**
     * Removes the node with the specified item from the tree.
     * If the item is not found, the tree remains unchanged.
     *
     * @param node The node node of the tree.
     * @param item The item to be removed.
     * @return The node node of the modified binary search tree.
     */
    template <typename T>
    Node<T>* remove(Node<T>* node, const T& item)
    {
        if (node == nullptr) // item is not in the tree
        {
            return nullptr; // return NULL;
        }
        else if (item < node->data)
        {
            node->leftchild = remove(node->leftchild, item);
        }
        else if (item > node->data)
        {
            node->rightchild = remove(node->rightchild, item);
        }
        else // Found the item, remove it.
        {
            // Maintain the BST property.
            Node<T>* temp = node;

            /**
             * If the node to be removed has only one child, then we can simply
             * replace the node with its child.
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
            // If the node to be removed has two children, then we replace the
            // node with the minimum value in the right subtree.
            else
            {
                temp = min(node->rightchild); // Find the minimum value in the
                                              // right subtree.

                node->data = temp->data; // Replace the node's data with the
                                         // minimum value.
                node->rightchild =
                    remove_min(node->rightchild); // Remove the minimum value
                                                  // from the right subtree.

                delete temp;
            }
        }

        return node;
    }

    /**
     * @brief Recursively clears the tree starting from the given
     * node.
     *
     * @tparam T The type of elements stored in the tree.
     * @param node The node node of the tree.
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
     * @brief Helper function to print the elements of the tree in
     * in-order traversal.
     *
     * @param node The node node of the tree.
     */
    template <typename T>
    void print(Node<T>* node, std::ostream& os)
    {
        if (node == nullptr)
        {
            return;
        }

        // In-order traversal.
        print(node->leftchild, os);
        os << node->data << ' ';
        print(node->rightchild, os);
    }

    /**
     * @brief Inserts a new node with the given item into the tree
     * 
     * @param node The root node of the subtree
     * @param item The item to be inserted
     * @return Node<T>* The root node of the modified subtree
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
            // Insert to the left subtree if item is less than node
            node->leftchild = insert(node->leftchild, item);
        }
        else
        {
            // Insert to the right subtree if item is greater than or equal
            node->rightchild = insert(node->rightchild, item);
        }
        return node;
    }
} // namespace helper
#endif // !HELPER_HPP
