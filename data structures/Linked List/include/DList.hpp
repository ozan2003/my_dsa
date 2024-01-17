// An implementation of double linked list.
#ifndef DLIST_HPP
#define DLIST_HPP

#include "Node.hpp"

#include <initializer_list>
#include <iostream> // operator<<

template <typename T>
class DList
{
private:
    Node<T>* m_head{nullptr};
    Node<T>* m_tail{nullptr};

    int m_size{};

public:
    // Default ctor.
    DList() = default;

    // Initializer list ctor.
    DList(std::initializer_list<T> i_list)
    {
        for (const auto& item : i_list)
        {
            append(item);
        }
    }

    // Copy ctor.
    DList(const DList<T>& other)
    {
        auto temp = other.m_head;

        while (temp != nullptr)
        {
            append(temp->data);
            temp = temp->next;
        }
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
            while (m_size > 0)
            {
                remove_back();
            }

            auto other_head = other.m_head; // Start from the beginning.

            // Copy the other list.
            while (other_head != nullptr)
            {
                append(other_head->data); // Append other's data to out list.
                other_head = other_head->next; // Move forward.
            }
        }

        return *this;
    }

    Node<T>* head() const
    {
        return m_head;
    }

    Node<T>* tail() const
    {
        return m_tail;
    }

    int size() const
    {
        return m_size;
    }

    void prepend(const T& item)
    {
        // Create a node holding our item and pointing to the head.
        auto new_item = new Node<T>{item, nullptr, m_head};

        // If the head is the last element
        // (meaning it is the only element),
        // it'll be the tail.
        if (m_head == nullptr)
        {
            m_tail = m_head;
        }

        m_head = new_item;
        m_size++;
    }

    void append(const T& item)
    {
        // Create a node pointing to the tail.
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
            //new_item->prev = m_tail; // Connect new_item's previous pointer to tail.
            m_tail = new_item; // Move the tail.
        }

        m_size++;
    }

    void insert(const int pos, const T& item)
    {
        // If the position is the beginning of the list, prepend the new node.
        if (pos <= 0)
        {
            prepend(item);
        }
        else if (pos >= m_size)
        {
            append(item);
        }
        else
        {
            // Create a new node.
            auto new_item = new Node<T>{item};

            // Starting from the head, go to the position.
            auto temp = m_head;
            for (int i{}; i < pos; ++i)
            {
                temp = temp->next;
            }

            // Update pointers.
            new_item->next = temp->prev->next;
            temp->prev->next = new_item;
            new_item->prev = temp->prev;

            if (new_item->next)
            {
                new_item->next->prev = new_item;
            }

            m_size++;

            /*
             Node *prev = get_node(index - 1);
             Node *next = prev->next;
             prev->next = node;
             node->prev = prev;
             node->next = next;
             if (next)
                 next->prev = node;
             if (prev == tail)
                 tail = node;
            */
        }
    }

    void remove_front()
    {
        // If there's no element, exit.
        if (m_head == nullptr)
        {
            return;
        }

        Node<T>* temp = m_head;

        m_head = m_head->next; // Move m_head one element forward.
        delete temp;           // Get rid of the previous element.

        m_size--;

        if (m_size == 0)
        {
            m_head = nullptr;
            m_tail = nullptr;
        }
    }

    void remove_back()
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

        m_tail = m_tail->prev;  // Move m_tail one back.
        delete m_tail->next;    // Remove the m_tail's next.

        m_tail->next = nullptr; // Invalidate m_tail's next pointer.

        m_size--;
    }

    void remove(const int pos)
    {
        if (pos <= 0)
        {
            remove_front();
        }
        else if (pos >= m_size - 1)
        {
            remove_back();
        }
        else
        {
            Node<T>* temp = m_head;

            // Go to the one past the pos.
            for (int i{}; i < pos - 1; ++i)
            {
                temp = temp->next;
            }

            // The element to be removed.
            auto marked = temp->next;

            temp->next = temp->next->next;
            temp->next->next->prev = temp;

            delete marked;
            m_size--;

            if (m_size == 0)
            {
                m_head = nullptr;
                m_tail = nullptr;
            }
        }
    }

    T& operator[](const int pos)
    {
        Node<T>* temp = m_head;

        for (int i{}; i != pos; ++i)
        {
            temp = temp->next;
        }

        return temp->data;
    }

    const T& operator[](const int pos) const
    {
        Node<T>* temp = m_head;

        for (int i{}; i != pos; ++i)
        {
            temp = temp->next;
        }

        return temp->data;
    }
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const DList<T>& dlist)
{
    for (auto i = dlist.head(); i != nullptr; i = i->next)
    {
        os << i->data << ' ';
    }
    return os;
}
#endif // DLIST_HPP
