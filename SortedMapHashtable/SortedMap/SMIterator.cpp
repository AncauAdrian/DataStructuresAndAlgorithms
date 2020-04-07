#include "SMIterator.h"
#include <exception>

SMIterator::SMIterator(SortedMap& c) : c(c) // complexity O(m)
{
	if (c.isEmpty())
		return;

	this->mins = new Node * [c.m];

	this->first();
}

SMIterator::~SMIterator() // complexity O(n)
{
	delete[] this->mins;
}

void SMIterator::first() // complexity O(m)
{
	if (c.isEmpty())
		return;

	this->minlength = 0;
	this->cur = -1;
	for (int i = 0; i < c.m; i++)
	{
		if (c.arr[i] == nullptr)
			this->mins[i] = nullptr;
		else
		{
			this->mins[i] = c.arr[i];
			this->minlength++;

			if (cur == -1)
				cur = i;
			else
			{
				if (c.rel(mins[i]->data.first, this->mins[cur]->data.first))
				{
					cur = i;
				}
			}
		}
	}
}

void SMIterator::next() // complexity O(m)
{
	if (!this->valid())
		throw std::exception();

	if (this->mins[cur]->next == nullptr)
	{
		this->mins[cur] = nullptr;
		this->minlength--;
	}
	else
	{
		this->mins[cur] = this->mins[cur]->next;
	}

	cur = -1;

	for (int i = 0; i < c.m; i++)
	{
		if (this->mins[i] != nullptr)
		{
			if (cur == -1)
				cur = i;
			else if (c.rel(mins[i]->data.first, mins[cur]->data.first))
			{
				cur = i;
			}
		}
	}

}

bool SMIterator::valid() const // complexity Theta(1)
{
	if (this->minlength == 0)
		return false;

	return true;
}

TElem SMIterator::getCurrent() const // complexity Theta(1)
{
	if (!this->valid())
		throw std::exception();

	return this->mins[cur]->data;
}

TElem SMIterator::remove() // Complexity O(n)
{
	if (!this->valid())
		throw std::exception();

	TElem toreturn = this->getCurrent();
	this->next();
	
	c.remove(toreturn.first);

	return toreturn;
}
