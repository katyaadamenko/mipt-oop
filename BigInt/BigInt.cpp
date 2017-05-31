#include "BigInt.h"
#include <cstring>
#include <algorithm>
#include <iomanip>
#include <assert.h>
using namespace std;

int BigInt::findDegreeOfBASE() {
	int base = BASE;
	int degreeOfBase = 0;
	while (base != 1) {
		base /= 10;
		++degreeOfBase;
	}
	return degreeOfBase;
}

void BigInt::setUnsignedNumber(unsigned long long int number) {
	isNegative = false;
	bool numberIsSet = false;
	for (int i = 0; i < MAX_LENGTH; ++i) {
		if (numberIsSet) {
			buf[i] = 0;
			continue;
		}
		buf[i] = number % BASE;
		number /= BASE;
		if (!number && !numberIsSet) {
			numberIsSet = true;
			maxIndex = i;
		}
	}
}

void BigInt::setNumber(long long int number) {
	if (number < 0) {
		isNegative = true;
		number *= -1;
	}
	else
		isNegative = false;
	bool numberIsSet = false;
	for (int i = 0; i < MAX_LENGTH; ++i) {
		if (numberIsSet) {
			buf[i] = 0;
			continue;
		}
		buf[i] = number % BASE;
		number /= BASE;
		if (!number && !numberIsSet) {
			numberIsSet = true;
			maxIndex = i;
		}
	}
}

BigInt::BigInt(long long int number) {
	setNumber(number);
}

BigInt::BigInt(unsigned long long int number) {
	setUnsignedNumber(number);
}

BigInt::BigInt(unsigned int number) {
	setUnsignedNumber(number);
}

BigInt::BigInt(int number) {
	setNumber(number);
}


BigInt::BigInt(const char* string) {
	int degreeOfBase = findDegreeOfBASE();
	int lengthOfString = strlen(string);
	if (string[0] == '-') {
		isNegative = true;
		--lengthOfString;
	}
	else
		isNegative = false;
	if (lengthOfString % degreeOfBase != 0)
		maxIndex = lengthOfString / degreeOfBase;
	else
		maxIndex = lengthOfString / degreeOfBase - 1;
	int numberOfElement;
	int i;
	if (isNegative)
		numberOfElement = lengthOfString;
	else
		numberOfElement = lengthOfString - 1;
		i = 0;
	for (int i = 0; i < MAX_LENGTH; ++i) {
		int multiplier = 1;
		buf[i] = 0;
		if (i <= maxIndex) {
			for (int k = 0; k < degreeOfBase && (numberOfElement >= 0 && !isNegative || numberOfElement > 0 && isNegative); ++k) {
				buf[i] += ((int)string[numberOfElement] - (int)'0') * multiplier;
				--numberOfElement;
				multiplier *= 10;
			}
		}
	}
}

BigInt::BigInt(const base_t *buf, int maxIndex, bool isNegative) {
	this->maxIndex = maxIndex;
	this->isNegative = isNegative;
	bool isCorrect = true;
	for (int i = 0; i <= maxIndex; ++i)
		if (buf[i] >= getBASE()) {
			cerr << "Wrong buffer!" << endl;
			isCorrect = false;
		}
	for (int i = 0; i < MAX_LENGTH && isCorrect; ++i)
		this->buf[i] = buf[i];
}

BigInt operator+(const BigInt& a) {
	return a;
}

BigInt operator-(const BigInt& a) {
	BigInt b(a);
	b.isNegative = !a.isNegative;
	return b;
}

BigInt BigInt::findAbs()const {
	return isNegative ? -(*this) : *this;
}

ostream & operator<<(ostream & os, const BigInt & b) {
	int base = b.BASE;
	if (b.isNegative)
		os << '-';
	os << b[b.maxIndex];
	int degreeOfBase = b.findDegreeOfBASE();
	for (int i = b.maxIndex - 1; i >= 0; --i) {
		os << setw(degreeOfBase) << setfill('0') << b[i];
	}
	return os;
}

void BigInt::setBufSumOfAbs(const BigInt& a, const BigInt & b) {
	base_t carry = 0;
	number_t value;
	int maxOfIndices = max(a.maxIndex, b.maxIndex);
	for (int i = 0; i <= maxOfIndices || carry; ++i) {
		value = a[i] + b[i] + carry;
		carry = value >= a.BASE;
		if (carry)
			(*this)[i] = value - a.BASE;
		else
			(*this)[i] = value;
		if ((*this)[i] != 0)
			this->maxIndex = i;
	}
	return;
}

