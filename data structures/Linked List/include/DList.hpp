// An implementation of double linked list.
#ifndef DLIST_HPP
#define DLIST_HPP

#include "DListIterator.hpp"
#include "Node.hpp"

#include <cstddef> // std::size_t
#include <initializer_list>
#include <iostream> // operator<<
#include <utility>  // std::exchange

template <typename T>
class DList
{
public:
    // Type aliases for STL compatibility.
    using value_type      = T;
    using size_type       = std::size_t;
    using reference       = value_type&;
    using const_reference = const value_type&;
    using pointer         = value_type*;
    using const_pointer   = const value_type*;
    using iterator        = DListIterator<value_type>;
    using const_iterator  = DListConstIterator<value_type>;

private:
    Node<value_type>* m_head{nullptr};
    Node<value_type>* m_tail{nullptr};

    size_type m_size{};

public:
    // Default ctor.
    DList() = default;

    // Initializer list ctor.
    DList(const std::initializer_list<value_type> i_list)
    {
        for (const auto& item : i_list)
        {
            push_back(item);
        }
    }

    // Copy ctor.
    DList(const DList<value_type>& other)
    {
        auto temp = other.m_head; // Start from the beginning.

        // Traverse the list while copying the elements.
        while (temp != nullptr)
        {
            // Constructing the list by appending the elements.
            push_back(temp->data);
            temp = temp->next; // Keep track of the other's pointer.
        }
    }

    // Move ctor.
    DList(DList<value_type>&& other) noexcept
        // Member-wise move.
        : m_head{std::exchange(other.m_head, nullptr)},
          m_tail{std::exchange(other.m_tail, nullptr)},
          m_size{std::exchange(other.m_size, 0ULL)}
    {
    }

    // Dtor.
    ~DList()
    {
        // Start from the beginning.
        Node<value_type>* temp = m_head;

        // Traverse the list while deleting previous elements.
        while (temp != nullptr)
        {
            temp = temp->next; // Move forward.
            delete m_head;     // Delete the previous element.
            m_head = temp;     // m_head moved one forward.
        }
    }

    // Assignment operator.
    DList& operator=(const DList<value_type>& other)
    {
        if (&other != this)
        {
            // Clear the current list.
            clear();

            // Copy the other list.
            auto other_head = other.m_head;
            while (other_head != nullptr)
            {
                push_back(other_head->data);
                other_head = other_head->next;
            }
        }

        return *this;
    }

    // Move assignment operator.
    DList& operator=(DList&& other) noexcept
    {
        if (&other != this)
        {
            clear();

            m_head = std::exchange(other.m_head, nullptr);
            m_tail = std::exchange(other.m_tail, nullptr);
            m_size = std::exchange(other.m_size, 0ULL);
        }

        return *this;
    }

    void clear()
    {
        // Start from the beginning
        Node<value_type>* current = m_head;

        // Traverse the list while deleting nodes
        while (current != nullptr)
        {
            Node<value_type>* next =
                current->next; // Save next pointer before deletion
            delete current;    // Delete current node
            current = next;    // Move to next node
        }

        // Reset member variables
        m_head = nullptr;
        m_tail = nullptr;
        m_size = 0ULL;
    }

    [[nodiscard]]
    iterator begin() const
    {
        return DListIterator{m_head};
    }

    [[nodiscard]]
    iterator rbegin() const
    {
        return DListIterator{m_tail};
    }

    [[nodiscard]]
    iterator end() const
    {
        // The end is nullptr.
        return DListIterator{m_tail ? m_tail->next : nullptr};
    }

    [[nodiscard]]
    iterator rend() const
    {
        // The rend is nullptr.
        return DListIterator{m_head ? m_head->prev : nullptr};
    }

    // Const iterators. Same as the regular iterators but starts with c.
    [[nodiscard]]
    const_iterator cbegin() const
    {
        return DListConstIterator<value_type>{m_head};
    }

    [[nodiscard]]
    const_iterator crbegin() const
    {
        return DListConstIterator<value_type>{m_tail};
    }

