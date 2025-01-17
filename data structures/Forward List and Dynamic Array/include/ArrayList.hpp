// An array-based approach of list.
#ifndef ARRAYLIST_HPP
#define ARRAYLIST_HPP

#include "ArrayListIterator.hpp"
#include "List.hpp"

#include <iostream> // operator<<
#include <utility>  // std::move, std::exchange

constexpr std::size_t INITIAL_SIZE{2};
constexpr std::size_t GROWTH_FACTOR{2};

template <typename T>
class ArrayList : public List<T>
{
public:
    using value_type      = typename List<T>::value_type;
    using size_type       = typename List<T>::size_type;
    using reference       = typename List<T>::reference;
    using const_reference = typename List<T>::const_reference;
    using pointer         = typename List<T>::pointer;

private:
    size_type m_capacity{};   // Maximum size of list.
    size_type m_size{};       // Current number of list elements.
    pointer   m_list_array{}; // Array holding list of elements.

    void reserve()
    {
        if (m_capacity == 0)
        {
            m_capacity = INITIAL_SIZE;
        }
        else
        {
            m_capacity *= GROWTH_FACTOR;
        }

        pointer temp =
            new value_type[m_capacity]; // Allocate new array in the heap.

        for (size_type i{}; i < m_size; ++i)
        {
            temp[i] =
                std::move(m_list_array[i]); // Move all items of original array.
        }

        delete[] m_list_array; // Get rid of the original array.
        m_list_array = temp;   // "temp" is our new array now.
    }

public:
    ArrayList() = default;

    ArrayList(const size_type size, const_reference value = value_type{})
        : m_capacity{size * GROWTH_FACTOR},
          m_size{size},
          m_list_array{new value_type[m_capacity]{value}}
          // ArrayList elements are initialized by value.
    {
    }

    ArrayList(const std::initializer_list<value_type> i_list)
        : ArrayList(i_list.size())
    // Don't use braces as initializer_list constructor uses it.
    // Otherwise this constructor would call itself.
    {
        for (size_type count{}; const auto& item : i_list)
        {
            m_list_array[count] = std::move(item);
            count++;
        }
    }

    // Copy constructor.
    /*
     * Rule of Three:
     * If a class requires a user-defined destructor,
     * a user-defined copy constructor,
     * or a user-defined copy assignment operator,
     * it almost certainly requires all three.
     */
    ArrayList(const ArrayList& other)
        : List<value_type>{},
          m_capacity{other.m_capacity},
          m_size{other.m_size},
          m_list_array{new value_type[other.m_capacity]{}}
    {
        for (size_type i{}; i < m_size; ++i)
        {
            m_list_array[i] = other.m_list_array[i];
        }
    }

    // Copy assignment operator.
    ArrayList& operator=(const ArrayList& other)
    {
        if (this != &other)
        {
            delete[] m_list_array;

            m_capacity   = other.m_capacity;
            m_size       = other.m_size;
            m_list_array = new value_type[other.m_capacity];

            for (size_type i{}; i < m_size; ++i)
            {
                m_list_array[i] = other.m_list_array[i];
            }
        }
        return *this;
    }

    // Move constructor.
    /*
     * Rule of Three becomes Rule of Five with C++11:
     * If a class requires a user-defined destructor,
     * a user-defined copy constructor,
     * a user-defined copy assignment operator,
     * or a user-defined move constructor,
     * or a user-defined move assignment operator,
     * it almost certainly requires all five.
     */
    ArrayList(ArrayList&& other) noexcept
        : List<value_type>{},
          // Member-wise move.
          // Replace the value of "other.m_capacity" with 0 and return the old
          // value.
          m_capacity{std::exchange(other.m_capacity, 0)},
          m_size{std::exchange(other.m_size, 0)},
          m_list_array{std::exchange(other.m_list_array, nullptr)}
    {
    }

    // Move assignment operator.
    ArrayList& operator=(ArrayList&& other) noexcept
    {
        if (this != &other)
        {
            delete[] m_list_array; // Clean up.

            // Member-wise move and reset.
            m_capacity   = std::exchange(other.m_capacity, 0);
            m_size       = std::exchange(other.m_size, 0);
            m_list_array = std::exchange(other.m_list_array, nullptr);
        }
        return *this;
    }

