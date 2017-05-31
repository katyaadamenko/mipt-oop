#ifndef ACTION
#define ACTION

#include <iostream>
#include <string>
#include <vector>
using namespace std;

typedef vector<string> TextType;

struct CursorPosition {
	size_t numberOfLine;
	size_t numberOfPosition;
	CursorPosition(size_t numberOfLine = 0, size_t numberOfPosition = 0) : 
		numberOfLine(numberOfLine), numberOfPosition(numberOfPosition) {}
};

class Action {
	TextType & text;
	CursorPosition cursorPosition;
protected:
	TextType & getText() {
		return text;
	}
	string getLine(int i)const {
		return text[i];
	}
	string & getLine(int i) {
		return text[i];
	}
	CursorPosition & getCursorPosition() {
		return cursorPosition;
	}
	CursorPosition getCursorPosition()const {
		return cursorPosition;
	}
	size_t getNumberOfline()const {
		return cursorPosition.numberOfLine;
	}
	size_t getNumberOfPosition()const {
		return cursorPosition.numberOfPosition;
	}
	size_t & getNumberOfline() {
		return cursorPosition.numberOfLine;
	}
	size_t & getNumberOfPosition() {
		return cursorPosition.numberOfPosition;
	}
public:
	Action(TextType & text, size_t numberOfLine = 0, size_t numberOfPosition = 0) : 
		text(text), cursorPosition(numberOfLine, numberOfPosition) {}
	Action(TextType & text, const CursorPosition & cursorPosition) : 
		text(text), cursorPosition(cursorPosition) {}
	virtual CursorPosition Do() = 0;
	virtual CursorPosition Undo() = 0;
};

class Insertion : public Action {
	const char c;
public:
	Insertion(TextType & text, const char c, CursorPosition cursorPosition) : 
		Action(text, cursorPosition), c(c) {}
	Insertion(TextType & text, const char c, size_t numberOfLine = 0, size_t numberOfPosition = 0) : 
		Action(text, numberOfLine, numberOfPosition), c(c) {}
	CursorPosition Do();
	CursorPosition Undo();
};

class Deletion : public Action {
	const char c;
public:
	Deletion(TextType & text, const char c, CursorPosition cursorPosition) : 
		Action(text, cursorPosition), c(c) {}
	Deletion(TextType & text, const char c, size_t numberOfLine = 0, size_t numberOfPosition = 0) : 
		Action(text, numberOfLine, numberOfPosition), c(c) {}
	CursorPosition Do();
	CursorPosition Undo();
};

class NewLine : public Action {
public:
	NewLine(TextType & text, size_t numberOfLine = 0, size_t numberOfPosition = 0) : 
		Action(text, numberOfLine, numberOfPosition) {}
	NewLine(TextType & text, const CursorPosition & cursorPosition) : 
		Action(text, cursorPosition) {}
	CursorPosition Do();
	CursorPosition Undo();
};

class Backspace : public Action {
	const char c;
	CursorPosition newCursorPosition;
public:
	Backspace(TextType & text, const char c, size_t numberOfLine = 0, size_t numberOfPosition = 0) :
		Action(text, numberOfLine, numberOfPosition), c(c) {
		newCursorPosition = getCursorPosition();
		if (getNumberOfPosition() == 0 &&
			getNumberOfline() != 0) {
			--newCursorPosition.numberOfLine;
			newCursorPosition.numberOfPosition = getText()[newCursorPosition.numberOfLine].length();
		}
		else
			--newCursorPosition.numberOfPosition;
	}
	CursorPosition Do();
	CursorPosition Undo();
};

#endif