#ifndef STACK
#define STACK

typedef char info_t;
class Stack {
	struct Node {
		info_t info;
		Node *prev;
		Node(info_t i, Node *pr) {
			info = i;
			prev = pr;
		}
	};
	Node *top;
public:
	void push(info_t value);
	info_t pop();
	bool isEmpty();
	info_t getTop();
	Stack() {
		top = nullptr;
	}
	~Stack();
};

#endif