    ~ArrayList()
    {
        delete[] m_list_array;
        m_list_array = nullptr; // Freeing pointer doesn't make it nullptr.
    }

    void clear()
    {
        delete[] m_list_array;
        m_list_array = nullptr;
        m_capacity   = 0;
        m_size       = 0;
    }

    // Insert "item" at given position.
    void insert(const size_type pos, const_reference item) override
    {
        if (pos > m_size)
        {
            throw std::out_of_range{"Position out of range."};
        }

        if (m_size == m_capacity)
        {
            reserve();
        }
        // assert(pos < m_size && "Out of range.\n");

        for (size_type s{m_size}; pos < s; --s) // Shift elements up...
        {
            m_list_array[s] = m_list_array[s - 1]; // ...to make room.
        }
        /// DEMONSTRATION
        // ┌────┬────┬────┬────┬────┬────┬────┐
        // │i[0]│i[1]│i[2]│i[3]│i[4]│i[5]│i[6]│     // INDEXES
        // ├────┼────┼────┼────┼────┼────┼────┤
        // │10  │20  │30  │40  │50  │60  │    │     // ITEMS
        // ├────┼────┼────┼────┼────┼────┼────┤
        // │    │10  │20  │30  │40  │50  │60  │     // SHIFT ELEMENTS UP
        // ├────┼────┼────┼────┼────┼────┼────┤
        // │item│10  │20  │30  │40  │50  │60  │     // INSERT "item"
        // └────┴────┴────┴────┴────┴────┴────┘
        //
        m_list_array[pos] = std::move(item); // Insert "item" at position "pos".

        m_size++; // Increment list size.
    }

    // Append "item".
    void append(const_reference item) override
    {
        if (m_size == m_capacity)
        {
            reserve();
        }
        // assert(m_size < m_capacity && "List capacity exceeded.\n");

        m_list_array[m_size] =
            std::move(item); // Append "item" at the end of the list.
        m_size++;
    }

    // Remove and return the current element.
    void remove(const size_type pos) override
    {
        if (pos >= m_size)
        {
            throw std::out_of_range{"No element at position."};
        }
        // assert(pos < m_size && "No element.\n");

        // T item = m_list_array[pos]; // Copy the item.

        // m_size - 1, because we're dealing with array indexes (array[size] is
        // out of bounds).
        for (size_type i{pos}; i < m_size - 1; ++i)
        {
            m_list_array[i] = m_list_array[i + 1]; // Shift elements down.
        }
        /// DEMONSTRATION
        // ┌────┬────┬────┬────┬────┬────┬────┐
        // │i[0]│i[1]│i[2]│i[3]│i[4]│i[5]│i[6]│     // INDEXES
        // ├────┼────┼────┼────┼────┼────┼────┤
        // │10  │item│20  │30  │40  │50  │60  │     // ITEMS
        // ├────┼────┼────┼────┼────┼────┼────┤
        // │10  │20  │30  │40  │50  │60  │... │     // SHIFT ELEMENTS DOWN
        // └────┴────┴────┴────┴────┴────┴────┘
        //
        --m_size; // Decrement size.

        // return item;
    }

    // Return list size.
    size_type size() const override
    {
        return m_size;
    }

    bool empty() const override
    {
        return size() == 0;
    }

    reference operator[](const size_type pos) override
    {
        return m_list_array[pos];
    }

    const_reference operator[](const size_type pos) const override
    {
        return m_list_array[pos];
    }

    reference at(const size_type pos) override
    {
        if (pos >= m_size)
        {
            throw std::out_of_range{"Index out of range."};
        }
        return m_list_array[pos];
    }

    // Return iterator at beginning of list.
    ArrayListIterator<value_type> begin() const
    {
        // m_list_array points to the first element.
        return ArrayListIterator<value_type>{m_list_array};
    }

    // Return iterator past end of list.
    ArrayListIterator<value_type> end() const
    {
        // m_list_array + m_size points to the element past the last one.
        return ArrayListIterator<value_type>{m_list_array + m_size};
    }
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const ArrayList<T>& list)
{
    for (const auto& item : list)
    {
        os << item << ' ';
    }
    return os;
}

#endif // ARRAYLIST_HPP
