// This is an iterator class for convenient use of STL algorithms.
#ifndef ARRAYLISTITERATOR_HPP
#define ARRAYLISTITERATOR_HPP

#include <cstddef>  // std::ptrdiff_t
#include <iterator> // std::random_access_iterator_tag

// This class is used in order to be compliant with the STL algorithms.
template <typename T>
class ArrayListIterator
{
public:
    // std::random_access_iterator_tag since we're using array, which is a random access container.
    using iterator_category = std::random_access_iterator_tag;
    using difference_type   = std::ptrdiff_t;
    using value_type        = T;
    using pointer           = T*;
    using reference         = T&;

    // Default constructor.
    ArrayListIterator() = default;

    // Constructor with pointer.
    ArrayListIterator(pointer ptr)
        : m_ptr{ptr}
    {
    }

    // To move one position forward. (Pre-increment)
    ArrayListIterator& operator++()
    {
        ++m_ptr;
        return *this;
    }

    // To move one position backward. (Pre-decrement)
    ArrayListIterator& operator--()
    {
        --m_ptr;
        return *this;
    }

    // To move one position forward. (Post-increment)
    ArrayListIterator& operator++(int)
    {
        ArrayListIterator temp{*this}; // Save the current iterator position.
        ++m_ptr;
        return temp;
    }

    // To move one position backward. (Post-decrement)
    ArrayListIterator& operator--(int)
    {
        ArrayListIterator temp{*this}; // Save the current iterator position.
        --m_ptr;
        return temp;
    }

    // To get the value at the current iterator position.
    reference operator*() const
    {
        return *m_ptr;
    }

    // To point at the current iterator position.
    pointer operator->()
    {
        return m_ptr;
    }

    // To compare iterators for equality.
    friend bool operator==(const ArrayListIterator& it1, const ArrayListIterator& it2)
    {
        return it1.m_ptr == it2.m_ptr;
    }

    // To compare iterators for inequality.
    friend bool operator!=(const ArrayListIterator& it1, const ArrayListIterator& it2)
    {
        return !(it1 == it2);
    }

    // To move the iterator forward by a certain amount.
    friend ArrayListIterator operator+(const ArrayListIterator& it, difference_type n)
    {
        return ArrayListIterator{it.m_ptr + n};
    }

    // To get the distance between two iterators.
    friend difference_type operator-(const ArrayListIterator& it1, const ArrayListIterator& it2)
    {
        return it1.m_ptr - it2.m_ptr;
    }

    // To move the iterator forward by a certain amount.
    friend ArrayListIterator& operator+=(ArrayListIterator& it, ArrayListIterator::difference_type n)
    {
        it.m_ptr += n;
        return it;
    }

    // To move the iterator backward by a certain amount.
    friend ArrayListIterator& operator-=(ArrayListIterator& it, difference_type n)
    {
        it.m_ptr -= n;
        return it;
    }

    // To get the value at a certain position.
    reference operator[](difference_type n)
    {
        return *(m_ptr + n);
    }

    // Comparing the iterators.
    friend bool operator<(const ArrayListIterator& it1, const ArrayListIterator& it2)
    {
        return it1.m_ptr < it2.m_ptr;
    }

    friend bool operator>(const ArrayListIterator& it1, const ArrayListIterator& it2)
    {
        return operator<(it2, it1); // Return the negated value of operator<.
    }

    friend bool operator<=(const ArrayListIterator& it1, const ArrayListIterator& it2)
    {
        return !(operator>(it1, it2)); // Return the negated value of operator>.
    }

    friend bool operator>=(const ArrayListIterator& it1, const ArrayListIterator& it2)
    {
        return !(operator<(it1, it2)); // Return the negated value of operator<.
    }

private:
    pointer m_ptr{nullptr};
};
#endif // ARRAYLISTITERATOR_HPP
