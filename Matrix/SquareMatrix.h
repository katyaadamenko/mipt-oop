#ifndef SQUARE_MATRIX
#define SQUARE_MATRIX

#include "Matrix.h"

template <typename T>
class SquareMatrix : public Matrix<T> {
public:
	SquareMatrix(int size) : Matrix(size, size) {}
	SquareMatrix(const SquareMatrix<T>& m) : Matrix(m){}
	~SquareMatrix(){}
	SquareMatrix<T> & operator =(const SquareMatrix<T> & m);
	void makeIdentity();
	T findTrace()const;
	SquareMatrix<T> findMinor(int i, int j)const;
	SquareMatrix<T> & reverseMatrix();//?
	double findDet()const;
	SquareMatrix<T> & changeLines(int line1, int line2);
	SquareMatrix<T> operator ^(int n)const;
};

template <typename T>
SquareMatrix<T> & SquareMatrix<T>::operator =(const SquareMatrix<T> & m) {
	if (this != &m){
		double * ptr = new T[m.getHeight() * m.getWidth()];
		delete[] array;
		this->array = ptr;
		copy(m);
	}
	return *this;
}

template <typename T>
void SquareMatrix<T>::makeIdentity() {
	for (int i = 0; i < this->getHeight(); ++i)
		for (int j = 0; j < this->getWidth(); ++j)
			if (i == j)
				(*this)(i, j) = 1;
			else
				(*this)(i, j) = 0;
	return;
}

template <typename T>
T SquareMatrix<T>::findTrace()const {
	T trace = 0;
	for (int i = 0; i < this->getHeight(); ++i)
		trace += (*this)(i, i);
	return trace;
}

template <typename T>
SquareMatrix<T> SquareMatrix<T>::findMinor(int i, int j)const {
	SquareMatrix<T> minor(this->getHeight() - 1);
	int lineMinor = 0;
	for (int line = 0; line < this->getHeight(); ++line) {
		int columnMinor = 0;
		if (line == i)
			continue;
		for (int column = 0; column < this->getHeight(); ++column) {
			if (column == j)
				continue;
			minor(lineMinor, columnMinor) = (*this)(line, column);
			++columnMinor;
		}
		++lineMinor;
	}
	return minor;
}

template <typename T>
double SquareMatrix<T>::findDet()const {
	double det = 1;
	SquareMatrix<T> matrix(*this);
	for (int j = 0; j < matrix.getHeight(); ++j) {
		if (matrix(j, j) == 0) {
			for (int k = j + 1; k < matrix.getHeight(); ++k)
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
		for (int k = matrix.getHeight() - 1; k >= j; --k) {
			matrix(j, k) /= divider;
		}
		for (int i = j + 1; i < matrix.getHeight(); ++i) {
			double multiplier = matrix(i, j);
			for (int k = matrix.getHeight() - 1; k >= j; --k) {
				matrix(i, k) -= multiplier * matrix(j, k);
			}
		}
	}
	for (int i = 0; i < matrix.getHeight(); ++i)
		det *= matrix(i, i);
	return det;
}

template <typename T>
SquareMatrix<T> & SquareMatrix<T>::changeLines(int line1, int line2) {
	if (line1 >= getHeight() || line2 >= getHeight())
		throw exception("Wrong number of line");
	for (int j = 0; j < this->getHeight(); ++j)
		swap((*this)(line1, j), (*this)(line2, j));
	return *this;
}

template <typename T>
SquareMatrix<T> & SquareMatrix<T>::reverseMatrix() {
	if (findDet() == 0)
		throw exception("It is impossible to find inverse matrix, det = 0");
	SquareMatrix<T> inverseMatrix(this->getHeight());
	inverseMatrix.makeIdentity();
	for (int j = 0; j < this->getHeight(); ++j) {
		if ((*this)(j, j) == 0) {								//перестановка
			for (int k = j + 1; k < this->getHeight(); ++k)
				if ((*this)(k, j) != 0) {
					this->changeLines(k, j);
					inverseMatrix.changeLines(k, j);
					break;
				}
		}
		double divider = (*this)(j, j);
		for (int k = this->getHeight() - 1; k >= 0; --k) {		//единица в выбранной клетке
			inverseMatrix(j, k) /= divider;
			(*this)(j, k) /= divider;
		}
		for (int i = 0; i < this->getHeight(); ++i) {			//вычитание строк
			if (i == j)
				continue;
			double multiplier = (*this)(i, j);
			for (int k = this->getHeight() - 1; k >= 0; --k) {
				(*this)(i, k) -= multiplier * (*this)(j, k);
				inverseMatrix(i, k) -= multiplier * inverseMatrix(j, k);
			}
		}
	}
	(*this) = inverseMatrix;
	return *this;
}

template <typename T>
SquareMatrix<T> SquareMatrix<T>:: operator ^(int n)const {
	if (n < 0)
		throw out_of_range("It is impossible to find negative power of matrix");
	SquareMatrix<T> multiplication(this->getHeight());
	multiplication.makeIdentity();
	for (int i = 0; i < n; ++i)
		multiplication *= (*this);
	return multiplication;
}

#endif
