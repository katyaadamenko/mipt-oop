#include "Matrix.h"
#include <assert.h>
#include <iomanip>

Matrix::Matrix(int size = 0) : size(size) {
	array = new double[size * size];
	for (int i = 0; i < size * size; ++i)
		array[i] = 0;
}

void Matrix::copy(const Matrix& m) {
	this->size = m.size;
	this->array = new double[size * size];
	for (int i = 0; i < size * size; ++i) {
		this->array[i] = m.array[i];
	}
}

Matrix::Matrix(const Matrix& m) {
	copy(m);
}

Matrix & Matrix::operator=(const Matrix& m) {
	if (this != &m) {
		delete[] array;
		copy(m);
	}
	return *this;
}

Matrix::~Matrix() {
	delete[] array;
}

double Matrix::operator()(int i, int j)const {
	assert(i < size && j < size);
	return *(array + i * size + j);
}

double & Matrix:: operator()(int i, int j) {
	assert(i < size && j < size);
	return *(array + i * size + j);
}

void Matrix::makeZero() {
	for (int i = 0; i < size; ++i)
		for (int j = 0; j < size; ++j)
			(*this)(i, j) = 0;
}

ostream & operator<<(ostream & os, const Matrix& m) {
	char old = cout.fill(' ');
	for (int i = 0; i < m.size; ++i) {
		for (int j = 0; j < m.size; ++j)
			os << setw(4) << m(i, j);
		os << endl;
	}
	os << old;
	return os;
}

Matrix Matrix::operator +(const Matrix& m)const {
	assert(this->size == m.size);
	Matrix sum(size);
	for (int i = 0; i < size; ++i)
		for (int j = 0; j < size; ++j)
			sum(i, j) = (*this)(i, j) + m(i, j);
	return sum;
}

Matrix Matrix::operator -(const Matrix& m)const {
	assert(this->size == m.size);
	Matrix difference(size);
	for (int i = 0; i < size; ++i)
		for (int j = 0; j < size; ++j)
			difference(i, j) = (*this)(i, j) - m(i, j);
	return difference;
}

Matrix Matrix::operator *(double a)const {
	Matrix newMatrix(size);
	for (int i = 0; i < size; ++i)
		for (int j = 0; j < size; ++j)
			newMatrix(i, j) = (*this)(i, j) * a;
	return newMatrix;
}

Matrix Matrix::operator *(const Matrix& m)const {
	assert(this->size == m.size);
	Matrix multiplication(this->size);
	multiplication.makeZero();
	for (int i = 0; i < this->size; ++i)
		for (int j = 0; j < m.size; ++j)
			for (int k = 0; k < this->size; ++k)
				multiplication(i, j) += (*this)(i, k) * m(k, j);
	return multiplication;
}

Matrix & Matrix::operator +=(const Matrix& m) {
	(*this) = (*this) + m;
	return *this;
}

Matrix & Matrix::operator -=(const Matrix& m) {
	(*this) = (*this) - m;
	return *this;
}

Matrix & Matrix::operator *=(double a) {
	(*this) = (*this) * a;
	return *this;
}

Matrix & Matrix::operator *=(const Matrix& m) {
	(*this) = (*this) * m;
	return *this;
}

Matrix & Matrix::transpose() {
	Matrix transposedMatrix(size);
	for (int i = 0; i < transposedMatrix.size; ++i)
		for (int j = 0; j < transposedMatrix.size; ++j)
			transposedMatrix(i, j) = (*this)(j, i);
	(*this) = transposedMatrix;
	return *this;
}

void Matrix::makeIdentity() {
	for (int i = 0; i < this->size; ++i)
		for (int j = 0; j < this->size; ++j)
			if (i == j)
				(*this)(i, j) = 1;
			else
				(*this)(i, j) = 0;
	return;
}

double Matrix::findTrace()const {
	double trace = 0;
	for (int i = 0; i < this->size; ++i)
		trace += (*this)(i, i);
	return trace;
}

Matrix Matrix::findMinor(int i, int j)const {
	Matrix minor(this->size - 1);
	int lineMinor = 0;
	for (int line = 0; line < this->size; ++line) {
		int columnMinor = 0;
		if (line == i)
			continue;
		for (int column = 0; column < this->size; ++column) {
			if (column == j)
				continue;
			minor(lineMinor, columnMinor) = (*this)(line, column);
			++columnMinor;
		}
		++lineMinor;
	}
	return minor;
}

double Matrix::findDet()const {
	double det = 1;
	Matrix matrix(*this);
	for (int j = 0; j < matrix.size; ++j) {
		if (matrix(j, j) == 0) {
			for (int k = j + 1; k < matrix.size; ++k)
				if (matrix(k, j) != 0) {
					matrix.changeLines(k, j);
					det *= -1;
					break;
				}
			if (matrix(j, j) == 0)
				return 0;
		}
		double divider = matrix(j, j);
		det *= divider;
		for (int k = matrix.size - 1; k >= j; --k) {
			matrix(j, k) /= divider;
		}
		for (int i = j + 1; i < matrix.size; ++i) {
			double multiplier = matrix(i, j);
			for (int k = matrix.size - 1; k >= j; --k) {
				matrix(i, k) -= multiplier * matrix(j, k);
			}
		}
	}
	for (int i = 0; i < matrix.size; ++i)
		det *= matrix(i, i);
	return det;
}

Matrix & Matrix::changeLines(int line1, int line2) {
	for (int j = 0; j < this->size; ++j)
		swap((*this)(line1, j), (*this)(line2, j));
	return *this;
}

Matrix & Matrix::inverseMatrix() {
	assert(findDet() != 0);
	Matrix inverseMatrix(this->size);
	//Matrix matrix(*this);
	inverseMatrix.makeIdentity();
	for (int j = 0; j < this->size; ++j) {
		if ((*this)(j, j) == 0) {								//перестановка
			for (int k = j + 1; k < this->size; ++k)
				if ((*this)(k, j) != 0) {
					this->changeLines(k, j);
					inverseMatrix.changeLines(k, j);
					break;
				}
		}
		double divider = (*this)(j, j);
		for (int k = this->size - 1; k >= 0; --k) {		//единица в выбранной клетке
			inverseMatrix(j, k) /= divider;
			(*this)(j, k) /= divider;
		}
		for (int i = 0; i < this->size; ++i) {			//вычитание строк
			if (i == j)
				continue;
			double multiplier = (*this)(i, j);
			for (int k = this->size - 1; k >= 0; --k) {
				(*this)(i, k) -= multiplier * (*this)(j, k);
				inverseMatrix(i, k) -= multiplier * inverseMatrix(j, k);
			}
		}
	}
	(*this) = inverseMatrix;
	return *this;
}

Matrix Matrix:: operator ^(int n)const {
	Matrix multiplication(this->size);
	multiplication.makeIdentity();
	for (int i = 0; i < n; ++i)
		multiplication *= (*this);
	return multiplication;
}