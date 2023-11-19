#ifndef STACK_HPP
#define STACK_HPP

#define INITIAL_SIZE 2

// The stack is a list-like structure in which elements may be inserted or removed
// from only one end.
template <typename T>
class Stack
{
private:
    int m_size{INITIAL_SIZE};      // Current size of stack. This cannot be changed once initialized.
    int m_top{};                   // Index of top element.
    T*  m_list_array{};            // The stack is implemented as an array rather than linked-list.

public:
    Stack() = default;

    Stack(const int size)
        : m_size{size}, m_list_array{new T[m_size]}
    {
    }

    ~Stack()
    {
        delete[] m_list_array;
    }

    void clear() noexcept
    {
        m_top = 0;
    }

    void push(const T& item)
    {
        if (m_top >= m_size)
        {
            throw "Stack is full.\n";
        }
        // Increase index by one and assign "item".
        m_list_array[m_top++] = item;
    }

    T pop() noexcept
    {
        if (!empty())
        {
            // Decrease index by one.
            return m_list_array[--m_top];
        }
    }

    // Only the top element is accessible.
    const T& peek() const
    {
        if (m_top == 0)
        {
            throw "Stack is empty.\n";
        }
        return m_list_array[m_top - 1];
    }

    int size() const noexcept
    {
        return m_top;
    }

    bool empty() const noexcept
    {
        return m_top == 0;
    }
};

#endif // STACK_HPP
