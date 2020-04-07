#pragma once
#include "Iterator.h"
#include "DynamicVector.h"

typedef int TElem;


class Bag {
private:

	DynamicVector<TElem> list;
	TElem max, min, realsize;

	friend class BagIterator;

public:

	//constructor

	Bag();

	//adds an element to the bag

	void add(TElem e);

	//removes one occurrence of an element from a bag

	//returns true if an element was removed, false otherwise (if e was not part of the bag)

	bool remove(TElem e);

	//checks if an element appearch is the bag

	bool search(TElem e) const;


	//returns the number of occurrences for an element in the bag

	int nrOccurrences(TElem e) const;


	//returns the number of elements from the bag

	int size() const;


	//returns an iterator for this bag

	BagIterator iterator() const;


	//checks if the bag is empty

	bool isEmpty() const;

	//returns the number of unique elements with the minimum frequency
	//if the bag is empty, it return 0
	int elementsWithMinimumFrequency() const;

};