#include "IndexedList.h"
#include "ListIterator.h"
#include <exception>


IndexedList::IndexedList()	//Complexity O(n) because the next vector must be filled
{
	this->head = -1;

	for (int i = 0; i < this->cap - 1; i++)
		this->next[i] = i + 1;
	
	this->next[this->cap - 1] = -1;
	this->firstEmpty = 0;
	this->truesize = 0;
}

int IndexedList::size() const	// Theta(1)
{
	return this->truesize;
}

bool IndexedList::isEmpty() const // Theta(1)
{
	if (this->truesize == 0)
		return true;

	return false;
}

TElem IndexedList::getElement(int pos) const	// Complexity O(n) because it needs to iterate over the list to find the position
{

	if (pos < 0)
		throw std::exception();

	int pozCurrent = 0;
	int nodCurrent = this->head;

	while (nodCurrent != -1 and pozCurrent < pos)
	{
		pozCurrent++;
		nodCurrent = this->next[nodCurrent];
	}

	if (nodCurrent != -1)
	{
		return this->elems[nodCurrent];
	}
	else
		throw std::exception();
}

TElem IndexedList::setElement(int pos, TElem e) // Complexity O(n) same reason
{
	int old;

	if (pos < 0)
		throw std::exception();

	if (pos == 0)
	{
		old = this->elems[this->head];
		this->elems[this->head] = e;
	}

	else
	{
		int pozCurrent = 0;
		int nodCurrent = this->head;

		while (nodCurrent != -1 and pozCurrent < pos)
		{
			pozCurrent++;
			nodCurrent = this->next[nodCurrent];
		}

		if (nodCurrent != -1)
		{
			old = this->elems[nodCurrent];
			this->elems[nodCurrent] = e;
		}
		else
			throw std::exception();
	}
	
	return old;
}

void IndexedList::addToEnd(TElem e)		//Complexity O(n)
{
	if (this->firstEmpty == -1)
	{
		this->elems.resize();
		this->next.resize();

		for (int i = this->cap; i < this->cap * 2 - 1; i++)
			this->next[i] = i + 1;

		this->firstEmpty = this->cap;

		this->cap *= 2;
		this->next[this->cap - 1] = -1;
	}

	if (this->head == -1)
	{
		this->elems[this->firstEmpty] = e;
		int old = this->next[this->firstEmpty];
		this->next[this->firstEmpty] = -1;
		this->head = this->firstEmpty;
		this->firstEmpty = old;
	}
	else
	{
		int cur = this->head;
		while (this->next[cur] != -1)
			cur = this->next[cur];

		this->elems[this->firstEmpty] = e;
		this->next[cur] = this->firstEmpty;
		int old = this->next[this->firstEmpty];
		this->next[this->firstEmpty] = -1;

		this->firstEmpty = old;
	}
	this->truesize++;

}

void IndexedList::addToPosition(int pos, TElem e) //Complexity O(n)
{
	if (pos < 0)
		throw std::exception();

	// TO DO CHECK CORRECT

	if (this->firstEmpty == -1)
	{
		this->elems.resize();
		this->next.resize();

		for (int i = this->cap; i < this->cap * 2 - 1; i++)
			this->next[i] = i + 1;

		this->firstEmpty = this->cap;

		this->cap *= 2;
		this->next[this->cap - 1] = -1;
	}

	if (pos == 0)
	{
		int newPosition = this->firstEmpty;
		this->elems[newPosition] = e;
		this->firstEmpty = this->next[this->firstEmpty];
		this->next[newPosition] = this->head;
		this->head = newPosition;
	}
	else
	{
		int pozCurrent = 0;
		int nodCurrent = this->head;

		while (nodCurrent != -1 && pozCurrent < pos - 1)
		{
			pozCurrent++;
			nodCurrent = this->next[nodCurrent];
		}
		
		if (nodCurrent != -1)
		{
			int newElem = this->firstEmpty;
			this->firstEmpty = this->next[this->firstEmpty];
			this->elems[newElem] = e;
			this->next[newElem] = this->next[nodCurrent];
			this->next[nodCurrent] = newElem;
		}
		else
			throw std::exception();
	}
	this->truesize++;
}

TElem IndexedList::remove(int pos) // Complexity O(n)
{
	int pozCurrent = 0;
	int prev = -1;
	int nodCurrent = this->head;

	while (nodCurrent != -1 && pozCurrent < pos)
	{
		pozCurrent++;
		prev = nodCurrent;
		nodCurrent = this->next[nodCurrent];
	}

	if (nodCurrent != -1)
	{
		if (nodCurrent == this->head)
		{
			this->head = this->next[nodCurrent];
		}
		else
		{
			this->next[prev] = this->next[nodCurrent];
		}

		this->next[nodCurrent] = this->firstEmpty;
		this->firstEmpty = nodCurrent;
	}
	else
		throw std::exception();
	
	this->truesize--;
	return this->elems[nodCurrent];
}

int IndexedList::search(TElem e) const // Complexity O(n)
{
	int current = this->head, pos = 0;

	while (current != -1 && this->elems[current] != e)
	{
		current = this->next[current];
		pos++;
	}

	if (current == -1)
		return -1;

	return pos;
}

ListIterator IndexedList::iterator() const // Complexity Theta(1)
{
	return ListIterator(*this);
}

int IndexedList::lastIndexOf(TElem e) // Complexity Theta(n)
{
	int current = this->head, lastPos = -1;

	while (current != -1)
	{
		if (this->elems[current] == e)
			lastPos = current;

		current = this->next[current];
	}

	return lastPos;
}
