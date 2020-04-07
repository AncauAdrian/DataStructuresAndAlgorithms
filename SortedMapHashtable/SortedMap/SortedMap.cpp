#include "SortedMap.h"
#include "SMIterator.h"
#include <iostream>
#include <math.h>

SortedMap::SortedMap(Relation r) // complexity O(m)
{
	this->rel = r;
	this->arr = new Node * [this->m];

	for (int i = 0; i < this->m; i++)
	{
		this->arr[i] = nullptr;
	}
}

int SortedMap::hash(TKey key) const // complexity Theta(1)
{
	return abs(key % this->m);
	//return key / 100;
}

void SortedMap::print() // complexity O(n)
{
	using namespace std;
	for (int i = 0; i < this->m; i++)
	{
		cout << i << ": ";

		Node* cur = this->arr[i];

		while (cur != nullptr)
		{
			cout << cur->data.first << "-" << cur->data.second << "  ";
			cur = cur->next;
		}

		cout << endl;
	}
}

TValue SortedMap::add(TKey c, TValue v) // complexity O(n)
{
	// Make TElem object and initialize it with c and v
	TElem data;
	data.first = c;
	data.second = v;

	this->realsize++;

	// Get the position from the hash function
	int pos = this->hash(c);

	// Get the head of the linked list from postion pos of arr
	Node* head = this->arr[pos];
	Node* n = new Node;
	n->data = data;
	n->next = nullptr;


	// if the head is nullptr that means the list is empty
	if (head == nullptr)
	{
		// create and insert the first element
		head = n;
		this->arr[pos] = head;
	}
	else if (this->rel(c, head->data.first) || c == head->data.first)
	{
		if (data.first == head->data.first)
		{
			TValue toreturn = head->data.second;
			head->data = data;
			this->realsize--;
			return toreturn;
		}
		n->next = head;
		head = n;
		this->arr[pos] = head;
	}
	else
	{
		Node* cur = head;
		while (cur->next != nullptr && cur->data.first != data.first && this->rel(cur->next->data.first, c))
			cur = cur->next;

		if (cur->data.first == data.first)
		{
			TValue toreturn = cur->data.second;
			cur->data = data;
			this->realsize--;
			return toreturn;
		}

		n->next = cur->next;
		cur->next = n;
	}

	return NULL_TVALUE;
}

TValue SortedMap::search(TKey c) const // complexity O(n)
{
	int pos = this->hash(c);

	Node* head = this->arr[pos];
	Node* cur = head;
	while (cur != nullptr && cur->data.first != c)
		cur = cur->next;

	if (cur == nullptr)
		return NULL_TVALUE;
	else
		return cur->data.second;
}

TValue SortedMap::remove(TKey c) // complexity O(n)
{
	int pos = this->hash(c);

	Node* head = this->arr[pos];
	Node* cur = head;

	if (head == nullptr)
		return NULL_TVALUE;


	if (head->data.first == c)
	{
		TValue toreturn = head->data.second;
		head = head->next;
		this->arr[pos] = head;
		this->realsize--;
		delete cur;
		return toreturn;
	}

	while (cur->next != nullptr && cur->next->data.first != c)
		cur = cur->next;

	if (cur->next == nullptr)
		return NULL_TVALUE;
	else
	{
		TValue toreturn = cur->next->data.second;
		Node* todelete = cur->next;
		cur->next = cur->next->next;
		this->realsize--;
		delete todelete;
		return toreturn;
	}
}

int SortedMap::size() const // complexity Theta(1)
{
	return this->realsize;
}

bool SortedMap::isEmpty() const // complexity Theta(1)
{
	if (this->realsize == 0)
		return true;

	return false;
}

SMIterator SortedMap::iterator() // complexity O(n)
{
	return SMIterator(*this);
}

SortedMap::~SortedMap() // complexity O(n)
{
	// For every linked list in this->arr
	for (int i = 0; i < this->m; i++)
	{
		// iterate through it and delete every node
		Node* cur = this->arr[i];

		if (cur == nullptr)
			continue;

		Node* todelete;
		while (cur->next != nullptr)
		{
			todelete = cur;
			cur = cur->next;
			delete todelete;
		}
		delete cur;
	}
	delete[] this->arr;
}
