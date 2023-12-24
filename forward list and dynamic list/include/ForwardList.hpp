#ifndef FORWARDLIST_HPP
#define FORWARDLIST_HPP

#include "List.hpp"
#include "Node.hpp"

#include <iostream> // operator<<

template <typename T>
class ForwardList: public List<T>
{
private:
	Node<T>* m_head{nullptr};
	Node<T>* m_tail{nullptr};

	int m_size{};


public:
	ForwardList() = default;

	ForwardList(std::initializer_list<T> i_list)
	{
		for (const auto& item : i_list)
		{
			append(item);
		}
	}

	// Copy constructor.
	ForwardList(const ForwardList<T>& other): List<T>{}
	{
		auto temp = other.m_head;

		while (temp != nullptr)
		{
			append(temp->data);
			temp = temp->next;
		}
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
			while (m_size > 0)
			{
				remove_back();
			}

			auto other_head = other.m_head;
			while (other_head != nullptr)
			{
				append(other_head->data);
				other_head = other_head->next;
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

	bool empty() const override
	{
		return m_size == 0;
	}

	int size() const override
	{
		return m_size;
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

		m_head = new_item;
		m_size++;
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
			// Otherwise, update the current tail's next pointer to the new item and move the tail.
			m_tail->next = new_item;
			m_tail = new_item;
		}

		m_size++;
	}

	// Avoid illegal indexes by making pos unsigned.
	void insert(const unsigned pos, const T& item) override
	{
		// If the position is the beginning of the list, prepend the new node.
		if (pos == 0)
		{
			prepend(item);
		}
		// If the position is beyond the end of the list, append the new node.
		else if (static_cast<int>(pos) >= m_size)
		{
			append(item);
		}
		else
		{
			// Create a new node.
			auto new_item = new Node<T>{item};

			// Starting from the head, go to the one past the position.
			auto temp = m_head;
			for (int i{}; i < static_cast<int>(pos) - 1; ++i)
			{
				temp = temp->next;
			}

			new_item->next = temp->next; // Link the new_item to the one after the temp.
			temp->next = new_item;       // Link temp to the new_item.

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
		//temp = temp->next;
		delete temp->next;

		m_tail->next = nullptr;

		--m_size;
	}

	// Avoid illegal indexes by making pos unsigned.
	void remove(const unsigned pos) override
	{
		if (pos == 0)
		{
			remove_front();
		}
		else if (pos == m_size - 1)
		{
			remove_back();
		}
		else
		{
			Node<T>* temp = m_head;

			// Go to the one past the pos.
			for (int i{}; i < static_cast<int>(pos) - 1; ++i)
			{
				temp = temp->next;
			}

			// The element to be removed.
			auto to_removed = temp->next;
			// Link the current node one after the to_removed.
			temp->next = temp->next->next;

			//T removed_data = to_removed->data; // Retrieve the data before deleting the node.

			delete to_removed; // Delete the to_removed.
			m_size--;          // Don't forget to decrement the size.

			if (m_size == 0)
			{
				m_head = nullptr;
				m_tail = nullptr;
			}
		}

		//return removed_data;
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

	void reverse()
	{
		Node<T>* prev = nullptr;
		Node<T>* curr = m_head;

		// Iterate through the forward list while the current node is not null.
		while (curr != nullptr)
		{
			// Store the next node in the next variable.
			Node<T>* next = curr->next;

			// Set the current node's next pointer to the previous node.
			curr->next = prev;

			// Update the previous and current node pointers.
			prev = curr;
			curr = next;
		}

		// Set the head of the forward list to the previous node.
		m_head = prev;
	}

};

template <typename T>
std::ostream& operator<<(std::ostream& os, const ForwardList<T>& llist)
{
	for (auto i = llist.head(); i != nullptr; i = i->next)
	{
		os << i->data << ' ';
	}
	return os;
}
#endif // FORWARDLIST_HPP
