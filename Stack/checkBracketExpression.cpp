#include "checkBracketExpression.h"
#include "Stack1.h"

const int numberOfBrackets = 3;
const char openingBrackets[numberOfBrackets] = {'{', '(', '['};
const char closingBrackets[numberOfBrackets] = { '}', ')', ']' };

bool isOpeningBracket(char bracket) {
	bool isOpening = false;
	for (int i = 0; i < numberOfBrackets; ++i) {
		if (bracket == openingBrackets[i]) {
			isOpening = true;
			break;
		}
	}
	return isOpening;
}

bool isClosingBracket(char bracket) {
	bool isClosing = false;
	for (int i = 0; i < numberOfBrackets; ++i) {
		if (bracket == closingBrackets[i]) {
			isClosing = true;
			break;
		}
	}
	return isClosing;
}

bool arePairedBrackets(char openingBracket, char closingBracket) {
	bool arePaired = false;
	for (int i = 0; i < numberOfBrackets; ++i) {
		if (openingBracket == openingBrackets[i] && closingBracket == closingBrackets[i]) {
			arePaired = true;
			break;
		}
	}
	return arePaired;
}

bool checkBracketExpression(const char *bracketExpression) {
	Stack stack;
	bool isCorrect = true;
	for (int i = 0; bracketExpression[i] != '\0'; ++i) {
		if (isOpeningBracket(bracketExpression[i]))
			stack.push(bracketExpression[i]);
		else {
			if (stack.isEmpty()) {
				isCorrect = false;
				break;
			}
			if (arePairedBrackets(stack.getTop(), bracketExpression[i]))
				stack.pop();
			else
				isCorrect = false;
		}
		if (!isCorrect)
			break;
	}
	isCorrect = isCorrect * stack.isEmpty();
	return isCorrect;
}