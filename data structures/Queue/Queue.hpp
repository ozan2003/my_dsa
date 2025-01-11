#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <initializer_list> // std::initializer_list
#include <stdexcept>        // std::runtime_error

template <typename T>
class Queue
{
private:
    int m_max_size{};
    int m_front{1};
    int m_rear{};
    T*  m_list_array{};

public:
    Queue() = default;

    Queue(const int size)
        : m_max_size{size + 1}, m_list_array{new T[m_max_size]}
    {
    }

    Queue(std::initializer_list<T> i_list)
        : Queue(static_cast<int>(i_list.size()))
    {
        for (const auto& item : i_list)
        {
            enqueue(item);
        }
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
};
#endif // QUEUE_HPP
