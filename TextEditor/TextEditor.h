#ifndef TEXT_EDITOR
#define TEXT_EDITOR

#include "Action.h"
#include <stack>

class TextEditor {
	TextType text;
	CursorPosition cursorPosition;
	stack<Action *> undoStack;
	stack<Action *> redoStack;
public:
	TextEditor();
	TextEditor(const TextEditor & textEditor) : text(textEditor.text),
		cursorPosition(textEditor.cursorPosition),
		undoStack(textEditor.undoStack), redoStack(textEditor.redoStack) {}
	TextEditor(TextType & text) : cursorPosition(0, 0), text(text){}
	~TextEditor();
	TextEditor & operator=(const TextEditor & textEditor) {
		text = textEditor.text;
		cursorPosition = textEditor.cursorPosition;
		undoStack = textEditor.undoStack;
		redoStack = textEditor.redoStack;
		return *this;
	}
	TextType TextEditor::getText()const {
		return text;
	}
	void doAction(Action * a) {
		cursorPosition = a->Do();
		undoStack.push(a);
	}
	void undoAction(){
		if (undoStack.empty())
			throw out_of_range("There are no actions to undo");
		while (undoStack.top() == nullptr && !undoStack.empty())
			undoStack.pop();
		if (undoStack.empty())
			throw out_of_range("There are no actions to undo");
		Action * a = undoStack.top();
		undoStack.pop();
		redoStack.push(a);
		cursorPosition = a->Undo();
	}
	void cursorLeft() {
		if (cursorPosition.numberOfPosition != 0)
			--cursorPosition.numberOfPosition;
		else if (cursorPosition.numberOfLine != 0)
			cursorPosition.numberOfPosition = text[--cursorPosition.numberOfLine].length();
	}
	void cursorRight();
	void cursorUp() {
		if (cursorPosition.numberOfLine != 0) {
			--cursorPosition.numberOfLine;
			if (cursorPosition.numberOfPosition > text[cursorPosition.numberOfLine].length())
				cursorPosition.numberOfPosition = text[cursorPosition.numberOfLine].length();
		}
	}
	void cursorDown() {
		if (cursorPosition.numberOfLine == text.size() - 1) {
			string str;
			text.push_back(str);
		}
		++cursorPosition.numberOfLine;
		if (cursorPosition.numberOfPosition > text[cursorPosition.numberOfLine].length())
			cursorPosition.numberOfPosition = text[cursorPosition.numberOfLine].length();
	}
	Action * codeToAction(pair<int, int> code);
	void makeChanges(pair<int, int> code);
};

#endif