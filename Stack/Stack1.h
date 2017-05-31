#ifndef STACK
#define STACK

typedef char info_t;
class Stack {
	static const int maxSize = 1000;
	info_t Array[maxSize];
	int top;
public:
	void push(info_t value);
	info_t pop();
	bool isEmpty();
	info_t getTop();
	Stack() {
		top = -1;
	}
};

#endif