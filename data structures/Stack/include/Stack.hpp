#ifndef STACK_HPP
#define STACK_HPP

#include <cstddef>   // std::size_t
#include <memory>    // std::unique_ptr
#include <stdexcept> // std::out_of_range
#include <utility>   // std::move, std::exchange

constexpr std::size_t DEFAULT_SIZE{5};  // Default size of the stack.
constexpr std::size_t RESIZE_FACTOR{2}; // Resize factor of the stack.

template <typename T>
class Stack
{
public:
    using value_type      = T;
    using size_type       = std::size_t;
    using reference       = T&;
    using const_reference = const T&;

private:
    size_type                     m_size{DEFAULT_SIZE};           // Size of the stack.
    std::unique_ptr<value_type[]> m_data{new value_type[m_size]}; // Pointer to the stack.
    size_type                     m_top{};                        // Index of the top of the stack.

    void resize()
    {
        m_size *= RESIZE_FACTOR; // Increase the size.

        if (m_size == 0) // If the size is zero.
        {
            m_size = DEFAULT_SIZE; // Give it an initial size.
        }

        auto temp = std::make_unique<value_type[]>(m_size); // Create a new stack with the new size.

        // Move the items from the old stack to the new stack.
        for (size_type i{}; i < m_size; ++i)
        {
            temp[i] = std::move(m_data[i]);
        }

        m_data.reset();           // Destroy the old stack.
        m_data = std::move(temp); // Move the new stack to the old stack.
    }

public:
    // Default constructor.
    Stack() = default;

    // Constructor with given size.
    Stack(const size_type size)
        : m_size{size}, m_data{new T[m_size]}
    {
    }

    // Destructor.
    ~Stack() = default;

    // Copy constructor.
    Stack(const Stack<value_type>& other)
        : m_size{other.m_size}, m_data{new value_type[m_size]}
    {
        // Copy the items from the other stack to this stack.
        for (size_type i{}; i < m_size; ++i)
        {
            m_data[i] = other.m_data[i];
        }
    }

    // Copy assignment operator.
    Stack& operator=(const Stack<value_type>& other)
    {
        if (this != &other) // Check for self-assignment.
        {
            m_data.reset(); // Delete the old stack.

            m_size = other.m_size;           // Copy the size.
            m_data = new value_type[m_size]; // Create a new stack with the given size.

            // Copy the items from the other stack to this stack.
            for (size_type i{}; i < m_size; ++i)
            {
                m_data[i] = other.m_data[i];
            }
        }
        return *this; // Return this stack.
    }

    // Move constructor.
    Stack(Stack<value_type>&& other) noexcept
        : m_size{std::exchange(other.m_size, 0)}, m_data{std::exchange(other.m_data, nullptr)}
    {
    }

    // Move assignment operator.
    Stack& operator=(Stack<value_type>&& other) noexcept
    {
        if (this != &other) // Check for self-assignment.
        {
            delete[] m_data; // Delete the old stack.

            // Member-wise move.
            m_size = std::exchange(other.m_size, 0);
            m_data = std::exchange(other.m_data, {});
        }
        return *this; // Return this stack.
    }

    // Add item to the top of the stack.
    void push(const_reference item) noexcept
    {
        // If the stack is full, resize it.
        if (m_top >= m_size)
        {
            resize();
        }
        m_data[m_top++] = item; // Add item to the top of the stack.
    }

    // Clear the stack.
    void clear() noexcept
    {
        m_top = 0; // Reset the index of the top of the stack.
    }

    // Remove item from the top of the stack.
    value_type pop()
    {
        if (empty()) // If the stack is empty.
        {
            throw std::out_of_range("Stack is empty!");
        }
        value_type item = m_data[--m_top]; // Move down the index and get the item.

        return item; // Return the item.
    }

    // Check if the stack is empty.
    bool empty() const noexcept
    {
        return m_top == 0;
    }

    // Return the size of the stack.
    size_type size() const noexcept
    {
        return m_size;
    }

    // Return the item at the top of the stack.
    reference top() const
    {
        if (empty()) // If the stack is empty.
        {
            throw std::out_of_range("Stack is empty!");
        }
        return m_data[m_top - 1];
    }
};
#endif // STACK_HPP