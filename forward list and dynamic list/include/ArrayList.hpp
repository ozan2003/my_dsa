// An array-based approach of list.
#ifndef ARRAYLIST_HPP
#define ARRAYLIST_HPP

#include "List.hpp"
#include <cassert>
#include <iostream> // operator<<

const int INITIAL_SIZE  = 2;
const int GROWTH_FACTOR = 2;

template <typename T>
class ArrayList: public List<T>
{
private:
	int m_capacity{};     // Maximum size of list.
	int m_size{};         // Current number of list elements.
	T*  m_list_array{};   // Array holding list of elements.

	void reserve()
	{
		m_capacity *= GROWTH_FACTOR;

		if (m_capacity == 0)
		{
			m_capacity = INITIAL_SIZE;
		}

		T* temp = new T[m_capacity];   // Allocate new array in the heap.

		for (int i{}; i < m_size; ++i)
		{
			temp[i] = m_list_array[i]; // Copy all items of original array.
		}

		delete[] m_list_array;         // Get rid of the original array.
		m_list_array = temp;           // "temp" is our new array now.
	}

public:
	ArrayList() = default;

	ArrayList(int size)
		: m_capacity{size * GROWTH_FACTOR},
		m_size{size},
		m_list_array{new T[m_capacity]{}} // ArrayList elements are zero initialized by default.
	{}

	ArrayList(std::initializer_list<T> i_list)
		: ArrayList(static_cast<int>(i_list.size()))
	// Don't use braces as initializer_list constructor uses it.
	// Otherwise this constructor would call itself.
	{
		int count{};
		for (const auto& item : i_list)
		{
			m_list_array[count] = item;
			count++;
		}
	}

	// Copy constructor.
	/*
	 * Rule of Three:
	 * If a class requires a user-defined destructor,
	 * a user-defined copy constructor,
	 * or a user-defined copy assignment operator,
	 * it almost certainly requires all three.
	 */
	ArrayList(const ArrayList& other)
		: List<T>{},
		m_capacity{other.m_capacity},
		m_size{other.m_size},
		m_list_array{new T[other.m_capacity]{}}
	{
		for (int i{}; i < m_size; ++i)
		{
			m_list_array[i] = other.m_list_array[i];
		}
	}


	~ArrayList()
	{
		delete[] m_list_array;
	}

	void clear()
	{
		delete[] m_list_array;
		m_list_array = nullptr;
		m_capacity = 0;
		m_size = 0;
	}

	// Insert "item" at given position.
	void insert(const unsigned pos, const T& item) override
	{
		if (m_size == m_capacity)
		{
			reserve();
		}
		assert(static_cast<int>(pos) < m_size && "Out of range.\n");

		for (int s{m_size}; static_cast<int>(pos) < s; --s)        // Shift elements up...
		{
			m_list_array[s] = m_list_array[s - 1]; // ...to make room.
		}
		///DEMONSTRATION
		//┌────┬────┬────┬────┬────┬────┬────┐
		//│i[0]│i[1]│i[2]│i[3]│i[4]│i[5]│i[6]│     // INDEXES
		//├────┼────┼────┼────┼────┼────┼────┤
		//│10  │20  │30  │40  │50  │60  │    │     // ITEMS
		//├────┼────┼────┼────┼────┼────┼────┤
		//│    │10  │20  │30  │40  │50  │60  │     // SHIFT ELEMENTS UP
		//├────┼────┼────┼────┼────┼────┼────┤
		//│item│10  │20  │30  │40  │50  │60  │     // INSERT "item"
		//└────┴────┴────┴────┴────┴────┴────┘
		//
		m_list_array[pos] = item;

		m_size++;                                  // Increment list size.
	}

	// Append "item".
	void append(const T& item) override
	{
		if (m_size == m_capacity)
		{
			reserve();
		}
		//assert(m_size < m_capacity && "List capacity exceeded.\n");

		m_list_array[m_size] = item;
		m_size++;
	}

	// Remove and return the current element.
	T remove(const unsigned pos) override
	{
		assert(static_cast<int>(pos) < m_size && "No element.\n");

		T item = m_list_array[pos];                // Copy the item.

		// m_size - 1, because we're dealing with array indexes (array[size] is out of bounds).
		for (int i{static_cast<int>(pos)}; i < m_size - 1; ++i)
		{
			m_list_array[i] = m_list_array[i + 1]; // Shift elements down.
		}
		///DEMONSTRATION
		//┌────┬────┬────┬────┬────┬────┬────┐
		//│i[0]│i[1]│i[2]│i[3]│i[4]│i[5]│i[6]│     // INDEXES
		//├────┼────┼────┼────┼────┼────┼────┤
		//│10  │item│20  │30  │40  │50  │60  │     // ITEMS
		//├────┼────┼────┼────┼────┼────┼────┤
		//│10  │20  │30  │40  │50  │60  │... │     // SHIFT ELEMENTS DOWN
		//└────┴────┴────┴────┴────┴────┴────┘
		//
		m_size--;                                  // Decrement size.

		return item;
	}

	// Return list size.
	int size() const override
	{
		return m_size;
	}

	bool empty() const override
	{
		return size() == 0;
	}

	T& operator[](const int pos) override
	{
		assert(!empty() && "No current element.\n");
		return m_list_array[pos];
	}

	const T& operator[](const int pos) const override
	{
		assert(!empty() && "No current element.\n");
		return m_list_array[pos];
	}
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const ArrayList<T>& list)
{
	for (int i{}, s{list.size()}; i < s; ++i)
	{
		os << list[i] << '\n';
	}
	return os;
}


#endif // ARRAYLIST_HPP
