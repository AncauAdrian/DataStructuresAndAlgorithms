#include "SMIterator.h"
#include <exception>

SMIterator::SMIterator(const SortedMap& c) : c(c) // complexity O(n)
{
	this->cur = c.getMinimum(c.root);
}

void SMIterator::first() // complexity O(n)
{
	this->cur = c.getMinimum(c.root);
}

void SMIterator::next() // complexity O(n)
{
	if (!this->valid())
		throw std::exception();

	this->cur = c.getSuccessor(this->cur);
}

bool SMIterator::valid() const // complexity Theta(1)
{
	if (this->cur == nullptr)
		return false;

	return true;
}

TElem SMIterator::getCurrent() const // complexity Theta(1)
{
	if (!this->valid())
		throw std::exception();

	return this->cur->data;
}
