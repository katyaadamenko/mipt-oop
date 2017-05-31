#include "Stack1.h"

void Stack::push(info_t value) {
	++top;
	Array[top] = value;
}

info_t Stack::pop() {
	info_t infoOfTop;
	infoOfTop = Array[top];
	--top;
	return infoOfTop;
}

bool Stack::isEmpty() {
	if (top == -1)
		return true;
	else
		return false;
}

info_t Stack::getTop() {
	return Array[top];
}