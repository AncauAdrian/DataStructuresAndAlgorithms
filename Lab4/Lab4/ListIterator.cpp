#include "ListIterator.h"

ListIterator::ListIterator(const IndexedList & c) : c(c) // Complexity Theta(1)
{
	this->curr = c.head;
}

void ListIterator::first() // Complexity Theta(1)
{
	this->curr = c.head;
}

void ListIterator::next() // Complexity Theta(1)
{
	if (!this->valid())
		throw std::exception();

	this->curr = c.next[this->curr];
}

bool ListIterator::valid() const // Complexity Theta(1)
{
	if (curr == -1)
		return false;

	return true;
}

TElem ListIterator::getCurrent() const // Complexity Theta(1)
{
	if (!this->valid())
		throw std::exception();

	return c.elems[curr];
}
