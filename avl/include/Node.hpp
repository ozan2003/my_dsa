#ifndef NODE_HPP
#define NODE_HPP

template <typename T>
struct Node
{
    T     data{};
    Node* leftchild{nullptr};
    Node* rightchild{nullptr};
    /*
     *  Height of the node is the longest path down to a leaf.
     *  Height = max(height(rightchild), height(leftchild)) + 1
     */
    int height{};

    Node() = default;

    Node(const T& dat, Node* left = nullptr, Node* right = nullptr)
        : data{dat}, leftchild{left}, rightchild{right}
    {
    }

    // Check whether node has childs.
    bool isleaf() const
    {
        return !(leftchild && rightchild);
    }
};
#endif // NODE_HPP
