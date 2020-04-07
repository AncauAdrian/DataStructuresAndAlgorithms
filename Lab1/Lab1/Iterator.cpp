#include "Iterator.h"
#include <exception>

BagIterator::BagIterator(const Bag & c) : c(c)  // Complexity Theta(1)
{ 
	this->index = 0;
	this->count = 0;
}

void BagIterator::first() // Complexity Theta(n)
{
	this->index = 0;

	while (this->c.list[this->index] == 0 && this->index != this->c.list.getSize())
		this->index++;

	this->count = 0;
}

void BagIterator::next() // Complexity Theta(n)
{
	if (!this->valid())
		throw std::exception();

	if (this->count == this->c.list[this->index] - 1)
	{
		this->index++;

		while (this->c.list[this->index] == 0 && this->index != this->c.list.getSize())
			this->index++;

		this->count = 0;
	}
	else
		this->count++;
}

bool BagIterator::valid() const // Complexity Theta(1)
{
	if (this->c.isEmpty())
		return false;

	if (this->index == this->c.list.getSize())
		return false;

	return true;
}

TElem BagIterator::getCurrent() const // Complexity Theta(1)
{
	if (!this->valid())
		throw std::exception();

	return this->index + this->c.min;
}
