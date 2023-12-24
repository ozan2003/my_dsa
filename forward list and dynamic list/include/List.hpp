// This is a blueprint for all list-like data structures.
// It won't specify how the operations are carried out.
#ifndef LIST_HPP
#define LIST_HPP

#include <initializer_list>

template <typename T>
class List
{
public:
	List()
	{}

	virtual ~List()
	{}

	List(const List&)
	{}

	virtual void insert(const unsigned pos, const T& item) = 0;
	virtual void append(const T& item) = 0;

	virtual void remove(const unsigned pos) = 0;

	virtual int size() const = 0;

	virtual bool empty() const = 0;

	// Because the result of operator[] can be used on the left hand side of an assignment
	// (e.g. list[2] = 3), the return value of operator[] must be an l-value. 
	// As it turns out, references are always l-values.
	virtual T& operator[](const int pos) = 0;
	// Subscript operators often come in pairs.
	// The const overload is called only when used on const object.
	virtual const T& operator[](const int pos) const = 0;

};
#endif // LIST_HPP
