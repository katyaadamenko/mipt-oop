#include <iostream>
#include <assert.h>
#include "Matrix.h"
#include <stdlib.h>

int main() {
	Matrix matrix(4);
	matrix.makeZero();
	cout << matrix << endl;
	Matrix matrix1(4);
	for (int i = 0; i < matrix1.getSize(); ++i)
		for (int j = 0; j < matrix1.getSize(); ++j) {
			matrix1(i, j) = 5;
			matrix(i, j) = i + j;
		}
	Matrix m(4);
	m = matrix + matrix1;
	cout << "Matrix1:" << endl << matrix1 << endl << "Matrix:" << endl << matrix << endl << "Matrix1 + Matrix:" << endl << m << endl << "Matrix1 - Matrix:"<< endl << matrix1 - matrix <<
		endl << "Matrix * 0.5:" << endl << matrix * 0.5 << endl;
	Matrix matrix2(3);
	Matrix matrix3(matrix2.getSize());
	for (int i = 0; i < matrix2.getSize(); ++i)
		for (int j = 0; j < matrix2.getSize(); ++j)
			matrix2(i, j) = 1;
	for (int i = 0; i < matrix3.getSize(); ++i)
		for (int j = 0; j < matrix3.getSize(); ++j)
			matrix3(i, j) = i + j;
	cout << "Matrix2:" << endl << matrix2 << endl << "Matrix3:" << endl << matrix3 << endl << "Matrix2 * Matrix3:" << endl << matrix2 * matrix3 << endl;
	Matrix matrix4(4);
	cout << "Matrix3:" << endl << matrix3 << endl << "Transposed matrix3:" << endl << matrix3.transpose() << endl;
	Matrix sqMatrix1(3);
	for (int i = 0; i < sqMatrix1.getSize(); ++i)
		for (int j = 0; j < sqMatrix1.getSize(); ++j)
			sqMatrix1(i, j) = i + j;
	cout << "sqMatrix1:" << endl << sqMatrix1 << endl;
	cout << "sqMatrix1.findMinor(0, 0):" << endl << sqMatrix1.findMinor(0, 0) << endl;
	cout << "sqMatrix1.findDet():" << endl << sqMatrix1.findDet() << endl;
	Matrix sqMatrix2(2);
	sqMatrix2(0, 0) = 2;
	sqMatrix2(0, 1) = 2;
	sqMatrix2(1, 0) = 2;
	sqMatrix2(1, 1) = 0;
	cout << "sqMatrix2:" << endl << sqMatrix2 << endl;
	cout << "sqMatrix2.inverseMatrix()" << endl << sqMatrix2.inverseMatrix() << endl;
	cout << "Trace of sqMatrix2:" << endl << sqMatrix2.findTrace() << endl;
	Matrix sqMatrix3(3);
	sqMatrix3(0, 0) = 1;
	sqMatrix3(0, 1) = -3;
	sqMatrix3(0, 2) = -1;
	sqMatrix3(1, 0) = -2;
	sqMatrix3(1, 1) = 7;
	sqMatrix3(1, 2) = 2;
	sqMatrix3(2, 0) = 3;
	sqMatrix3(2, 1) = 2;
	sqMatrix3(2, 2) = -4;
	cout << "sqMatrix3:" << endl << sqMatrix3 << endl;
	cout << "sqMatrix3.findDet()" << endl << sqMatrix3.findDet() << endl;
	sqMatrix1 = sqMatrix3;
	cout << "sqMatrix1:" << sqMatrix1 << endl;
	sqMatrix1 += sqMatrix3;
	cout << "sqMatrix1 += sqMatrix3, sqMatrix1:" << endl;
	cout << sqMatrix1 << endl;
	cout << "sqMatrix1.findDet():"  << sqMatrix1.findDet() << endl;
	sqMatrix1.changeLines(0, 1);
	cout << "sqMatrix1:" << endl << sqMatrix1 << endl;
	cout << "sqMatrix1.findDet():" << endl << sqMatrix1.findDet() << endl;
	sqMatrix3(0, 0) = 0;
	cout << sqMatrix3.findDet() << endl;
	cout << "sqMatrix3:" << endl << sqMatrix3 << endl;
	cout << "sqMatrix3 ^ 0:" << endl << (sqMatrix3 ^ 0) << endl;
	cout << "sqMatrix3 ^ 1:" << endl <<(sqMatrix3 ^ 1) << endl;
	cout << "sqMatrix3 ^ 2:" << endl <<(sqMatrix3 ^ 2) << endl;

	char c;
	cin >> c;
	return 0;
}