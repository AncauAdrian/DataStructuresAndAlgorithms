#pragma once

template <typename T>
class DynamicVector
{
	T *elems;
	int capacity;
	int size;
public:
	// Default constructor
	DynamicVector(int capacity = 32);

	// Copy constructor
	DynamicVector(const DynamicVector<T> &v);
	~DynamicVector();

	// Assignment operator overloading
	DynamicVector& operator=(const DynamicVector& v);

	DynamicVector& operator+(const T& e);

	// Subscript operator overloading
	T& operator[](int pos) const;

	// Add element to the vector
	void add(T e);

	// Add an element at the begining of the vector
	void add_first(T e);

	// Removes an element at index from vector
	void remove(int index);

	// Get current size of the vector
	int getSize() const;

private:
	// Resizes the current vector by a specified factor
	void resize(int factor = 2);
};


template <typename T>
DynamicVector<T>::DynamicVector(int capacity) // Complexity Theta(n)
{
	if (capacity <= 0)
		throw "[ERROR] Invalid capacity!";

	this->capacity = capacity;
	this->size = 0;

	this->elems = new T[capacity];
}

template <typename T>
DynamicVector<T>::DynamicVector(const DynamicVector<T> &v) // Complexity Theta(n)
{
	this->capacity = v.capacity;
	this->size = v.size;

	this->elems = new T[this->capacity];

	for (int i = 0; i < v.size; i++)
		this->elems[i] = v.elems[i];
}

template <typename T>
DynamicVector<T>::~DynamicVector() // Complexity Theta(1)
{
	delete[] this->elems;
}

template <typename T>
DynamicVector<T>& DynamicVector<T>::operator=(const DynamicVector<T>& v) // Complexity Theta(n)
{
	if (this == &v)
		return *this;

	this->size = v.size;
	this->capacity = v.capacity;

	T *aux = new T[this->capacity];

	delete[] this->elems;

	this->elems = aux;
	for (int i = 0; i < this->size; i++)
		this->elems[i] = v.elems[i];

	return *this;
}

template<typename T>
inline DynamicVector<T> & DynamicVector<T>::operator+(const T & e) // Complexity Theta(1)
{
	this->add(e);
	return *this;
}

template <typename T>
T& DynamicVector<T>::operator[](int pos) const // Complexity Theta(1)
{
	return this->elems[pos];
}

template <typename T>
void DynamicVector<T>::resize(int factor) // Complexity Theta(n)
{
	if (factor <= 1)
		throw "[ERROR] Cannot resize a vector by a factor or 1 or less";

	this->capacity *= factor;

	T* els = new T[this->capacity];
	for (int i = 0; i < this->size; i++)
		els[i] = this->elems[i];

	delete[] this->elems;
	this->elems = els;
}

template <typename T>
void DynamicVector<T>::add(T e) // Complexity Theta(1)
{
	if (this->size == this->capacity)
		this->resize();

	this->elems[this->size] = e;
	this->size++;
}

template <typename T>
void DynamicVector<T>::add_first(T e) // Complexity Theta(n)
{
	if (this->size == this->capacity)
		this->resize();

	for (int i = this->size; i > 0; i--)
		this->elems[i] = this->elems[i - 1];

	this->elems[0] = e;
	this->size++;
}

template <typename T>
void DynamicVector<T>::remove(int index) // Complexity O(n)
{
	for (int i = index; i < this->size - 1; i++)
		this->elems[i] = this->elems[i + 1];

	this->size--;
}

template <typename T>
int DynamicVector<T>::getSize() const // Complexity Theta(1)
{
	return this->size;
}