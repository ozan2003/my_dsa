#ifndef NODE_HPP
#define NODE_HPP

template <typename T>
struct Node
{
	T data{};	         // Value of the node.
	Node* next{nullptr}; // Pointer to the next node.

	Node(const T& dat, Node* nxt = nullptr)
		: data{dat}, next{nxt}
	{}

};
#endif // NODE_HPP
