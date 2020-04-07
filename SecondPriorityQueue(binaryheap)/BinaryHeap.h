#pragma once
#pragma warning (disable : 6386)

#include <assert.h>
#include <iostream>

typedef int TElem;
typedef int TPriority;
typedef std::pair<TElem, TPriority> Element;
typedef bool(*Relation)(TPriority p1, TPriority p2);

class BinaryHeap
{
	Element* elems;
	size_t capacity, size;
public:

	// Default Constructor
	BinaryHeap(size_t size = 64);

	// Copy Constructor
	BinaryHeap(const BinaryHeap& heap);

	// Assignment Operator Overload
	BinaryHeap& operator=(const BinaryHeap& heap);

	// Subscript Operator Overload
	Element& operator[](size_t pos);

	// Default Destructor
	~BinaryHeap();

	// Resize function for elems array
	void resize(size_t factor = 2);

	// Size getter
	size_t getSize() const;

	// Add to heap function
	void add(Element e, Relation r);

	// Bubble Up from pos to preserve the heap property
	void bubbleUp(size_t pos, Relation r);

	Element top(Relation r) const;

	// Remove the root, first in priority
	Element remove(Relation r);

	// Remove the element with the second priority
	Element remove_second(Relation r);

	// Bubble Down from pos
	void bubbleDown(size_t pos, Relation r);
};
