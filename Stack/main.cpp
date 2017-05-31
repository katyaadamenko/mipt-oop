#include <iostream>
#include "Stack.h"
#include "checkBracketExpression.h"
using namespace std;

int main() {
	char bracketExpression[1000];
	cout << "Enter bracket expression:" << endl;
	cin >> bracketExpression;
	bool isCorrect = checkBracketExpression(bracketExpression);
	if (isCorrect)
		cout << "This bracket expression is correct" << endl;
	else
		cout << "This bracket expression is incorrect" << endl;
	char c;
	cin >> c;
	return 0;
}

