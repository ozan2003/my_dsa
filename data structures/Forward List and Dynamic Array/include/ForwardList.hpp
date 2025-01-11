#ifndef FORWARDLIST_HPP
#define FORWARDLIST_HPP

#include "ForwardListIterator.hpp"
#include "List.hpp"
#include "Node.hpp"

#include <cstddef>  // std::size_t
#include <iostream> // operator<<
#include <utility>  // std::move, std::exchange

template <typename T>
class ForwardList : public List<T>
{
private:
    Node<T>* m_head{nullptr};
    Node<T>* m_tail{nullptr};

    std::size_t m_size{};

public:
    ForwardList() = default;

    ForwardList(const std::initializer_list<T> i_list)
    {
        for (const auto& item : i_list)
        {
            append(item);
        }
    }

    // Copy constructor.
    ForwardList(const ForwardList<T>& other)
        : List<T>{}
    {
        auto temp = other.m_head;

        while (temp != nullptr)
        {
            // Append to our list and update the other's pointer position.
            append(temp->data);
            temp = temp->next;
        }
    }

    ForwardList(ForwardList<T>&& other) noexcept
        // Member-wise move.
        : m_head{std::exchange(other.m_head, nullptr)},
          m_tail{std::exchange(other.m_tail, nullptr)},
          m_size{std::exchange(other.m_size, 0ull)}
    {
        other.m_head = nullptr;
        other.m_tail = nullptr;
        other.m_size = 0ull;
    }

    ~ForwardList()
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

    ForwardList& operator=(const ForwardList<T>& other)
    {
        if (&other != this)
        {
            // Delete the current list one by one.
            while (m_size > 0ull)
            {
                remove_back();
            }

            auto other_head = other.m_head; // Start from the beginning of the other list.

            // Traverse the other list while appending the elements to this list.
            while (other_head != nullptr)
            {
                append(other_head->data);
                other_head = other_head->next;
            }
        }

        return *this;
    }

    ForwardList& operator=(ForwardList<T>&& other) noexcept
    {
        if (&other != this)
        {
            // Delete the current list one by one.
            while (m_size > 0ull)
            {
                remove_back();
            }

            m_head = std::exchange(other.m_head, nullptr);
            m_tail = std::exchange(other.m_tail, nullptr);
            m_size = std::exchange(other.m_size, 0ull);
        }

        return *this;
    }

    // Iterator pointing at beginning.
    ForwardListIterator<T> begin() const
    {
        return ForwardListIterator{m_head};
    }

    // Iterator pointing one past the end.
    ForwardListIterator<T> end() const
    {
        return ForwardListIterator{m_tail->next};
    }

    std::size_t size() const override
    {
        return m_size;
    }

    bool empty() const override
    {
        return size() == 0ull;
    }

    void prepend(const T& item)
    {
        // Create a node holding our item and pointing to the head.
        auto new_item = new Node<T>{item, m_head};

        // If the head is the last element
        // (meaning it is the only element),
        // it'll be the tail.
        if (m_head == nullptr)
        {
            m_tail = m_head;
        }

        m_head = new_item; // Update the head.
        m_size++;          // Don't forget to increment the size.
    }

    void append(const T& item) override
    {
        // Create a node with no pointer.
        auto new_item = new Node<T>{item};

        if (m_tail == nullptr)
        {
            // If the list is empty, set the new item as the head as well.
            m_head = new_item;
            m_tail = new_item;
        }
        else
        {
            // Otherwise, update the current tail's ahead pointer to the new item and move the tail.
            m_tail->next = new_item;
            m_tail       = new_item;
        }

        m_size++;
    }

    // Avoid illegal indexes by making pos unsigned.
    void insert(const std::size_t pos, const T& item) override
    {
        // If the position is the beginning of the list, prepend the new node.
        if (pos == 0ull)
        {
            prepend(item);
        }
        // If the position is beyond the end of the list, append the new node.
        else if (pos >= m_size)
        {
            append(item);
        }
        else
        {
            // Create a new node.
            auto new_item = new Node<T>{item};

            // Starting from the head, go to the one past the position.
            auto temp = m_head;
            for (std::size_t i{}; i < pos - 1ull; ++i)
            {
                temp = temp->next;
            }

            new_item->next = temp->next; // Link the new_item to the one ahead the temp.
            temp->next     = new_item;   // Link temp to the new_item.

            m_size++;
        }
    }

    void remove_front()
    {
        Node<T>* temp = m_head;

        // If there's no element, exit.
        if (m_head == nullptr)
        {
            return;
        }

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
        Node<T>* temp = m_head;

        if (temp == nullptr)
        {
            return;
        }

        // If the list's size is 1.
        if (temp == m_tail)
        {
            delete temp;
            m_head = m_tail = nullptr;

            --m_size;

            return;
        }

        // Traverse to one before the end.
        while (temp->next != m_tail)
        {
            temp = temp->next;
        }

        m_tail = temp;
        // temp = temp->ahead;
        delete temp->next;

        m_tail->next = nullptr;

        --m_size;
    }

    // Avoid illegal indexes by making pos unsigned.
    void remove(const std::size_t pos) override
    {
        if (pos == 0)
        {
            remove_front();
        }
        else if (pos >= m_size)
        {
            remove_back();
        }
        else
        {
            Node<T>* temp = m_head;

            // Go to the one past the pos.
            for (std::size_t i{}; i < pos - 1ull; ++i)
            {
                temp = temp->next;
            }

            // The element to be removed.
            auto to_removed = temp->next;
            // Link the current node one ahead the to_removed.
            temp->next = to_removed->next;

            // T removed_data = to_removed->data; // Retrieve the data before deleting the node.

            delete to_removed; // Delete the to_removed.
            m_size--;          // Don't forget to decrement the size.

            if (m_size == 0)
            {
                m_head = nullptr;
                m_tail = nullptr;
            }
        }

        // return removed_data;
    }

    T& operator[](const std::size_t pos) override
    {
        Node<T>* temp = m_head;

        for (std::size_t i{}; i != pos; ++i)
        {
            temp = temp->next;
        }

        return temp->data;
    }

    const T& operator[](const std::size_t pos) const override
    {
        Node<T>* temp = m_head;

        for (std::size_t i{}; i != pos; ++i)
        {
            temp = temp->next;
        }

        return temp->data;
    }

    // Reverse the list.
    void reverse()
    {
        Node<T>* behind  = nullptr;
        Node<T>* current = m_head;
        Node<T>* ahead   = nullptr;

        while (current != nullptr)
        {
            ahead         = current->next; // Store the ahead node.
            current->next = behind;        // Reverse the current node's pointer.
            behind        = current;       // Move behind one forward.
            current       = ahead;         // Move current one forward.
        }

        m_head = behind; // Update the head.
    }
};

// Print the list.
template <typename T>
std::ostream& operator<<(std::ostream& os, const ForwardList<T>& list)
{
    for (const auto& item : list)
    {
        os << item << ' ';
    }

    return os;
}
#endif // FORWARDLIST_HPP
