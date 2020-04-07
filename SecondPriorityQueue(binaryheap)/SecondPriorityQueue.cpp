#include "SecondPriorityQueue.h"
#include <exception>

SecondPriorityQueue::SecondPriorityQueue(Relation r)
{
	this->rel = r;
}

void SecondPriorityQueue::push(TElem e, TPriority p)
{
	Element a;
	a.first = e;
	a.second = p;

	this->heap.add(a, this->rel);
}

Element SecondPriorityQueue::top() const
{
	try {
		return heap.top(this->rel);
	}
	catch (std::exception & e)
	{
		throw e;
	}
}

Element SecondPriorityQueue::pop()
{
	try {
		return heap.remove_second(this->rel);
	}
	catch (std::exception & e)
	{
		throw e;
	}
}

bool SecondPriorityQueue::atMostOne() const
{
	if (heap.getSize() <= 1)
		return true;

	return false;
}