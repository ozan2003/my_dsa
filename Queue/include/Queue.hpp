#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <stdexcept> // std::overflow_error, std::underflow_error

constexpr int default_size{2};

/*
 * Like the stack, the queue is a list-like structure that provides restricted access to
 * its elements. Queue elements may only be inserted at the back (called enqueue) and 
 * removed from the front (called dequeue).
 */

/* The array's elements are numbered from 0 to size - 1, 
 * and position size−1 is defined to immediately precede position 0 
 * (which is equivalent to position size % size).
 */ 
// The queue is implemented as circular.
template <typename T>
class Queue
{
private:
    int m_size;  // m_size is used to control the circular motion of the queue 
                 // (it is the base for the modulus operator).
    int m_front; // position of the front element.
    int m_back;  // position of the back element.
    T*  m_list_array;

public:
    // Make list array one position larger for empty slot.
    Queue(const unsigned size = default_size)
        : m_size{static_cast<int>(size) + 1}, m_front{1}, m_back{0}, m_list_array{new T[m_size]}
    {
    }

    ~Queue()
    {
        delete[] m_list_array;
    }

    void clear() noexcept
    {
        // Reinitialize.
        m_front = 1;
        m_back = 0;

        // --------------------------------------------
        // ^         ^
        // back  front

    }

    int length() const noexcept
    {
        return (m_back - m_front + m_size) % m_size;
    }

    // Increment the back pointer.
    void enqueue(const T& item)
    {
        if ((m_back + 2) % m_size == m_front)
        {
            throw std::overflow_error("Queue is full.\n");
        }

        m_back = (m_back + 1) % m_size; // Circular increment.
        m_list_array[m_back] = item;
    }

    // Increment the front pointer.
    // Take element out.
    T dequeue()
    {
        if (length() < 0)
        {
            throw std::underflow_error("Queue is empty.\n");
        }

        T temp = m_list_array[m_front];

        m_front = (m_front + 1) % m_size; // Circular increment.

        return temp;
    }

    const T& peek_front() const
    {
        if (length() < 0)
        {
            throw std::underflow_error("Queue is empty.\n");
        }

        return m_list_array[m_front];
    }
};


#endif // QUEUE_HPP
