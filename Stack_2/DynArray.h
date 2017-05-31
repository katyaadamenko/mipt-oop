#ifndef DYN_ARRAY
#define DYN_ARRAY
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
using namespace std;

template <typename T>
class DynArray {
	T * buf;
	size_t size;
	size_t capacity;
	static const int n = 2;
	void copy(const DynArray<T>& d);
	void increaseCapacity();
public:
	DynArray(size_t capacity = 1);
	~DynArray();
	DynArray(const DynArray<T>& d);
	T operator[](size_t i)const {
		if (i >= capacity)
			throw out_of_range("Wrong index");
		return buf[i];
	}
	T & operator[](size_t i) {
		if (i >= capacity)
			throw out_of_range("Wrong index");
		return buf[i];
	}
	size_t getSize()const {
		return size;
	}
	size_t getCapacity()const {
		return capacity;
	}
	DynArray<T> & operator = (const DynArray<T> & d);
	void push_back(const T & value);
	void pop_back();
	void insert(const T & value, size_t i);
	void erase(size_t i);
};

template <typename T>
DynArray<T>::DynArray(size_t capacity) : capacity(capacity) {
	buf = new T[capacity];
	size = 0;
}

template <>
DynArray<char *>::~DynArray() {
	for (size_t i = 0; i < size; ++i)
		delete[]buf[i];
	delete[] buf;
}

template <typename T>
DynArray<T>:: ~DynArray() {
	delete[] buf;
}

template <>
void DynArray<char *>::copy(const DynArray<char *> & d) {
	this->size = d.size;
	this->capacity = d.capacity;
	for (size_t i = 0; i < size; ++i)
		strcpy(buf[i], d.buf[i]);
}

template <typename T>
void DynArray<T>::copy(const DynArray<T>& d) {
	this->size = d.size;
	this->capacity = d.capacity;
	for (size_t i = 0; i < size; ++i)
		buf[i] = d.buf[i];
}

template <>
DynArray<char *>::DynArray(const DynArray<char *> & d) {
	buf = new char *[d.capacity];
	for (size_t i = 0; i < size; ++i)
		buf[i] = new char[strlen(d.buf[i]) + 1];
	copy(d);
}

template <typename T>
DynArray<T>::DynArray(const DynArray<T> & d) {
	buf = new T[d.capacity];
	copy(d);
}

template <>
DynArray<char *> & DynArray<char *>::operator = (const DynArray<char *> & d) {
	if (this != &d) {
		char ** newBuf = new char *[d.capacity];
		for (size_t i = 0; i < size; ++i)
			newBuf[i] = new char[strlen(d.buf[i]) + 1];
		for (size_t i = 0; i < size; ++i)
			delete[] buf[i];
		delete[] buf;
		buf = newBuf;
		copy(d);
	}
	return *this;
}

template <typename T>
DynArray<T> & DynArray<T>::operator = (const DynArray<T> & d) {
	if (this != &d) {
		T * newBuf = new T[d.capacity];
		delete[] buf;
		buf = newBuf;
		copy(d);
	}
	return *this;
}

template <>
void DynArray<char *>::increaseCapacity() {
	char ** newBuf = new char *[capacity * n];
	for (size_t i = 0; i < size; ++i)
		newBuf[i] = new char[strlen(buf[i]) + 1];
	for (size_t i = 0; i < capacity; ++i)
		strcpy(newBuf[i], buf[i]);
	for (size_t i = 0; i < size; ++i)
		delete[] buf[i];
	delete[] buf;
	buf = newBuf;
	capacity *= n;
}

template <typename T>
void DynArray<T>::increaseCapacity() {
	T * newBuf = new T[capacity * n];
	for (size_t i = 0; i < capacity; ++i)
		newBuf[i] = buf[i];
	delete[] buf;
	buf = newBuf;
	capacity *= n;
}

template <>
void DynArray<char *>::push_back(char * const & value) {
	if (size == capacity)
		increaseCapacity();
	char * newBuf = new char[strlen(value) + 1];
	buf[size++] = newBuf;
	strcpy(buf[size - 1], value);
}

template <typename T>
void DynArray<T>::push_back(const T & value) {
	if (size == capacity)
		increaseCapacity();
	buf[size++] = value;
}

template <>
void DynArray<char *>::insert(char * const & value, size_t i) {
	if (i < 0 || i > size)
		throw out_of_range("Impossible to insert value. Wrong index");
	if (size == capacity)
		increaseCapacity();
	char * ptr = new char[strlen(value) + 1];
	for (size_t j = size; j > i; --j)
		buf[j] = buf[j - 1];
	++size;
	buf[i] = ptr;
	strcpy(buf[i], value);
}

template <typename T>
void DynArray<T>::insert(const T & value, size_t i) {
	if (i < 0 || i > size)
		throw out_of_range("Impossible to insert value. Wrong index");
	if (size == capacity)
		increaseCapacity();
	for (size_t j = size; j > i; --j)
		buf[j] = buf[j - 1];
	++size;
	buf[i] = value;
}

template <>
void DynArray<char *>::pop_back() {
	if (size == 0)
		throw out_of_range("Impossible to pop. Array is empty");
	--size;
	delete[] buf[size];
}

template <typename T>
void DynArray<T>::pop_back() {
	if (size == 0)
		throw out_of_range("Impossible to pop. Array is empty");
	--size;
}

template <>
void DynArray<char *>::erase(size_t i) {
	if (i >= size || i < 0)
		throw out_of_range("Impossible to delete this element. Wrong index");
	delete[] buf[i];
	for (size_t j = i; j < size - 1; ++j)
		buf[j] = buf[j + 1];
	--size;
}

template <typename T>
void DynArray<T>::erase(size_t i) {
	if (i >= size || i < 0)
		throw out_of_range("Impossible to delete this element. Wrong index");
	for (size_t j = i; j < size - 1; ++j)
		buf[j] = buf[j + 1];
	--size;
}

#endif DYN_ARRAY