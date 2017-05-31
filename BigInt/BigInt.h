#ifndef BIG_INT
#define BIG_INT
#include <iostream>
using namespace std;

typedef unsigned int base_t;
typedef unsigned long int number_t;//тип, содержащий квадрат base_t

class BigInt {
	static const base_t BASE = 10000;
	static const int MAX_LENGTH = 200;
	base_t buf[MAX_LENGTH];
	int maxIndex;
	bool isNegative;
	void levelUp();
	BigInt(const base_t *buf, int maxIndex, bool isNegative);
	void setUnsignedNumber(unsigned long long int number);
	void setNumber(long long int number);
	void setBufSumOfAbs(const BigInt& a, const BigInt& b);
	void setBufDifferenceOfAbs(const BigInt& a, const BigInt& b);
	void setBufQuotientOfAbs(const BigInt& a, const BigInt& b);
	base_t & operator [](int i) {
		return  buf[i];
	}
public:
	BigInt(unsigned long long int number);
	BigInt(long long int number = 0);
	BigInt(unsigned int number);
	BigInt(int number);
	BigInt(const char* string);
	static base_t getBASE() {
		return BASE;
	}
	static int getMAX_LENGTH() {
		return MAX_LENGTH;
	}
	static int findDegreeOfBASE();
	int getMaxIndex()const {
		return maxIndex;
	}
	BigInt & operator +=(const BigInt& a);
	BigInt & operator -=(const BigInt& a);
	BigInt & operator *=(const BigInt& a);
	BigInt & operator /=(const BigInt& a);
	BigInt & operator %=(const BigInt& a);
	BigInt & operator %=(base_t a); // a < BASE
	base_t operator[](int i)const {
		return  buf[i];
	}
	BigInt findAbs()const;
	friend BigInt operator -(const BigInt& a);
	friend BigInt operator +(const BigInt& a);
	friend BigInt operator +(const BigInt& a, const BigInt& b);
	friend BigInt operator -(const BigInt& a, const BigInt& b);//работает, когда a > b
	friend BigInt operator *(const BigInt& a, const BigInt& b);
	friend BigInt operator *(const BigInt& a, base_t b); // b < BASE
	friend BigInt operator /(const BigInt& a, const BigInt& b);
	friend BigInt operator /(const BigInt& a, base_t b);// b < BASE
	friend BigInt operator %(const BigInt& a, const BigInt& b);
	friend BigInt operator %(const BigInt& a, base_t b);//b < BASE
	friend bool operator <(const BigInt& a, const BigInt& b);
	friend bool operator <=(const BigInt& a, const BigInt& b);
	friend bool operator >(const BigInt& a, const BigInt& b);
	friend bool operator >=(const BigInt& a, const BigInt& b);
	friend bool operator ==(const BigInt& a, const BigInt& b);
	friend bool operator !=(const BigInt&a, const BigInt& b);
	friend ostream & operator<<(ostream & os, const BigInt& b);
};

BigInt findGreatestCommonDivisor(BigInt number1, BigInt number2);

#endif
