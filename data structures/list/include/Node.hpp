#ifndef NODE_HPP
#define NODE_HPP

template <typename T>
struct Node
{
    Node* prev{nullptr}; // Pointer to the previous node.
    T     data{};        // The value the node holds.
    Node* next{nullptr}; // Pointer to the next node.

    Node(const T& dat, Node* pr = nullptr, Node* nxt = nullptr)
        : prev{pr}, data{dat}, next{nxt}
    {
    }
};

#endif // NODE_HPP
