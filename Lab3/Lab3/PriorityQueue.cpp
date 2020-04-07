#include "PriorityQueue.h"
#include <exception>

PriorityQueue::PriorityQueue(Relation r) // Complexity Theta(1)
{
	this->rel = r;
	head = nullptr;
}

void PriorityQueue::push(TElem e, TPriority p) // Complexity O(n)
{
	Element a;
	a.first = e;
	a.second = p;

	Node *n = new Node;
	n->e = a;
	n->next = nullptr;

	if (this->head == nullptr)
		this->head = n;
	else if (this->rel(p, this->head->e.second))
	{
		n->next = this->head;
		this->head = n;
	}
	else
	{
		Node *curnode = this->head;
		while (curnode->next != nullptr && this->rel(p, curnode->next->e.second) == false)
			curnode = curnode->next;

		n->next = curnode->next;
		curnode->next = n;
	}

}

Element PriorityQueue::top() const // Complexity Theta(1)
{
	if (this->head == nullptr)
		throw std::exception();

	/*Node *curnode = this->head;
	Node *max = curnode;
	while (curnode->next != nullptr)
	{
		if (max->e.second, curnode->e.second)
			max = curnode;

		curnode = curnode->next;
	}*/

	return this->head->e;
}

Element PriorityQueue::pop() // Complexity Theta(1)
{
	if (this->head == nullptr)
		throw std::exception();

	/*Node *curnode = this->head;
	Node *max = curnode;
	while (curnode->next != nullptr)
	{
		if (max->e.second, curnode->e.second)
			max = curnode;

		curnode = curnode->next;
	}*/

	Element ret = this->head->e;
	Node *todelete = this->head;
	this->head = this->head->next;
	delete todelete;

	return ret;
}

bool PriorityQueue::isEmpty() const // Complexity Theta(1)
{
	if (this->head == nullptr)
		return true;

	return false;
}

PriorityQueue::~PriorityQueue() // // Complexity Theta(n)
{
	if (this->head == nullptr)
		return;

	Node *curnode = this->head;
	Node *todelete;
	while (curnode->next != nullptr)
	{
		todelete = curnode;
		curnode = curnode->next;
		delete todelete;
	}

	delete curnode;
}
