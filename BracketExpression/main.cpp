#include <iostream>
#include <stack>
using namespace std;

const int numberOfBrackets = 4;
const char openingBrackets[numberOfBrackets] = { '{', '(', '[', '<' };
const char closingBrackets[numberOfBrackets] = { '}', ')', ']', '>' };

bool isOpeningBracket(char bracket);
bool arePairedBrackets(char openingBracket, char closingBracket);

int main() {
	stack <char> Stack;
	bool isCorrect = true;
	char bracket;
	while (cin >> bracket) {
		if (isOpeningBracket(bracket)) {
			Stack.push(bracket);
		}
		else {
			if (Stack.empty()) {
				isCorrect = false;
				break;
			}
			else {
				if (!arePairedBrackets(Stack.top(), bracket)) {
					isCorrect = false;
					break;
				}
				Stack.pop();
			}
		}
	}
	while (cin >> bracket) {
	}
	isCorrect = isCorrect && Stack.empty();
	if (isCorrect)
		cout << "YES" << endl;
	else
		cout << "NO" << endl;
	return 0;
}

bool isOpeningBracket(char bracket) {
	bool isOpening = false;
	for (int i = 0; i < numberOfBrackets; ++i)
		if (bracket == openingBrackets[i]) {
			isOpening = true;
			break;
		}
	return isOpening;
}

bool isClosingBracket(char bracket) {
	bool isClosing = false;
	for (int i = 0; i < numberOfBrackets; ++i)
		if (bracket == closingBrackets[i]) {
			isClosing = true;
			break;
		}
	return isClosing;
}

bool arePairedBrackets(char openingBracket, char closingBracket) {
	bool isPaired = false;
	for (int i = 0; i < numberOfBrackets; ++i)
		if (openingBracket == openingBrackets[i] && closingBracket == closingBrackets[i]) {
			isPaired = true;
			break;
		}
	return isPaired;
}