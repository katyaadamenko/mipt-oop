#ifndef FRACTION
#define FRACTION
#include <iostream>
using namespace std;

class Fraction {
	int numerator;
	int denominator;
	void reduceFraction();
public:
	Fraction(int num = 0, int den = 1);
	Fraction(double fraction);//дроби с точностью до 5 знака после запятой
	explicit operator double();
	int getNumerator()const {
		return numerator;
	}
	int getDenominator()const {
		return denominator;
	}
	Fraction(const Fraction & fr1);
	Fraction operator-();
	Fraction operator+();
	Fraction & operator+=(const Fraction & fr1);
	Fraction & operator-=(const Fraction & fr1);
	Fraction & operator*=(const Fraction & fr1);
	Fraction & operator/=(const Fraction & fr1);
	Fraction & operator++();
	Fraction operator++(int);
	Fraction & operator--();
	Fraction operator--(int);
	friend ostream & operator<<(ostream &os, const Fraction &fr);
};

ostream & operator<<(ostream &os, Fraction &fr);
Fraction operator+(const Fraction & fr1, const Fraction & fr2);
Fraction operator-(const Fraction & fr1,const Fraction & fr2);
Fraction operator*(const Fraction & fr1, const Fraction & fr2);
Fraction operator/(const Fraction & fr1, const Fraction & fr2);
bool operator==(const Fraction & fr1, const Fraction & fr2);
bool operator!=(const Fraction & fr1, const Fraction & fr2);
bool operator>(const Fraction & fr1, const Fraction & fr2);
bool operator>=(const Fraction & fr1, const Fraction & fr2);
bool operator<(const Fraction & fr1,const Fraction & fr2);
bool operator<=(const Fraction & fr1, const Fraction & fr2);

#endif