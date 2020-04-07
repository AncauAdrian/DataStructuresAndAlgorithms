#include "BinaryHeap.h"


BinaryHeap::BinaryHeap(size_t size)
{
	this->elems = new Element[size];
	this->capacity = size;
	this->size = 0;
}

BinaryHeap::BinaryHeap(const BinaryHeap& heap)
{
	this->capacity = heap.capacity;
	this->size = heap.size;
	this->elems = new Element[this->capacity];

	for (size_t i = 0; i < heap.size; i++)
	{
		this->elems[i] = heap.elems[i];
	}
}

BinaryHeap& BinaryHeap::operator=(const BinaryHeap& heap)
{
	if (this == &heap)
		return *this;

	this->capacity = heap.capacity;
	this->size = heap.size;

	delete[] elems;
	this->elems = new Element[this->capacity];

	for (size_t i = 0; i < this->size; i++)
	{
		this->elems[i] = heap.elems[i];
	}

	return *this;
}

Element& BinaryHeap::operator[](size_t pos)
{
	if (pos > this->size)
		throw;

	return this->elems[pos];
}

BinaryHeap::~BinaryHeap()
{
	delete[] this->elems;
}

void BinaryHeap::resize(size_t factor)
{
	this->capacity *= factor;
	Element* aux = new Element[this->capacity];

	for (size_t i = 0; i < this->size; i++)
	{
		aux[i] = this->elems[i];
	}

	delete[] elems;

	this->elems = aux;
}

size_t BinaryHeap::getSize() const
{
	return this->size;
}

void BinaryHeap::add(Element e, Relation r)
{
	if (this->size == this->capacity)
		this->resize();

	this->elems[this->size] = e;
	this->size++;
	this->bubbleUp(this->size - 1, r);
}

void BinaryHeap::bubbleUp(size_t pos, Relation r)
{
	size_t cur = pos, parent = (pos - 1) / 2;
	Element belem = this->elems[pos];


	while (cur > 0 && r(belem.second, this->elems[parent].second))
	{
		this->elems[cur] = this->elems[parent];
		cur = parent;
		parent = (cur - 1) / 2;
	}

	this->elems[cur] = belem;
}

Element BinaryHeap::top(Relation r) const
{
	if (this->size < 2)
		throw std::exception();

	size_t second = 1;

	if (this->size > 2)
	{
		if (r(this->elems[2].second, this->elems[1].second))
			second++;
	}

	return this->elems[second];
}

Element BinaryHeap::remove(Relation r)
{
	if (this->size == 0)
		throw std::exception();

	Element deleted = this->elems[0];
	this->elems[0] = this->elems[this->size - 1];
	this->size--;
	this->bubbleDown(0, r);

	return deleted;
}

Element BinaryHeap::remove_second(Relation r)
{
	if (this->size < 2)
		throw std::exception();

	size_t second = 1;

	if (this->size > 2)
	{
		if (r(this->elems[2].second, this->elems[1].second))
			second++;
	}

	Element deleted = this->elems[second];
	this->elems[second] = this->elems[this->size - 1];
	this->size--;
	this->bubbleDown(second, r);

	return deleted;
}

void BinaryHeap::bubbleDown(size_t pos, Relation r)
{
	size_t cur = pos;
	Element elem = this->elems[pos];

	while (cur < this->size)
	{
		size_t maxChild = 0;

		if (cur * 2 + 1 < this->size)
		{
			maxChild = cur * 2 + 1;

			if (maxChild + 1 < this->size && r(this->elems[maxChild + 1].second, this->elems[maxChild].second))
				maxChild++;
		}

		if (maxChild != 0 && !r(elem.second, this->elems[maxChild].second))
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

//void testHeap()
//{
//	BinaryHeap heap;
//
//	heap.add(99, );
//	heap.add(75, );
//	heap.add(10, );
//	heap.add(33, );
//	heap.add(49, );
//	heap.add(12, );
//	heap.add(100, );
//	heap.add(3, );
//	heap.add(41, );
//	heap.add(90, );
//
//
//	/*for (size_t i = 0; i < heap.getSize(); i++)
//	{
//		std::cout << heap[i] << ' ';
//	}
//	std::cout << std::endl;*/
//
//	assert(heap[0] == 100);
//	assert(heap[1] == 90);
//	assert(heap[2] == 99);
//	assert(heap[3] == 41);
//	assert(heap[4] == 75);
//	assert(heap[5] == 10);
//	assert(heap[6] == 12);
//	assert(heap[7] == 3);
//	assert(heap[8] == 33);
//	assert(heap[9] == 49);
//
//	assert(heap.remove() == 100);
//
//	/*for (size_t i = 0; i < heap.getSize(); i++)
//	{
//		std::cout << heap[i] << ' ';
//	}
//	std::cout << std::endl;*/
//
//	assert(heap[0] == 99);
//	assert(heap[1] == 90);
//	assert(heap[2] == 49);
//	assert(heap[3] == 41);
//	assert(heap[4] == 75);
//	assert(heap[5] == 10);
//	assert(heap[6] == 12);
//	assert(heap[7] == 3);
//	assert(heap[8] == 33);
//
//	assert(heap.remove() == 99);
//
//	/*for (size_t i = 0; i < heap.getSize(); i++)
//	{
//		std::cout << heap[i] << ' ';
//	}
//	std::cout << std::endl;*/
//
//	assert(heap[0] == 90);
//	assert(heap[1] == 75);
//	assert(heap[2] == 49);
//	assert(heap[3] == 41);
//	assert(heap[4] == 33);
//	assert(heap[5] == 10);
//	assert(heap[6] == 12);
//	assert(heap[7] == 3);
//
//	heap.remove_second();
//
//	/*for (size_t i = 0; i < heap.getSize(); i++)
//	{
//		std::cout << heap[i] << ' ';
//	}
//	std::cout << std::endl;*/
//
//	assert(heap[0] == 90);
//	assert(heap[1] == 41);
//	assert(heap[2] == 49);
//	assert(heap[3] == 3);
//	assert(heap[4] == 33);
//	assert(heap[5] == 10);
//	assert(heap[6] == 12);
//}
