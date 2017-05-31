#include "Stack.h"

int main() {
	Stack <double> stack;
	stack.push(2);
	cout << stack.top() << endl;
	stack.push(4);
	cout << stack.top() << endl;
	cout << stack.size() << endl;
	if (stack.empty())
		cout << "Stack is empty" << endl;
	else
		cout << "Stack is not empty" << endl;
	try {
		cout << stack.top() << endl;
	}
	catch (out_of_range & ex) {
		cerr << ex.what() << endl;
	}
	try {
		stack.top() = 5;
		cout << stack.top() << endl;
	}
	catch (out_of_range & ex) {
		cerr << ex.what() << endl;
	}
	try {
		stack.pop();
		cout << stack.top() << endl;
	}
	catch (out_of_range & ex) {
		cerr << ex.what() << endl;
	}
	try {
		stack.pop();
		stack.pop();
	}
	catch (out_of_range & ex) {
		cerr << ex.what() << endl;
	}
	try {
		stack.top();
	}
	catch (out_of_range & ex) {
		cerr << ex.what() << endl;
	}
	return 0;
}