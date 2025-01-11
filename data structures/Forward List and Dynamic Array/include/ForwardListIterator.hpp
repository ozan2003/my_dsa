// This is an iterator class for convenient use of STL algorithms.
#ifndef FORWARDLISTITERATOR_HPP
#define FORWARDLISTITERATOR_HPP

#include "Node.hpp"

#include <cstddef>  // std::ptrdiff_t
#include <iterator> // std::forward_iterator_tag

template <typename T>
class ForwardListIterator
{
public:
    // std::forward_iterator_tag since we can only move forward in a singly linked list.
    using iterator_category = std::forward_iterator_tag;
    using difference_type   = std::ptrdiff_t;
    // The iterator allows direct access to the data via value or reference.
    // The pointer is used to point at the current iterator position.
    // This is done to allow the user to easily use the STL algorithms.
    using value_type = T; 
    using pointer   = Node<T>*; 
    using reference = T&; 

    // Default constructor.
    ForwardListIterator() = default;

    // Constructor with pointer.
    // Explicit to avoid implicit conversion from Node* to ForwardListIterator.
    explicit ForwardListIterator(pointer ptr)
        : m_ptr{ptr}
    {
    }

    // Access the data directly at the current iterator position.
    reference operator*() const
    {
        return m_ptr->data; // Access data member of the Node
    }

    // To point at the current iterator position (unchanged).
    pointer operator->()
    {
        return m_ptr;
    }

    // To move one position forward. (Pre-increment)
    ForwardListIterator& operator++()
    {
        m_ptr = m_ptr->next;
        return *this;
    }

    // To move one position forward. (Post-increment)
    ForwardListIterator operator++(int)
    {
        ForwardListIterator tmp = *this; // Save the current iterator position.
        ++(*this);
        return tmp;
    }

    // To compare iterators for equality.
    bool operator==(const ForwardListIterator& other) const
    {
        return m_ptr == other.m_ptr;
    }

    // To compare iterators for inequality.
    bool operator!=(const ForwardListIterator& other) const
    {
        return m_ptr != other.m_ptr;
    }

private:
    pointer m_ptr{nullptr};
};
#endif // FORWARDLISTITERATOR_HPP
