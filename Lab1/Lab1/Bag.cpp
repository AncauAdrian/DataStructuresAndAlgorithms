#include "Bag.h"
#include "Iterator.h"


Bag::Bag()
{
	this->max = 0;
	this->min = 0;
	this->realsize = 0;
}

void Bag::add(TElem e) // Complexity O(n)
{
	if (this->list.getSize() == 0)
	{
		list.add(1);
		this->min = e;
		this->max = e;
		this->realsize++;
	}
	else if (e < this->min)
	{
		int times = this->min - e;  // -3 2 > 5        -3 0 > 3      1 2 > 1       -5 -3 > 2
		for (int i = 0; i < times; i++)
			list.add_first(0);

		list[0] = 1;
		this->min = e;
		this->realsize++;
	}
	else if (e > this->max)
	{
		int times = e - this->max;  // 3 1 > 2   1 -1 > 2
		for (int i = 0; i < times; i++)
			list.add(0);

		list[this->list.getSize() - 1] = 1;
		this->max = e;
		this->realsize++;
	}
	else
	{
		this->list[e - this->min]++;
		this->realsize++;
	}
}

bool Bag::remove(TElem e) // Complexity Theta(1)
{
	if (this->size() == 0)
		return false;

	if (e < this->min || e > this->max)
		return false;

	if (this->list[e - this->min] == 0)
		return false;

	this->list[e - this->min]--;

	this->realsize--;

	return true;
}

bool Bag::search(TElem e) const // Complexity Theta(1)
{
	if (this->size() == 0)
		return false;

	if (e < this->min || e > this->max)
		return false;

	if (this->list[e - this->min] == 0)
		return false;

	return true;
}

int Bag::nrOccurrences(TElem e) const // Complexity Theta(1)
{
	if (this->size() == 0)
		return false;

	if (e < this->min || e > this->max)
		return 0;

	return this->list[e - this->min];
}

int Bag::size() const // Complexity Theta(1)
{
	return this->realsize;
}

BagIterator Bag::iterator() const // Complexity Theta(1)
{
	return BagIterator(*this);
}

bool Bag::isEmpty() const // Complexity Theta(1)
{
	if (this->size() == 0)
		return true;

	return false;
}

int Bag::elementsWithMinimumFrequency() const
{
	if (this->isEmpty())
		return 0;

	int min = 99999999;

	for (int i = 0; i < this->list.getSize(); i++)
	{
		if (this->list[i] < min && this->list[i] != 0)
			min = this->list[i];
	}

	int count = 0;

	for (int i = 0; i < this->list.getSize(); i++)
	{
		if (this->list[i] == min)
			count++;
	}
	
	return count;
}
