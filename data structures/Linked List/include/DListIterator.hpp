// An iterator class for taking advantage of the Modern C++ STL algorithms.
#ifndef DLISTITERATOR_HPP
#define DLISTITERATOR_HPP

#include "Node.hpp"

#include <cstddef>  // std::ptrdiff_t
#include <iterator> // std::bidirectional_iterator_tag

template <typename T>
class DListIterator
{
public:
    // Bidirectional iterator because its a doubly linked list.
    // It can move forward and backward.
    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type   = std::ptrdiff_t;
    // The iterator allows direct access to the data via value or reference.
    // The pointer is used to point at the current iterator position.
    // This is done to allow the user to easily use the STL algorithms.
    using value_type = T;
    using pointer    = Node<T>*;
    using reference  = T&;

private:
    pointer m_ptr{nullptr};

public:
    DListIterator() = default;

    // Explicit because we don't want the compiler to do any implicit conversions.
    explicit DListIterator(pointer ptr)
        : m_ptr{ptr}
    {
    }

    // Dereference operator.
    reference operator*() const
    {
        return m_ptr->data; // Return the data of the current node.
    }

    // Pointing at the current iterator position.
    pointer operator->() const
    {
        return m_ptr;
    }

    // Prefix increment operator.
    DListIterator& operator++()
    {
        m_ptr = m_ptr->next; // Move to the next node.
        return *this;
    }

    // Postfix increment operator.
    DListIterator operator++(int)
    {
        DListIterator tmp{*this}; // Create a copy of the current iterator.
        ++(*this);                // Move to the next node.
        return tmp;               // Return the copy of the original iterator.
    }

    // Prefix decrement operator.
    DListIterator& operator--()
    {
        m_ptr = m_ptr->prev; // Move to the previous node.
        return *this;
    }

    // Postfix decrement operator.
    DListIterator operator--(int)
    {
        DListIterator tmp{*this}; // Create a copy of the current iterator.
        --(*this);                // Move to the previous node.
        return tmp;               // Return the copy of the original iterator.
    }

    // Equality operator.
    bool operator==(const DListIterator& other) const
    {
        return m_ptr == other.m_ptr; // Compare the pointers.
    }

    // Inequality operator.
    bool operator!=(const DListIterator& other) const
    {
        return !(*this == other); // Reuse the equality operator.
    }
};

#endif // DLISTITERATOR_HPP