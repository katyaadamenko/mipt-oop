#include <algorithm>
#include "Fraction.h"
#include "math.h"

int foundGreatestCommonDivisor(int number1, int number2) {
	while (number1 != 0 && number2 != 0) {
		if (number1 >= number2)
			number1 %= number2;
		else
			number2 %= number1;
	}
	return number1 + number2;
}

double roundFraction(double & fraction) {
	fraction *= 1000000;
	if ((int)fraction % 10 >= 5)
		fraction = (int)fraction / 10 + 1;
	else
		fraction = (int)fraction / 10;
	fraction /= 100000;
	return fraction;
}

void Fraction::reduceFraction() {
	int GCD = foundGreatestCommonDivisor(abs(numerator), denominator);
	numerator /= GCD;
	denominator /= GCD;
}

Fraction::Fraction(int newNumerator, int newDenominator) {
	if (newDenominator == 0)
		cerr << "Wrong denominator!" << endl;
	else {
		if (newDenominator < 0) {
			newNumerator *= -1;
			newDenominator *= -1;
		}
		denominator = newDenominator;
		numerator = newNumerator;
	}
	reduceFraction();
}

Fraction::Fraction(double fraction) {
	roundFraction(fraction);
	numerator = (int)(fraction * 100000);
	denominator = 100000;
	reduceFraction();
}

Fraction::operator double() {
	return (double)numerator / denominator;
}

Fraction::Fraction(const Fraction & fr1) {
	this->numerator = fr1.numerator;
	this->denominator = fr1.denominator;
}

Fraction Fraction::operator-() {
	Fraction fr(-numerator, denominator);
	return fr;
}

Fraction Fraction::operator+() {
	Fraction fr = *this;
	return fr;
}

Fraction operator+(const Fraction & fr1, const Fraction & fr2) {
	Fraction fr(fr1.getNumerator() * fr2.getDenominator() + 
				fr2.getNumerator() * fr1.getDenominator(),
				fr1.getDenominator() * fr2.getDenominator());
	return fr;
}

Fraction operator-(const Fraction & fr1, const Fraction & fr2) {
	Fraction fr(fr1.getNumerator() * fr2.getDenominator() - 
				fr2.getNumerator() * fr1.getDenominator(),
				fr1.getDenominator() * fr2.getDenominator());
	return fr;
}

Fraction operator*(const Fraction & fr1,const Fraction & fr2) {
	Fraction fr(fr1.getNumerator() * fr2.getNumerator(),
				fr1.getDenominator() * fr2.getDenominator());
	return fr;
}

Fraction operator/(const Fraction & fr1, const Fraction & fr2) {
	Fraction fr(fr1.getNumerator() * fr2.getDenominator(),
				fr1.getDenominator() * fr2.getNumerator());
	return fr;
}

Fraction & Fraction::operator+=(const Fraction & fr1) {
	(*this) = (*this) + fr1;
	return *this;
}

Fraction & Fraction::operator-=(const Fraction & fr1) {
	(*this) = (*this) - fr1;
	return *this;
}

Fraction & Fraction::operator*=(const Fraction & fr1) {
	(*this) = (*this) * fr1;
	return *this;
}

Fraction & Fraction::operator/=(const Fraction & fr1) {
	(*this) = (*this) / fr1;
	return *this;
}

Fraction & Fraction::operator++() {
	this->numerator += this->denominator;
	return *this;
}

Fraction Fraction::operator++(int) {
	Fraction oldValue = *this;
	++(*this);
	return oldValue;
}

Fraction & Fraction::operator--() {
	this->numerator -= this -> denominator;
	return *this;
}

Fraction Fraction::operator--(int) {
	Fraction oldValue = *this;
	--(*this);
	return oldValue;
}

bool operator==(const Fraction & fr1, const Fraction & fr2) {
	return fr1.getNumerator() == fr2.getNumerator() &&
		fr1.getDenominator() == fr2.getDenominator();
}

bool operator!=(const Fraction & fr1, const Fraction & fr2) {
	return fr1.getNumerator() != fr2.getNumerator() ||
		fr1.getDenominator() != fr2.getDenominator();
}

bool operator>(const Fraction & fr1, const Fraction & fr2) {
	return fr1.getNumerator() * fr2.getDenominator() >
		fr1.getDenominator() * fr2.getNumerator();
}

bool operator>=(const Fraction & fr1, const Fraction & fr2) {
	return fr1.getNumerator() * fr2.getDenominator() >=
		fr1.getDenominator() * fr2.getNumerator();
}

bool operator<(const Fraction &fr1, const Fraction &fr2) {
	return fr2 > fr1;
}

bool operator<=(const Fraction &fr1, const Fraction &fr2) {
	return fr2 >= fr1;
}

ostream & operator<<(ostream &os, Fraction &fr) {
	int integerPart;
	integerPart = fr.getNumerator() / fr.getDenominator();
	if (fr.getDenominator() == 1)
		os << integerPart;
	else if (integerPart >= 1)
		os << integerPart << ' ' << fr.getNumerator() - integerPart * fr.getDenominator() << '/' << fr.getDenominator();
	else if (integerPart <= -1)
		os << integerPart << ' ' << integerPart * fr.getDenominator() - fr.getNumerator() << '/' << fr.getDenominator();
	else
		os << fr.getNumerator() << '/' << fr.getDenominator();
	return os;
}

