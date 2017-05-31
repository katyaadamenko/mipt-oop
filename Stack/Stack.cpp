#include "Stack.h"
#include <iostream>
using namespace std;

void Stack::push(info_t value) {
	Node *newNode = new Node(value, top);
	top = newNode;
}

info_t Stack::pop() {
	info_t infoOfTop;
	Node *pointerTop = top;
	infoOfTop = top->info;
	top = top->prev;
	delete pointerTop;
	return infoOfTop;
}

bool Stack::isEmpty() {
	if (top == nullptr)
		return true;
	else
		return false;
}

info_t Stack::getTop() {
	if (!top) {
		cerr << "Stack is empty" << endl;
		return '0';
	}
	else
		return top->info;
}

Stack::~Stack() {
	while (!isEmpty())
		pop();
}