#include <iostream>
#include "Matrix.h"
#include "SquareMatrix.h"
using namespace std;

int main() {
	Matrix<double>matrix(4, 8);
	matrix.makeZero();
	double a;
	try {
		a = matrix(4, 9);
	}
	catch (out_of_range & ex) {
		cerr << "'out_of_range' " << ex.what() << endl;
	}
	Matrix<double>matrix1(3, 8);
	for (int i = 0; i < matrix.getHeight(); ++i)
		for (int j = 0; j < matrix.getWidth(); ++j) {
			if (i < 3) {
				try {
					matrix1(i, j) = 5;
				}
				catch (out_of_range & ex) {
					cerr << "'out_of_range' " << ex.what() << endl;
				}
			}
			matrix(i, j) = i + j;
		}
	try {
		matrix + matrix1;
	}
	catch (exception & ex) {
		cerr << ex.what() << endl;
	}
	try {
		matrix - matrix1;
	}
	catch (exception & ex) {
		cerr << ex.what() << endl;
	}
	try {
		matrix * matrix1;
	}
	catch (exception & ex) {
		cerr << ex.what() << endl;
	}
	cout << matrix << endl;
	try {
		matrix += matrix1;
	}
	catch (exception & ex) {
		cerr << ex.what() << endl;
	}
	cout << matrix << endl;
	try {
		matrix -= matrix1;
	}
	catch (exception & ex) {
		cerr << ex.what() << endl;
	}
	try {
		matrix *= matrix1;
	}
	catch (exception & ex) {
		cerr << ex.what() << endl;
	}
	SquareMatrix<double> matrix2(3);
	for (int i = 0; i < matrix2.getHeight(); ++i)
		for (int j = 0; j < matrix2.getHeight(); ++j)
			matrix2(i, j) = 2;
	cout << matrix2.findDet() << endl;
	try {
		matrix2.reverseMatrix();
	}
	catch (exception & ex) {
		cerr << ex.what() << endl;
	}
	try {
		matrix2 ^ (-1);
	}
	catch (exception & ex) {
		cerr << ex.what() << endl;
	}
	try {
		matrix2.changeLines(3, 1);
	}
	catch (exception & ex) {
		cerr << ex.what() << endl;
	}
	char c;
	cin >> c;
	return 0;
}