#ifndef MATRIX
#define MATRIX

#include <iostream>
using namespace std;

template <typename T>
class Matrix {
	int height;
	int width;
protected:
	T * array;
	void copy(const Matrix & m);
public:
	Matrix(int height, int weight);
	Matrix(const Matrix & m);
	int getHeight()const {
		return height;
	}
	int getWidth()const {
		return width;
	}
	void makeZero();
	Matrix<T> & operator =(const Matrix<T> & m);
	Matrix<T> operator +(const Matrix<T> & m)const;
	Matrix<T> operator -(const Matrix<T> & m)const;
	Matrix<T> operator *(const Matrix<T> & m)const;
	Matrix<T> operator *(T a)const;
	Matrix<T> & operator +=(const Matrix<T> & m);
	Matrix<T> & operator -=(const Matrix<T> & m);
	Matrix<T> & operator *=(T a);
	Matrix<T> & operator *=(const Matrix<T> & m);
	T operator ()(int i, int j)const;
	T & operator ()(int i, int j);
	~Matrix();
	Matrix<T> & transpose();
	friend ostream & operator<<(ostream & os, const Matrix<T> & m);
};

template <typename T>
Matrix<T>::Matrix(int height = 0, int width = 0) : height(height), width(width) {
	array = new T[height * width];
	for (int i = 0; i < height * width; ++i)
		array[i] = 0;
}

template <typename T>
void Matrix<T>::copy(const Matrix & m) {
	this->height = m.height;
	this->width = m.width;
	for (int i = 0; i < height * width; ++i) {
		this->array[i] = m.array[i];
	}
}

template <typename T>
Matrix<T>::Matrix(const Matrix & m) {
	this->array = new T[m.height * m.width];
	copy(m);
}

template <typename T>
Matrix<T> & Matrix<T>::operator=(const Matrix<T> & m) {
	if (this != &m) {
		T * ptr = new T[m.height * m.width];
		delete[] array;
		this->array = ptr;
		copy(m);
	}
	return *this;
}

template <typename T>
Matrix<T>::~Matrix() {
	delete[] array;
}

template <typename T>
T Matrix<T>::operator()(int i, int j)const {
	if (i >= height || j >= width)
		throw out_of_range("Wrong indices");
	return *(array + i * width + j);
}

template <typename T>
T & Matrix<T>:: operator()(int i, int j) {
	if (i >= height || j >= width)
		throw out_of_range("Wrong indices");
	return *(array + i * width + j);
}

template <typename T>
void Matrix<T>::makeZero() {
	for (int i = 0; i < height; ++i)
		for (int j = 0; j < width; ++j)
			(*this)(i, j) = 0;
}

template <typename T>
ostream & operator<<(ostream & os, const Matrix<T> & m) {
	char old = cout.fill(' ');
	for (int i = 0; i < m.height; ++i) {
		for (int j = 0; j < m.width; ++j)
			os << setw(4) << m(i, j);
		os << endl;
	}
	os << old;
	return os;
}

template <typename T>
Matrix<T> Matrix<T>::operator +(const Matrix<T> & m)const {
	if (this->height != m.height || this->width != m.width)
		throw exception("It is impossible to find the sum of matrices");
	Matrix<T> sum(height, width);
	for (int i = 0; i < height; ++i)
		for (int j = 0; j < width; ++j)
			sum(i, j) = (*this)(i, j) + m(i, j);
	return sum;
}

template <typename T>
Matrix<T> Matrix<T>::operator -(const Matrix<T>& m)const {
	if (this->height != m.height || this->width != m.width)
		throw exception("It is impossible to find the difference between matrices");
	Matrix<T> difference(height, width);
	for (int i = 0; i < height; ++i)
		for (int j = 0; j < width; ++j)
			difference(i, j) = (*this)(i, j) - m(i, j);
	return difference;
}

template <typename T>
Matrix<T> Matrix<T>::operator *(T a)const {
	Matrix<T> newMatrix(height, width);
	for (int i = 0; i < height; ++i)
		for (int j = 0; j < width; ++j)
			newMatrix(i, j) = (*this)(i, j) * a;
	return newMatrix;
}

template <typename T>
Matrix<T> Matrix<T>::operator *(const Matrix<T> & m)const {
	if (this->width != m.height)
		throw exception("It is impossible to find multiplication of matrices");
	Matrix<T> multiplication(this->height, m.width);
	multiplication.makeZero();
	for (int i = 0; i < this->height; ++i)
		for (int j = 0; j < m.width; ++j)
			for (int k = 0; k < this->width; ++k)
				multiplication(i, j) += (*this)(i, k) * m(k, j);
	return multiplication;
}

template <typename T>
Matrix<T> & Matrix<T>::operator +=(const Matrix<T> & m) {
	(*this) = (*this) + m;
	return *this;
}

template <typename T>
Matrix<T> & Matrix<T>::operator -=(const Matrix<T> & m) {
	(*this) = (*this) - m;
	return *this;
}

template <typename T>
Matrix<T> & Matrix<T>::operator *=(T a) {
	(*this) = (*this) * a;
	return *this;
}

template <typename T>
Matrix<T> & Matrix<T>::operator *=(const Matrix<T> & m) {
	(*this) = (*this) * m;
	return *this;
}

template <typename T>
Matrix<T> & Matrix<T>::transpose() {
	Matrix<T> transposedMatrix(width, height);
	for (int i = 0; i < transposedMatrix.getHeight(); ++i)
		for (int j = 0; j < transposedMatrix.getWidth(); ++j)
			transposedMatrix(i, j) = (*this)(j, i);
	(*this) = transposedMatrix;
	return *this;
}

#endif MATRIX