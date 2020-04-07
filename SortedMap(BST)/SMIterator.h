#pragma once
#include "SortedMap.h"

class SortedMap;
typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue> TElem;
#define NULL_TVALUE -1
typedef bool(*Relation)(TKey, TKey);

struct Node;

class SMIterator {
private:
	friend class SortedMap;

	//Constructor receives a reference of the container.
	//after creation the iterator will refer to the first element of the container, or it will be invalid if the container is empty
	SMIterator(const SortedMap& c);

	//contains a reference of the container it iterates over
	const SortedMap& c;

	/* representation specific for the iterator*/

	Node* cur;

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


