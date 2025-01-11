#ifndef NODE_HPP
#define NODE_HPP

template <typename T>
struct Node
{
    T     data{};
    Node* leftchild{nullptr};
    Node* rightchild{nullptr};

    Node() = default;

    Node(const T& dat, Node* left = nullptr, Node* right = nullptr)
        : data{dat}, leftchild{left}, rightchild{right}
    {
    }

    bool is_leaf() const
    {
        return leftchild == nullptr && rightchild == nullptr;
    }
};
#endif // NODE_HPP