void BigInt::setBufDifferenceOfAbs(const BigInt& a, const BigInt& b) {
	base_t carry = 0;
	for (int i = 0; i <= a.maxIndex; ++i) {
		if (a[i] >= (b[i] + carry)) {
			(*this)[i] = a[i] - b[i] - carry;
			carry = 0;
		}
		else {
			(*this)[i] = a[i] - b[i] - carry + a.BASE;
			carry = 1;
		}
		if ((*this)[i] != 0)
			this->maxIndex = i;
	}
	return;
}

BigInt operator+(const BigInt & a, const BigInt & b) {
	BigInt sum;
	if (a.isNegative) {
		if (b.isNegative) {
			sum.isNegative = true;
			sum.setBufSumOfAbs(a, b);
		}
		else if (-a > b) {
			sum.isNegative = true;
			sum.setBufDifferenceOfAbs(a, b);
		}
		else {
			sum.isNegative = false;
			sum.setBufDifferenceOfAbs(b, a);
		}
	}
	else if (!b.isNegative) {
		sum.isNegative = false;
		sum.setBufSumOfAbs(a, b);
	}
	else if (-b > a) {
		sum.isNegative = true;
		sum.setBufDifferenceOfAbs(b, a);
	}
	else {
		sum.isNegative = false;
		sum.setBufDifferenceOfAbs(a, b);
	}
	return sum;
}

BigInt operator-(const BigInt & a, const BigInt & b) {
	return a + (-b);
}

BigInt & BigInt:: operator+=(const BigInt & a) {
	*this = (*this) + a;
	return *this;
}

BigInt & BigInt:: operator-=(const BigInt & a) {
	*this = (*this) - a;
	return *this;
}

bool operator <(const BigInt& a, const BigInt& b) {
	if (!a.isNegative && b.isNegative)
		return false;
	else if (a.isNegative && !b.isNegative)
		return true;
	bool isAbsLess;
	bool isAbsEqual = true;
	if (a.maxIndex > b.maxIndex)
		isAbsLess = false;
	else if (a.maxIndex < b.maxIndex) {
		isAbsEqual = false;
		isAbsLess = true;
	}
	else {
		for (int i = b.maxIndex; i >= 0; --i) {
			if (a[i] > b[i]) {
				isAbsLess = false;
				isAbsEqual = false;
				break;
			}
			else if (a[i] < b[i]) {
				isAbsLess = true;
				isAbsEqual = false;
				break;
			}
		}
	}
	if (a.isNegative)
		return !isAbsEqual && !isAbsLess;
	else
		return !isAbsEqual && isAbsLess;
}

bool operator ==(const BigInt& a, const BigInt& b) {
	if (a.maxIndex != b.maxIndex || (a.isNegative + b.isNegative == 1))
		return false;
	bool isEqual = true;
	for (int i = 0; i <= a.maxIndex; ++i) {
		if (a[i] != b[i]) {
			isEqual = false;
			break;
		}
	}
	return isEqual;
}

bool operator >(const BigInt& a, const BigInt& b) {
	return b < a;
}

bool operator <=(const BigInt& a, const BigInt& b){
	return !(b < a);
}

bool operator >=(const BigInt& a, const BigInt& b) {
	return !(a < b);
}

bool operator !=(const BigInt&a, const BigInt& b) {
	return !(a == b);
}

BigInt operator *(const BigInt& a, base_t b) {
	BigInt multiplication;
	if (a == 0)
		return a;
	else if (b == 0) {
		return multiplication;
	}
	if (a.isNegative && b > 0 || !a.isNegative && b < 0)
		multiplication.isNegative = true;
	base_t carry = 0;
	number_t value;
	for (int i = 0; i <= a.maxIndex || carry; ++i) {
		value = a[i] * b + carry;
		carry = value / a.BASE;
		multiplication[i] = value % a.BASE;//multiplication.setBufI(i, value % a.BASE);
		if (multiplication[i] != 0)
			multiplication.maxIndex = i;
	}
	return multiplication;
}


