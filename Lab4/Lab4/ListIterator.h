#pragma once
#include "IndexedList.h"
#include <exception>

class IndexedList;

typedef int TElem;

class ListIterator
{
private:

	//contains a reference of the container it iterates over
	const IndexedList &c;
	int curr;
	friend class IndexedList;

	//Constructor receives a reference of the container.
	//after creation the iterator will refer to the first element of the container, or it will be invalid if the container is empty
	ListIterator(const IndexedList& c);

	/* representation specific for the iterator*/
public:
	//sets the iterator to the first element of the container
	void first();

	//moves the iterator to the next element
	//throws exception if the iterator is not valid
	void next();

	//checks if the iterator is valid
	bool valid() const;

	//returns the value of the current element from the iterator
	// throws exception if the iterator is not valid
	TElem getCurrent() const;

};

