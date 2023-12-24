#ifndef NODE_HPP
#define NODE_HPP

template <typename T>
struct Node
{
    T data{};
    Node* leftchild{nullptr};
    Node* rightchild{nullptr};

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