BigInt operator *(const BigInt& a, const BigInt& b) {
	if (a == 0)
		return a;
	else if (b == 0)
		return b;
	BigInt multiplication;
	multiplication.isNegative = (a.isNegative + b.isNegative == 1);
	base_t carry;
	number_t value;
	for (int i = 0; i <= b.maxIndex; ++i) {
		carry = 0;
		for (int j = 0; j <= a.maxIndex || carry; ++j) {
			value = multiplication[i + j] + b[i] * a[j] + carry;
			carry = value / a.BASE;
			if (carry)
				multiplication[i + j] = value % a.BASE; //multiplication.setBufI(i + j, value %= a.BASE);
			else
				multiplication[i + j] = value; //multiplication.setBufI(i + j, value);
			if (multiplication[i + j] != 0 && (i + j) > multiplication.maxIndex)
				multiplication.maxIndex = i + j;
		}
	}
	return multiplication;
}

void BigInt::levelUp() {
	if (maxIndex == MAX_LENGTH - 1) {
		cerr << "Impossible1";
		return;
	}
	for (int i = maxIndex; i >= 0; --i)
		buf[i + 1] = buf[i];//setBufI(i + 1, buf[i]);
	buf[0] = 0;//setBufI(0, 0);
	if (buf[maxIndex + 1] != 0)
		++maxIndex;
}

void BigInt::setBufQuotientOfAbs(const BigInt& a, const BigInt& b) {
	BigInt residue;
	base_t divider = 0;
	base_t medium;
	base_t leftBorder;
	base_t rightBorder;
	bool findMaxIndex = false;
	for (int i = a.maxIndex; i >= 0; --i) {
		residue.levelUp();
		residue[0] = a[i];
		leftBorder = 0;
		rightBorder = a.BASE - 1;
		BigInt multiplication;
		while (leftBorder <= rightBorder) {
			medium = leftBorder + (rightBorder - leftBorder) / 2;
			multiplication = b * medium;
			if (multiplication == residue) {
				divider = medium;
				break;
			}
			else if (multiplication < residue) {
				divider = medium;
				leftBorder = medium + 1;
			}
			else
				rightBorder = medium - 1;
			if (leftBorder == 0 && rightBorder == 0) {
				divider = 0;
				break;
			}
		}
		(*this)[i] = divider;//quotient.setBufI(i, divider);
		residue -= divider * b;
		if ((*this)[i] != 0 && !findMaxIndex) {
			(*this).maxIndex = i;
			findMaxIndex = true;
		}
	}
	return;
}

BigInt operator/(const BigInt& a, const BigInt& b) {
	assert(b != 0);
	if (a == 0)
		return a;
	BigInt quotient;
	quotient.isNegative = (a.isNegative + b.isNegative == 1);
	quotient.setBufQuotientOfAbs(a.findAbs(), b.findAbs());
	return quotient;
}

BigInt operator %(const BigInt& a, const BigInt& b) {
	return (a - (a / b) * b);
}

BigInt & BigInt:: operator *=(const BigInt& a) {
	*this = (*this) * a;
	return *this;
}

BigInt & BigInt:: operator /=(const BigInt& a) {
	*this = (*this) / a;
	return *this;
}

BigInt & BigInt:: operator %=(const BigInt& a) {
	*this = (*this) % a;
	return *this;
}

BigInt findGreatestCommonDivisor(BigInt number1, BigInt number2) {
	assert(number1 > 0 && number2 > 0);
	while (number1 != 0 && number2 != 0) {
		if (number1 >= number2)
			number1 %= number2;
		else
			number2 %= number1;
	}
	return number1 + number2;
}

BigInt operator/(const BigInt& a, base_t b) {
	assert(b != '0');
	if (a == '0')
		return a;
	BigInt quotient;
	number_t residue = 0;
	bool findMaxIndex = false;
	for (int i = a.maxIndex; i >= 0; --i) {
		residue += a[i];
		quotient[i] = residue / b;//quotient.setBufI(i, residue / b);
		residue = (residue % b) * a.BASE;
		if (quotient[i] != 0 && !findMaxIndex) {
			quotient.maxIndex = i;
			findMaxIndex = true;
		}
	}
	return quotient;
}

BigInt operator%(const BigInt& a, base_t b) {
	return a - (a / b) * b;
}

BigInt & BigInt:: operator%=(base_t b) {
	*this = (*this) % b;
	return *this;
}

