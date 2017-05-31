#include "Action.h"

CursorPosition Insertion::Do() {
	if (getText().size() == 0) {
		string s;
		getText().push_back(s);
	}
	string & str = getLine(getNumberOfline());
	string::iterator position = str.begin() + getNumberOfPosition();
	str.insert(position, this->c);
	CursorPosition newCursorPosition(getNumberOfline(),getNumberOfPosition() + 1);
	return newCursorPosition;
}

CursorPosition Insertion::Undo() {
	string & str = getLine(getNumberOfline());
	string::iterator position = str.begin() + getNumberOfPosition();
	str.erase(position);
	CursorPosition newCursorPosition(getCursorPosition());
	return newCursorPosition;
}

CursorPosition Deletion::Do() {
	string & str = getLine(getNumberOfline());
	string::iterator position = str.begin() + getNumberOfPosition();
	if (getNumberOfPosition() == getLine(getNumberOfline()).length() &&
			getNumberOfline() != getText().size() - 1) {
		getLine(getNumberOfline()) += getLine(getNumberOfline() + 1);
		vector<string>::iterator it = getText().begin() + getNumberOfline() + 1;
		getText().erase(it);
	}
	else if (getNumberOfPosition() != getLine(getNumberOfline()).length()) {
		str.erase(position);
	}
	CursorPosition newCursorPosition(getCursorPosition());
	return newCursorPosition;
}

CursorPosition Deletion::Undo() {
	if (this->c == '~') {
		NewLine newLine(getText(), getCursorPosition());
		newLine.Do();
	}
	else {
		Insertion insertion(getText(), this->c, getCursorPosition());
		insertion.Do();
	}
	CursorPosition newCursorPosition(getCursorPosition());
	return newCursorPosition;
}

CursorPosition Backspace::Do() {
	string & str = getLine(getNumberOfline());
	string::iterator position = str.begin() + getNumberOfPosition();
	if (getNumberOfPosition() == 0 &&
		getNumberOfline() != 0) {
		getLine(getNumberOfline() - 1) += getLine(getNumberOfline());
		vector<string>::iterator it = getText().begin() + getNumberOfline();
		this->getText().erase(it);
	}
	else if (this->getNumberOfPosition() != 0)
		str.erase(position - 1);
	return newCursorPosition;
}

CursorPosition Backspace::Undo() {
	if (this->c == '~') {
		int numberOfPosition = newCursorPosition.numberOfPosition;
		NewLine newLine(getText(), getNumberOfline() - 1, numberOfPosition);
		newLine.Do();
	}
	else {
		Insertion insertion(getText(), this->c, getNumberOfline(), getNumberOfPosition() - 1);
		insertion.Do();
	}
	CursorPosition newCursorPosition(getCursorPosition());
	return newCursorPosition;
}

CursorPosition NewLine::Do() {
	int numberOfStrings = getText().size();
	TextType::iterator it = getText().begin() + getNumberOfline() + 1;
	string str;
	str = getText()[getNumberOfline()].substr(getNumberOfPosition());
	getText().insert(it, str);
	str.clear();
	size_t length = getText()[getNumberOfline()].length() - getNumberOfPosition();
	getText()[getNumberOfline()].replace(getNumberOfPosition(), length, str);
	CursorPosition newCursorPosition(getNumberOfline() + 1, 0);
	return newCursorPosition;
}

CursorPosition NewLine::Undo() {
	CursorPosition newCursorPosition(getCursorPosition());
	Backspace backspace(getText(), '~', getNumberOfline() + 1, 0);
	backspace.Do();
	return newCursorPosition;
}