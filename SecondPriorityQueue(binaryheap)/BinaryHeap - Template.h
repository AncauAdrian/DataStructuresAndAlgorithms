#pragma once
#pragma warning (disable : 6386)

#include <assert.h>
#include <iostream>

template<class E>
class BinaryHeap
{
	E* elems;
	size_t capacity, size;
public:

	// Default Constructor
	BinaryHeap(size_t size = 64);

	// Copy Constructor
	BinaryHeap(const BinaryHeap<E>& heap);

	// Assignment Operator Overload
	BinaryHeap<E>& operator=(const BinaryHeap<E>& heap);

	// Subscript Operator Overload
	E& operator[](size_t pos);

	// Default Destructor
	~BinaryHeap();

	// Resize function for elems array
	void resize(size_t factor = 2);

	// Size getter
	size_t getSize();

	// Add to heap function
	void add(E e);

	// Bubble Up from pos to preserve the heap property
	void bubbleUp(size_t pos);

	// Remove the root, first in priority
	E remove();

	// Remove the element with the second priority
	E remove_second();

	// Bubble Down from pos
	void bubbleDown(size_t pos);
};


template<class E>
BinaryHeap<E>::BinaryHeap(size_t size)
{
	this->elems = new E[size];
	this->capacity = size;
	this->size = 0;
}

template<class E>
BinaryHeap<E>::BinaryHeap(const BinaryHeap<E>& heap)
{
	this->capacity = heap.capacity;
	this->size = heap.size;
	this->elems = new E[this->capacity];

	for (size_t i = 0; i < heap.size; i++)
	{
		this->elems[i] = heap.elems[i];
	}
}

template<class E>
BinaryHeap<E>& BinaryHeap<E>::operator=(const BinaryHeap<E>& heap)
{
	if (this == &heap)
		return *this;

	this->capacity = heap.capacity;
	this->size = heap.size;

	delete[] elems;
	this->elems = new E[this->capacity];

	for (size_t i = 0; i < this->size; i++)
	{
		this->elems[i] = heap.elems[i];
	}

	return *this;
}

template<class E>
E& BinaryHeap<E>::operator[](size_t pos)
{
	if (pos > this->size)
		throw;

	return this->elems[pos];
}

template<class E>
BinaryHeap<E>::~BinaryHeap()
{
	delete[] this->elems;
}

template<class E>
void BinaryHeap<E>::resize(size_t factor)
{
	this->capacity *= factor;
	E *aux = new E[this->capacity];
	
	for (size_t i = 0; i < this->size; i++)
	{
		aux[i] = this->elems[i];
	}

	this->elems = aux;

	delete[] aux;
}

template<class E>
size_t BinaryHeap<E>::getSize()
{
	return this->size;
}

template<class E>
void BinaryHeap<E>::add(E e)
{
	if (this->size == this->capacity)
		this->resize();

	this->elems[this->size] = e;
	this->size++;
	this->bubbleUp(this->size - 1);
}

template<class E>
void BinaryHeap<E>::bubbleUp(size_t pos)
{
	size_t cur = pos, parent = (pos - 1) / 2;
	E belem = this->elems[pos];

	while (cur > 0 && belem > this->elems[parent])
	{
		this->elems[cur] = this->elems[parent];
		cur = parent;
		parent = (cur - 1) / 2;
	}

	this->elems[cur] = belem;
}

template<class E>
E BinaryHeap<E>::remove()
{
	if (this->size == 0)
		throw;

	E deleted = this->elems[0];
	this->elems[0] = this->elems[this->size - 1];
	this->size--;
	this->bubbleDown(0);
	
	return deleted;
}

template<class E>
E BinaryHeap<E>::remove_second()
{
	if (this->size < 2)
		throw;
	
	size_t second = 1;

	if (this->size > 2)
	{
		if (this->elems[2] > this->elems[1])
			second++;
	}

	E deleted = this->elems[second];
	this->elems[second] = this->elems[this->size - 1];
	this->size--;
	this->bubbleDown(second);

	return deleted;
}

template<class E>
void BinaryHeap<E>::bubbleDown(size_t pos)
{
	size_t cur = pos;
	E elem = this->elems[pos];

	while (cur < this->size)
	{
		size_t maxChild = 0;

		if (cur * 2 + 1 < this->size)
		{
			maxChild = cur * 2 + 1;

			if (maxChild + 1 < this->size && this->elems[maxChild + 1] > this->elems[maxChild])
				maxChild++;
		}

		if (maxChild != 0 && elem < this->elems[maxChild])
		{
			this->elems[cur] = this->elems[maxChild];
			cur = maxChild;
		}
		else
		{
			this->elems[cur] = elem;
			break;
		}
	}
}

void testHeap()
{
	BinaryHeap<int> heap;

	heap.add(99);
	heap.add(75);
	heap.add(10);
	heap.add(33);
	heap.add(49);
	heap.add(12);
	heap.add(100);
	heap.add(3);
	heap.add(41);
	heap.add(90);

	
	/*for (size_t i = 0; i < heap.getSize(); i++)
	{
		std::cout << heap[i] << ' ';
	}
	std::cout << std::endl;*/

	assert(heap[0] == 100);
	assert(heap[1] == 90);
	assert(heap[2] == 99);
	assert(heap[3] == 41);
	assert(heap[4] == 75);
	assert(heap[5] == 10);
	assert(heap[6] == 12);
	assert(heap[7] == 3);
	assert(heap[8] == 33);
	assert(heap[9] == 49);

	assert(heap.remove() == 100);

	/*for (size_t i = 0; i < heap.getSize(); i++)
	{
		std::cout << heap[i] << ' ';
	}
	std::cout << std::endl;*/

	assert(heap[0] == 99);
	assert(heap[1] == 90);
	assert(heap[2] == 49);
	assert(heap[3] == 41);
	assert(heap[4] == 75);
	assert(heap[5] == 10);
	assert(heap[6] == 12);
	assert(heap[7] == 3);
	assert(heap[8] == 33);

	assert(heap.remove() == 99);

	/*for (size_t i = 0; i < heap.getSize(); i++)
	{
		std::cout << heap[i] << ' ';
	}
	std::cout << std::endl;*/

	assert(heap[0] == 90);
	assert(heap[1] == 75);
	assert(heap[2] == 49);
	assert(heap[3] == 41);
	assert(heap[4] == 33);
	assert(heap[5] == 10);
	assert(heap[6] == 12);
	assert(heap[7] == 3);

	heap.remove_second();

	/*for (size_t i = 0; i < heap.getSize(); i++)
	{
		std::cout << heap[i] << ' ';
	}
	std::cout << std::endl;*/
	
	assert(heap[0] == 90);
	assert(heap[1] == 41);
	assert(heap[2] == 49);
	assert(heap[3] == 3);
	assert(heap[4] == 33);
	assert(heap[5] == 10);
	assert(heap[6] == 12);
}