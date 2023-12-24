#ifndef STACK_HPP
#define STACK_HPP

constexpr int DEFAULT_SIZE{1};  // Default size of the stack.
constexpr int RESIZE_FACTOR{2}; // Resize factor of the stack.

template <typename T>
class Stack
{
    int  m_size{DEFAULT_SIZE};       // Size of the stack.
    T*   m_storage{new T[m_size]};   // Pointer to the stack.
    int  m_top{};                    // Index of the top of the stack.

    void resize()
    {
        m_size *= RESIZE_FACTOR; // Increase the size.

        if (m_size == 0) // If the size is zero.
        {
            m_size = DEFAULT_SIZE; // Give it an initial size.
        }

        T* temp = new T[m_size]; // Create a new stack with the given size.

        // Copy the items from the old stack to the new stack.
        for (int i{}; i < m_size; ++i)
        {
            temp[i] = m_storage[i];
        }

        delete[] m_storage; // Delete the old stack.
        m_storage = temp;   // Point to the new stack.
    }

public:
    // Default constructor.
    Stack() = default;

    // Constructor with given size.
    Stack(const int size)
        : m_size{size}, m_storage{new T[m_size]}
    {
    }

    // Destructor.
    ~Stack()
    {
        delete[] m_storage; // Delete the array holding the stack.
    }

    // Copy constructor.
    Stack(const Stack<T>& other)
        : m_size{other.m_size}, m_storage{new T[m_size]}
    {
        // Copy the items from the other stack to this stack.
        for (int i{}; i < m_size; ++i)
        {
            m_storage[i] = other.m_storage[i];
        }
    }

    // Copy assignment operator.
    Stack& operator=(const Stack<T>& other)
    {
        if (this != &other) // Check for self-assignment.
        {
            delete[] m_storage; // Delete the old stack.

            m_size = other.m_size;        // Copy the size.
            m_storage = new T[m_size]; // Create a new stack with the given size.

            // Copy the items from the other stack to this stack.
            for (int i{}; i < m_size; ++i)
            {
                m_storage[i] = other.m_storage[i];
            }
        }
        return *this; // Return this stack.
    }

    // Add item to the top of the stack.
    void push(const int item)
    {
        // If the stack is full, resize it.
        if (m_top >= m_size)
        {
            resize();
        }
        m_storage[m_top++] = item; // Add item to the top of the stack.
    }

    // Remove item from the top of the stack.
    T pop()
    {
        T item = m_storage[--m_top]; // Remove item from the top of the stack.

        return item; // Return the item.
    }

    // Check if the stack is empty.
    bool empty() const
    {
        return m_top == 0;
    }

    // Return the size of the stack.
    int size() const
    {
        return m_size;
    }

    T& top() const
    {
        return m_storage[m_top - 1];
    }
};

#endif // STACK_HPP