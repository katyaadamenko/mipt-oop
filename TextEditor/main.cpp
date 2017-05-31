#include <iostream>
#include <cctype>
#include <cstring>
#include <conio.h>
#include "TextEditor.h"
using namespace std;

int main() {
	TextEditor textEditor;
	pair <int, int> code;
	code.first = _getch();
	if (code.first == 224) // 'ð' = (char)224
		code.second = _getch();
	if (code.second == 0 && code.first != 13 &&
		code.first != 26 && code.first != 27 &&
		code.first != 8)
		cout << (char)code.first;
	while (code.first != 27) { //esc
		try {
			textEditor.makeChanges(code);
		}
		catch (out_of_range & ex) {
			cout << ex.what() << endl;
		}
		code.second = 0;
		code.first = _getch();
		if (code.first == 224) // 'ð' = (char)224
			code.second = _getch();
		if (code.second == 0 && code.first != 13 &&
			code.first != 26 && code.first != 27 &&
			code.first != 8 && code.first != 25)
			cout << (char)code.first;
	}
	return 0;
}

