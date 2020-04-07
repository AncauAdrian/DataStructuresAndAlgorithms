#pragma once
#define INIT_CAPACITY 256

#include "DynamicVector.h"
#include "ListIterator.h"

typedef int TElem;

class IndexedList {

private:

	//representation of the IndexedList

	int cap = INIT_CAPACITY;
	DynamicVector<TElem> elems = DynamicVector<TElem>(INIT_CAPACITY);
	DynamicVector<int> next = DynamicVector<int>(INIT_CAPACITY);
	int head, firstEmpty, truesize;

	friend class ListIterator;

public:

	// constructor
	IndexedList();

	// returns the number of elements from the list
	int size() const;

	// checks if the list is empty
	bool isEmpty() const;

	// returns an element from a position
	//throws exception if the position is not valid
	TElem getElement(int pos) const;

	// modiifes an element from agiven position
	//returns the old value from the position
	//throws an exception if the position is not valid
	TElem setElement(int pos, TElem e);

	// adds an element to the end of the list
	void addToEnd(TElem e);

	// adds an element to a given position
	//throws an exception if the position is not valid
	void addToPosition(int pos, TElem e);

	// removes an element from a given position
	//returns the removed element
	//throws an exception if the position is not valid
	TElem remove(int pos);

	// searches for an element and returns the first position where the element appears or -1 if the element is not in the list
	int search(TElem e)  const;

	// returns an iterator set to the first element of the list or invalid if the list is empty
	ListIterator iterator() const;

	// returns the last index of a given element
	// if the element is not in the list it returns -1
	int lastIndexOf(TElem e);

};