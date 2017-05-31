#include <iostream>
#include "Fraction.h"
using namespace std;

int main() {
	Fraction fraction(1.4);
	cout << fraction << endl;

	Fraction fraction1(1, 3);
	Fraction fraction2(1, 6);
	Fraction fr;
	fr = fraction1 + fraction2;
	cout << fraction1 << " + " << fraction2 << " = " << fr << endl;
	fr = fraction1 * fraction2;
	cout << fraction1 << " * " << fraction2 << " = " << fr << endl;
	cout << -fr << endl;
	cout << +fr << endl;
	fr = fraction2 - fraction1;
	cout << fraction2 << " - " << fraction1 << " = " << fr << endl;
	fr = fraction1 / fraction2;
	cout << fraction1 << " / " << fraction2 << " = " << fr << endl;

	Fraction fraction3(2);
	cout << fraction3 << endl;

	Fraction fraction4(6, 3);
	if (fraction3 == fraction4)
		cout << "yes" << endl;
	else
		cout << "no" << endl;

	Fraction g(2, -8);
	fraction4 = g;
	cout << fraction4 << " = " << (double)fraction4 << endl;
	fraction4 = fraction + (Fraction)1.5;
	cout << fraction << " + 1.5 = " <<  fraction4 << endl;

	cout << "fraction1 = " << fraction1 << endl;
	fraction1 += (Fraction)1.2;
	cout << "fraction1 += 1.2 : " << fraction1 << endl;

	cout << "fraction2 = " << fraction2 << ", fraction4 = " << fraction4 << endl;
	fraction2 -= fraction4;
	cout << "fraction2 -= fraction4 : " << fraction2 << endl;

	cout << "fraction = " << fraction << endl;
	fraction *= (Fraction)(1.0 / 2);
	cout << "fraction *= (1.0 / 2) : "<< fraction << endl;
	fraction /= fraction2;
	cout << "fraction /= fraction2 : " << fraction << endl;

	Fraction fraction5(7, 8);
	cout << fraction5 << endl;
	if (fraction5 < (Fraction)1)
		cout << fraction5 << " < 1" << endl;
	else
		cout << ":(" << endl;
	if (fraction5 > (Fraction)71.8)
		cout << ":(" << endl;
	if (fraction5 >= (Fraction)0.5) {
		fraction5++;
		cout << fraction5 << endl;
	}
	else
		cout << ":(" << endl;
	if (fraction5 <= (Fraction)(-5))
		cout << ":(" << endl;
	if (fraction5 != fraction4)
		cout << "yes" << endl;
	else
		cout << ":(" << endl;

	Fraction fraction6(1, 2);
	fr = fraction6++;
	cout << fr << endl;
	fr = ++fraction6;
	cout << fr << endl;
	cout << fraction6 << endl;
	fr = --fraction6;
	cout << fr << endl;
	fr = fraction6--;
	cout << fr << endl;
	cout << fraction6 << endl;

	char c;
	cin >> c;
}
