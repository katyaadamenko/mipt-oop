#ifndef MATRIX
#define MATRIX

#include <iostream>
using namespace std;

class Matrix {
	int size;
	double *array;
	void copy(const Matrix& m);
public:
	Matrix(int size);
	Matrix(const Matrix& m);
	int getSize()const {
		return size;
	}
	void makeZero();
	Matrix & operator =(const Matrix& m);
	Matrix operator +(const Matrix& m)const;
	Matrix operator -(const Matrix& m)const;
	Matrix operator *(const Matrix& m)const;
	Matrix operator *(double a)const;
	Matrix & operator +=(const Matrix& m);
	Matrix & operator -=(const Matrix& m);
	Matrix & operator *=(double a);
	Matrix & operator *=(const Matrix& m);
	Matrix operator ^(int n)const;
	double operator ()(int i, int j)const;
	double & operator ()(int i, int j);
	~Matrix();
	Matrix & transpose();
	friend ostream & operator<<(ostream & os, const Matrix& m);
	void makeIdentity();
	double findTrace()const;
	Matrix findMinor(int i, int j)const;
	Matrix & inverseMatrix();
	double findDet()const;
	Matrix & changeLines(int line1, int line2);
};

#endif MATRIX