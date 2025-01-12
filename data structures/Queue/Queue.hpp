#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <algorithm>        // std::copy
#include <cstdint>          // std::int64_t
#include <initializer_list> // std::initializer_list
#include <stdexcept>        // std::runtime_error
#include <utility>          // std::swap, std::exchange

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

    pointer m_list_array{};

public:
    /**
     * @brief Default constructor.
     */
    Queue() = default;

    /**
     * @brief Constructs a queue with the given size.
     * @param size The size of the queue.
     *
     * @throws std::invalid_argument if the size is negative.
     */
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
        : m_max_size{std::exchange(other.m_max_size, 0)},
          m_front{std::exchange(other.m_front, 0)},
          m_rear{std::exchange(other.m_rear, -1)},
          m_list_array{std::exchange(other.m_list_array, nullptr)}
    {
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
        /*
         * For circular queues, we can't simply subtract front from rear
         * because rear might be "behind" front in the array. The formula
         * handles wraparound:
         * 1. Add m_max_size to ensure positive number before modulo
         * 2. Add 1 because rear points to last element (not one past it)
         * 3. Use modulo to handle wraparound
         */
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
        /*
         * The check (m_rear + 2) % m_max_size == m_front detects if queue is
         * full We use +2 because:
         * 1. +1 for the next position
         * 2. +1 for the empty slot we maintain
         */
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
        /*
         * We first get the front element, then move the front pointer
         * forward circularly using modulo
         */
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
     * @brief Clears the queue by resetting pointers to initial state
     */
    void clear() noexcept
    {
        /*
         * No need to actually clear memory since front/rear pointers
         * control what's considered "in" the queue
         */
        m_front = 0;
        m_rear  = -1;
    }
};
#endif // QUEUE_HPP