    [[nodiscard]]
    const_iterator cend() const
    {
        return DListConstIterator<value_type>{m_tail ? m_tail->next : nullptr};
    }

    [[nodiscard]]
    const_iterator crend() const
    {
        return DListConstIterator<value_type>{m_head ? m_head->prev : nullptr};
    }

    [[nodiscard]]
    reference front()
    {
        return *begin();
    }

    [[nodiscard]]
    reference back()
    {
        return *rbegin();
    }

    [[nodiscard]]
    const_reference front() const
    {
        return m_head->data;
    }

    [[nodiscard]]
    size_type size() const
    {
        return m_size;
    }

    [[nodiscard]]
    bool empty() const
    {
        return m_size == 0ULL;
    }

    void push_front(const_reference item)
    {
        // Create a node holding our item and its next pointer pointing to the
        // head.
        auto new_item = new Node<value_type>{item, nullptr, m_head};

        // If the head is the last element
        // (meaning it is the only element),
        // it'll be the tail.
        if (m_head == nullptr)
        {
            m_head = new_item;
            m_tail = new_item;
        }
        else
        {
            m_head->prev = new_item; // Update the head's previous pointer.
            m_head       = new_item; // Move the head.
        }
        m_size++;
    }

    void push_back(const_reference item)
    {
        // Create a node whose prev pointer pointing to the tail.
        auto new_item = new Node<value_type>{item, m_tail};

        if (m_tail == nullptr)
        {
            // If the list is empty, set the new item as the head as well.
            m_head = new_item;
            m_tail = new_item;
        }
        else
        {
            // Otherwise, update the current tail's next pointer to the new
            // item.
            m_tail->next = new_item;
            m_tail       = new_item; // Move the tail.
        }

        m_size++;
    }

    void insert(const size_type pos, const_reference item)
    {
        // If the position is the end of the list, append the new node.
        if (pos >= m_size)
        {
            push_back(item);
        }
        // If the position is the beginning of the list, prepend the new node.
        else if (pos == 0ULL)
        {
            push_front(item);
        }
        else
        {
            // Create a new node.
            auto new_item = new Node<value_type>{item};

            // Starting from the head, go to the position.
            auto temp = m_head;
            for (size_type i{}; i < pos; ++i)
            {
                temp = temp->next;
            }

            // Update pointers, connect new_item to the previous element two
            // ways. Update the previous element's next pointer.
            temp->prev->next = new_item;
            // Update the new item's previous pointer pointing to the previous
            // element.
            new_item->prev = temp->prev;
            // Connect new_item to the next element two ways.
            // Update the new item's next pointer pointing to the next element.
            new_item->next = temp;
            // Update the next element's previous pointer pointing to the new
            // item.
            temp->prev = new_item;

            m_size++;
        }
    }

    void pop_front()
    {
        // If there's no element, exit.
        if (m_head == nullptr)
        {
            return;
        }

        Node<value_type>* temp = m_head;
        m_head = m_head->next; // Move the head one forward. `temp` is still
                               // pointing to the previous head.

        // If the list has more than one element.
        if (m_head != nullptr)
        {
            m_head->prev = nullptr; // Cut the link to the previous element.
        }
        // The list has one element. m_head and m_tail are the same.
        else
        {
            // List is becoming empty.
            m_tail = nullptr;
        }

        delete temp;
        m_size--;
    }

    void pop_back()
    {
        Node<value_type>* temp = m_tail;

        // If the list is empty.
        if (temp == nullptr)
        {
            return;
        }

        // If the list's size is 1.
        if (temp == m_head)
        {
            delete temp;
            m_head = m_tail = nullptr;

            --m_size;

            return;
        }

        m_tail = m_tail->prev; // Move m_tail one back.
        delete temp;           // Get rid of the previous element.

        m_tail->next = nullptr; // Invalidate m_tail's next pointer.

        m_size--; // Don't forget to decrement the size.
    }

