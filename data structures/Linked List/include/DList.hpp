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
private:
    Node<T>* m_head{nullptr};
    Node<T>* m_tail{nullptr};

    std::size_t m_size{};

public:
    // Default ctor.
    DList() = default;

    // Initializer list ctor.
    DList(const std::initializer_list<T> i_list)
    {
        for (const auto& item : i_list)
        {
            push_back(item);
        }
    }

    // Copy ctor.
    DList(const DList<T>& other)
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
    DList(DList<T>&& other) noexcept
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
        Node<T>* temp = m_head;

        // Traverse the list while deleting previous elements.
        while (temp != nullptr)
        {
            temp = temp->next; // Move forward.
            delete m_head;     // Delete the previous element.
            m_head = temp;     // m_head moved one forward.
        }
    }

    // Assignment operator.
    DList& operator=(const DList<T>& other)
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
        while (m_size > 0ULL)
        {
            pop_back();
        }
    }

    DListIterator<T> begin() const
    {
        return DListIterator{m_head};
    }

    DListIterator<T> rbegin() const
    {
        return DListIterator{m_tail};
    }

    DListIterator<T> end() const
    {
        // The end is nullptr.
        return DListIterator{m_tail->next};
    }

    DListIterator<T> rend() const
    {
        // The rend is nullptr.
        return DListIterator{m_head->prev};
    }

    T& front()
    {
        return *begin();
    }

    T& back()
    {
        return *rbegin();
    }

    const T& front() const
    {
        return m_head->data;
    }

    std::size_t size() const
    {
        return m_size;
    }

    bool empty() const
    {
        return m_size == 0ULL;
    }

    void push_front(const T& item)
    {
        // Create a node holding our item and its next pointer pointing to the head.
        auto new_item = new Node<T>{item, nullptr, m_head};

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

    void push_back(const T& item)
    {
        // Create a node whose prev pointer pointing to the tail.
        auto new_item = new Node<T>{item, m_tail};

        if (m_tail == nullptr)
        {
            // If the list is empty, set the new item as the head as well.
            m_head = new_item;
            m_tail = new_item;
        }
        else
        {
            // Otherwise, update the current tail's next pointer to the new item.
            m_tail->next = new_item;
            m_tail       = new_item; // Move the tail.
        }

        m_size++;
    }

    void insert(const std::size_t pos, const T& item)
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
            auto new_item = new Node<T>{item};

            // Starting from the head, go to the position.
            auto temp = m_head;
            for (std::size_t i{}; i < pos; ++i)
            {
                temp = temp->next;
            }

            // Update pointers, connect new_item to the previous element two ways.
            // Update the previous element's next pointer.
            temp->prev->next = new_item;
            // Update the new item's previous pointer pointing to the previous element.
            new_item->prev = temp->prev;
            // Connect new_item to the next element two ways.
            // Update the new item's next pointer pointing to the next element.
            new_item->next = temp;
            // Update the next element's previous pointer pointing to the new item.
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

        Node<T>* temp = m_head;
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
        Node<T>* temp = m_tail;

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

    void remove(const std::size_t pos)
    {
        if (pos >= m_size)
        {
            pop_back();
        }
        else
        {
            Node<T>* marked = m_head;
            // Go to the pos.
            for (std::size_t i{}; i < pos; ++i)
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
                // Connect the previous element's next pointer to the next element.
                marked->prev->next = marked->next;
                // Connect the next element's previous pointer to the previous element.
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

    T& operator[](const std::size_t pos)
    {
        if (pos >= m_size)
        {
            throw std::out_of_range("Index out of bounds");
        }

        Node<T>* temp = m_head;
        for (std::size_t i{}; i != pos; ++i)
        {
            temp = temp->next;
        }
        return temp->data;
    }

    const T& operator[](const std::size_t pos) const
    {
        if (pos >= m_size)
        {
            throw std::out_of_range("Index out of bounds");
        }

        Node<T>* temp = m_head;
        for (std::size_t i{}; i != pos; ++i)
        {
            temp = temp->next;
        }
        return temp->data;
    }

    // Reverse the pointers.
    void reverse()
    {
        // Start from the head.
        Node<T>* temp = m_head;
        Node<T>* prev = nullptr;
        Node<T>* next = nullptr;

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
