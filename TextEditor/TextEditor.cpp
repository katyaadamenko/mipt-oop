#include "TextEditor.h"
#include <cstdlib>

TextEditor::TextEditor() : cursorPosition(0, 0) {
	TextType text;
	this->text = text;
	stack<Action *> undoStack;
	stack<Action *> redoStack;
	this->undoStack = undoStack;
	this->redoStack = redoStack;
}

TextEditor:: ~TextEditor() {
	while (!undoStack.empty()) {
		delete undoStack.top();
		undoStack.pop();
	}
	while (!redoStack.empty()) {
		delete redoStack.top();
		redoStack.pop();
	}
}

void TextEditor::cursorRight() {
	if (cursorPosition.numberOfPosition != text[cursorPosition.numberOfLine].length())
		++cursorPosition.numberOfPosition;
	else {
		if (cursorPosition.numberOfLine == text.size() - 1) {
			string str;
			text.push_back(str);
		}
		cursorPosition.numberOfPosition = 0;
		++cursorPosition.numberOfLine;
	}
}

Action * TextEditor::codeToAction(pair<int, int> code) {
	Action * ptr;
	char c;
	int numberOfPreviousPosition = -1;
	if (code.first == 224 && code.second == 83) {
		if (cursorPosition.numberOfPosition == text[cursorPosition.numberOfLine].length() &&
			cursorPosition.numberOfLine == getText().size() - 1)
			ptr = nullptr;
		else {
			if (cursorPosition.numberOfPosition == text[cursorPosition.numberOfLine].length() &&
				cursorPosition.numberOfLine != getText().size() - 1)
				c = '~';
			else
				c = text[cursorPosition.numberOfLine][cursorPosition.numberOfPosition];
			ptr = new Deletion(text, c, cursorPosition.numberOfLine, cursorPosition.numberOfPosition);
		}
	}
	else if (code.first == 8 && code.second == 0) {
		if (cursorPosition.numberOfPosition == 0 &&
			cursorPosition.numberOfLine == 0)
			ptr = nullptr;
		else {
			if (cursorPosition.numberOfPosition == 0 &&
				cursorPosition.numberOfLine != 0)
				c = '~';
			else
				c = text[cursorPosition.numberOfLine][cursorPosition.numberOfPosition - 1];
			ptr = new Backspace(text, c, cursorPosition.numberOfLine, cursorPosition.numberOfPosition);
		}
	}
	else if (code.first == 13 && code.second == 0) {
		ptr = new NewLine(text, cursorPosition.numberOfLine, cursorPosition.numberOfPosition);
	}
	else if (code.second != 0)
		throw out_of_range("Impossible to create Action. Wrong code");
	else {
		c = (char)code.first;
		ptr = new Insertion(text, c, cursorPosition.numberOfLine, cursorPosition.numberOfPosition);
	}
	return ptr;
}

void TextEditor::makeChanges(pair<int, int> code) {
	if (code.first == 224 && code.second != 83) { // стрелки
		if (code.second == 75)
			this->cursorLeft();
		else if (code.second == 72)
			this->cursorUp();
		else if (code.second == 77)
			this->cursorRight();
		else if (code.second == 80)
			this->cursorDown();
	}
	else if (code.first == 26 && code.second == 0) //ctrl + z
		undoAction();
	else if (code.first == 25 && code.second == 0) { //ctrl + y
		if (redoStack.empty())
			throw out_of_range("There are no actions to redo");
		while (redoStack.top() == nullptr && !redoStack.empty())
			redoStack.pop();
		if (redoStack.empty())
			throw out_of_range("There are no actions to redo");
		Action * a = redoStack.top();
		redoStack.pop();
		this->doAction(a);
	}
	else {
		Action * a = codeToAction(code);
		if (a == nullptr)
			return;
		doAction(a);
		while (!redoStack.empty()) {
			delete redoStack.top();
			redoStack.pop();
		}
	}
	system("cls");
	for (size_t i = 0; i < this->text.size(); ++i)
		cout << this->text[i] << endl;
}