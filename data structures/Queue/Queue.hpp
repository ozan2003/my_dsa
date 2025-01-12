#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <algorithm>        // std::copy
#include <cstdint>          // std::int64_t
#include <initializer_list> // std::initializer_list
#include <stdexcept>        // std::runtime_error
#include <utility>          // std::swap

constexpr std::int64_t DEFAULT_QUEUE_SIZE{10};

template <typename T>
class Queue
{
public:
    using value_type = T;
    using size_type  = std::int64_t; // We're using -1 to represent the rear of
                                     // the queue. So we need a signed type.
    using difference_type = std::ptrdiff_t;
    using reference       = value_type&;
    using const_reference = const value_type&;
    using pointer         = value_type*;
    using const_pointer   = const value_type*;

private:
    size_type m_max_size{DEFAULT_QUEUE_SIZE};
    size_type m_front{0};
    size_type m_rear{-1};
    pointer   m_list_array{};

public:
    Queue() = default;

    Queue(const size_type size)
        : m_max_size{size + 1}
    {
        if (size < 0)
        {
            throw std::invalid_argument("Queue size must be non-negative");
        }
        m_list_array = new value_type[m_max_size];
    }

    Queue(const Queue& other)
        : m_max_size{other.m_max_size},
          m_front{other.m_front},
          m_rear{other.m_rear},
          m_list_array{new value_type[other.m_max_size]}
    {
        std::copy(other.m_list_array,
                  other.m_list_array + m_max_size,
                  m_list_array);
    }

    Queue& operator=(const Queue& other)
    {
        if (this != &other)
        {
            Queue temp(other);
            std::swap(m_max_size, temp.m_max_size);
            std::swap(m_front, temp.m_front);
            std::swap(m_rear, temp.m_rear);
            std::swap(m_list_array, temp.m_list_array);
        }
        return *this;
    }

    Queue(std::initializer_list<T> i_list)
        : Queue(static_cast<int>(i_list.size()))
    {
        for (const auto& item : i_list)
        {
            enqueue(item);
        }
    }

    Queue(Queue&& other) noexcept
        : m_max_size{other.m_max_size},
          m_front{other.m_front},
          m_rear{other.m_rear},
          m_list_array{other.m_list_array}
    {
        other.m_list_array = nullptr;
        other.m_max_size   = 0;
        other.m_front      = 0;
        other.m_rear       = -1;
    }

    Queue& operator=(Queue&& other) noexcept
    {
        if (this != &other)
        {
            delete[] m_list_array;

            m_max_size   = other.m_max_size;
            m_front      = other.m_front;
            m_rear       = other.m_rear;
            m_list_array = other.m_list_array;

            other.m_list_array = nullptr;
            other.m_max_size   = 0;
            other.m_front      = 0;
            other.m_rear       = -1;
        }
        return *this;
    }

    ~Queue()
    {
        delete[] m_list_array;
    }
    
    /**
     * @brief Returns the number of elements in the queue.
     * @return The number of elements in the queue.
     */
    size_type length() const noexcept
    {
        return ((m_rear + m_max_size) - m_front + 1) % m_max_size;
    }

    /**
     * @brief Returns the front element of the queue.
     * @return The front element of the queue.
     * 
     * @throws std::runtime_error if the queue is empty.
     */
    const_reference peek_front() const
    {
        if (length() == 0)
        {
            throw std::runtime_error("Queue is empty.");
        }

        return m_list_array[m_front];
    }

    /**
     * @brief Adds an element to the rear of the queue.
     * @param item The element to add to the queue.
     * 
     * @throws std::runtime_error if the queue is full.
     */
    void enqueue(const_reference item)
    {
        if ((m_rear + 2) % m_max_size == m_front)
        {
            throw std::runtime_error("Queue is full.");
        }

        m_rear               = (m_rear + 1) % m_max_size;
        m_list_array[m_rear] = item;
    }

    /**
     * @brief Removes the front element of the queue.
     * @return The front element of the queue.
     * 
     * @throws std::runtime_error if the queue is empty.
     */
    value_type dequeue()
    {
        if (length() == 0)
        {
            throw std::runtime_error("Queue is empty.");
        }

        value_type temp = peek_front();

        m_front = (m_front + 1) % m_max_size;
        return temp;
    }

    /**
     * @brief Returns the capacity of the queue.
     * @return The capacity of the queue.
     */
    size_type capacity() const noexcept
    {
        return m_max_size - 1;
    }

    /**
     * @brief Returns true if the queue is empty.
     * @return True if the queue is empty.
     */
    bool empty() const noexcept
    {
        return length() == 0;
    }

    /**
     * @brief Clears the queue.
     */
    void clear() noexcept
    {
        m_front = 0;
        m_rear  = -1;
    }
};
#endif // QUEUE_HPP
