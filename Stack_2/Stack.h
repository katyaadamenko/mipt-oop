#ifndef STACK_1
#define STACK_1

#include "DynArray.h"

template <typename T>
class Stack {
	DynArray <T> array;
public:
	void push(const T & value) {
		array.push_back(value);
	}
	void pop();
	T & top();
	const T & top()const;
	size_t size()const {
		return array.getSize();
	}
	bool empty()const;
};

template <typename T>
T & Stack<T>::top() {
	if (size() == 0)
		throw out_of_range("Impossible to find top element. Stack is empty");
	return array[size() - 1];
}

template <typename T>
const T & Stack<T>::top()const {
	if (size() == 0)
		throw out_of_range("Impossible to find top element. Stack is empty");
	return array[size() - 1];
}

template <typename T>
void Stack<T>::pop() {
	try {
		array.pop_back();
	}
	catch (out_of_range ex) {
		throw out_of_range("Impossible to pop. Stack is empty");
	}
}

template <typename T>
bool Stack<T>::empty()const {
	bool isEmpty = false;
	if (size() == 0)
		isEmpty = true;
	return isEmpty;
}

#endif STACK_1