    void remove(const size_type pos)
    {
        if (pos >= m_size)
        {
            pop_back();
        }
        else
        {
            Node<value_type>* marked = m_head;
            // Go to the pos.
            for (size_type i{}; i < pos; ++i)
            {
                marked = marked->next;
            }

            // If the marked is the head.
            if (marked == m_head)
            {
                pop_front();
                return;
            }
            else
            {
                // Update pointers.
                // Connect the previous element's next pointer to the next
                // element.
                marked->prev->next = marked->next;
                // Connect the next element's previous pointer to the previous
                // element.
                marked->next->prev = marked->prev;

                delete marked;
                --m_size;

                // If the list is empty, reset m_head and m_tail.
                if (m_size == 0)
                {
                    m_head = nullptr;
                    m_tail = nullptr;
                }
            }
        }
    }

    reference operator[](const size_type pos)
    {
        if (pos >= m_size)
        {
            throw std::out_of_range("Index out of bounds");
        }

        Node<value_type>* temp = m_head;
        for (size_type i{}; i != pos; ++i)
        {
            temp = temp->next;
        }
        return temp->data;
    }

    const_reference operator[](const size_type pos) const
    {
        if (pos >= m_size)
        {
            throw std::out_of_range("Index out of bounds");
        }

        Node<value_type>* temp = m_head;
        for (size_type i{}; i != pos; ++i)
        {
            temp = temp->next;
        }
        return temp->data;
    }

    // Reverse the pointers.
    void reverse()
    {
        // Start from the head.
        Node<value_type>* temp = m_head;
        Node<value_type>* prev = nullptr;
        Node<value_type>* next = nullptr;

        // Traverse the list.
        while (temp != nullptr)
        {
            // Store the next element.
            next = temp->next;
            // Reverse the pointers.
            temp->next = prev;
            temp->prev = next;
            // Move forward.
            prev = temp;
            temp = next;
        }

        // Swap the head and the tail.
        std::swap(m_head, m_tail);
    }

    // Check if a value exists in the list
    [[nodiscard]]
    bool contains(const_reference value) const
    {
        for (const auto& item : *this)
        {
            if (item == value)
            {
                return true;
            }
        }
        return false;
    }

    // Swap two lists
    void swap(DList& other) noexcept
    {
        // Just swap the pointers and the size.
        std::swap(m_head, other.m_head);
        std::swap(m_tail, other.m_tail);
        std::swap(m_size, other.m_size);
    }

    // Check if a value exists in the list
    [[nodiscard]]
    bool contains(const_reference value) const
    {
        for (const auto& item : *this)
        {
            if (item == value)
            {
                return true;
            }
        }
        return false;
    }

    // Construct element directly in the new node at the front
    template <typename... Args>
    void emplace_front(Args&&... args)
    {
        // Create a new node and construct the element in-place using perfect
        // forwarding
        auto new_item =
            new Node<value_type>{value_type(std::forward<Args>(args)...),
                                 nullptr,
                                 m_head};

        if (m_head == nullptr)
        {
            m_head = new_item;
            m_tail = new_item;
        }
        else
        {
            m_head->prev = new_item;
            m_head       = new_item;
        }
        m_size++;
    }

    // Construct element directly in the new node at the back
    template <typename... Args>
    void emplace_back(Args&&... args)
    {
        // Create a new node and construct the element in-place using perfect
        // forwarding
        auto new_item =
            new Node<value_type>{value_type(std::forward<Args>(args)...),
                                 m_tail};

        if (m_tail == nullptr)
        {
            m_head = new_item;
            m_tail = new_item;
        }
        else
        {
            m_tail->next = new_item;
            m_tail       = new_item;
        }
        m_size++;
    }
};

template <typename T>
std::ostream& operator<<(std::ostream& out, const DList<T>& dlist)
{
    // Format: [item1, item2, item3, ...]
    out << '[';
    for (auto it = dlist.begin(); it != dlist.end(); ++it)
    {
        out << *it;
        if (it != dlist.rbegin())
        {
            out << ", ";
        }
    }
    out << ']';
    return out;
}
#endif // DLIST_HPP
