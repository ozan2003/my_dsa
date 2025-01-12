#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <algorithm>        // std::copy
#include <initializer_list> // std::initializer_list
#include <stdexcept>        // std::runtime_error

template <typename T>
class Queue
{
private:
    int m_max_size{};
    int m_front{0};
    int m_rear{-1};
    T*  m_list_array{};

public:
    Queue() = default;

    Queue(const int size)
        : m_max_size{size + 1}
    {
        if (size < 0)
        {
            throw std::invalid_argument("Queue size must be non-negative");
        }
        m_list_array = new T[m_max_size];
    }

    Queue(const Queue& other)
        : m_max_size{other.m_max_size},
          m_front{other.m_front},
          m_rear{other.m_rear},
          m_list_array{new T[other.m_max_size]}
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

    int length() const noexcept
    {
        return ((m_rear + m_max_size) - m_front + 1) % m_max_size;
    }

    const T& peek_front() const
    {
        if (length() == 0)
        {
            throw std::runtime_error("Queue is empty.");
        }

        return m_list_array[m_front];
    }

    void enqueue(const T& item)
    {
        if ((m_rear + 2) % m_max_size == m_front)
        {
            throw std::runtime_error("Queue is full.");
        }

        m_rear               = (m_rear + 1) % m_max_size;
        m_list_array[m_rear] = item;
    }

    T dequeue()
    {
        if (length() == 0)
        {
            throw std::runtime_error("Queue is empty.");
        }

        T temp = peek_front();

        m_front = (m_front + 1) % m_max_size;
        return temp;
    }

    int capacity() const noexcept
    {
        return m_max_size - 1;
    }

    bool empty() const noexcept
    {
        return length() == 0;
    }

    void clear() noexcept
    {
        m_front = 0;
        m_rear  = -1;
    }
};
#endif // QUEUE_HPP
