#include <iostream>
#include "BigInt.h"
#include <ctime>
using namespace std;

int main() {
	cout << (-5) / 2 << ' ' << (-5) % 2 << endl;
	BigInt b(12045);
	int w = -10000;
	BigInt k(w);
	cout << k << endl;
	BigInt a = "-5678003";
	cout << "b = " << b << " a = " << a << endl;
	cout << a.getBASE() << endl;
	cout << a.getMaxIndex() << endl;
	cout << endl;
	
	BigInt d(1111111);
	BigInt e(9999999);
	BigInt f;
	f = d + e;
	cout << d << " + " << e << " = " << f << endl;
	f += 45611;
	cout << "f += 45611, f = " << f << endl;
	BigInt number("100001");
	BigInt number1("99999");
	cout << number << " - " << number1 << " = " << number - number1 << endl;
	BigInt number2(15055055);
	cout << "number2 = " << number2 << endl;
	cout << "number2 -= 5999999, number2 = " << (number2 -= 5999999) << endl;
	number2 -= 10000000;
	cout << "number2 -= 10000000, number2 = " << number2 << endl;
	BigInt result = number1 * f;
	cout << number1 << " * " << f << " = " << result << endl;
	BigInt number3("9827365432");
	BigInt number4("8374536");
	BigInt fr = number3 * number4;
	cout << number3 << " * " << number4 << " = " << fr << endl;

	BigInt number10("-100000");
	BigInt number11(-99999);
	cout << number10 << ' ' << number11 << endl;
	if (number10 < number11)
		cout << "yes!" << endl;
	else
		cout << "no!" << endl;

	if (number10 == number11)
		cout << "no!" << endl;
	else
		cout << "yes!" << endl;

	if (number11  >= '0')
		cout << "no!" << endl;
	else
		cout << "yes!" << endl;

	if (number11 <= 1)
		cout << "yes!" << endl;
	else
		cout << "no!" << endl;

	if (number11 == -99999)
		cout << "yes!" << endl;
	else
		cout << "no!" << endl;

	number11 = -number11;
	cout << number11 << endl;
	fr = number10 + number11;
	cout << number10 << " + " << number11 << " = " << fr << endl;
	fr = number10 - number11;
	cout << number10 << " - " << number11 << " = " << fr << endl;

	fr = number3 / number4;
	cout << number3 << " / " << number4 << " = " << fr  << endl;

	fr -= 1000;
	cout << fr << endl;

	cout << number2 << ' ' << number << endl;
	if (number2 >= number)
		cout << ":(" << endl;
	else
		cout << "yes!" << endl;
	if (number1 < 1234000)
		cout << "yes!" << endl;
	else
		cout << ":(" << endl;
	BigInt number7("736487264726249826497326492364");
	BigInt number8("65382328738278376473648273872");
	if (number7 == number8)
		cout << ":(" << endl;
	else
		cout << "yes!" << endl;
	if (number8 != number4)
		cout << "yes!" << endl;
	else
		cout << ":(" << endl;

	number7 = "7364723642346928";
	base_t number9 = 675;
	cout << number7 << " / " << number9 << " = " << number7 / number9 << endl;

	number7 = 674983;
	cout << "number7 = " << number7 << endl;
	number7 *= -12345;
	cout << "number7 *= -12345, number7 = " << number7 << endl;
	number8 = "123";
	cout << number7 / 123 << endl;
	number7 /= number8;
	cout << "number7 /= 123, number7 = " << number7 << endl;
	number8 = "12347";
	number7 = -47;
	cout << number8 / number7 << endl;
	fr = number8 / number7;
	cout << number8 << " % " << number7 << " = " << number8 % number7 << endl;
	number8 %= number7;
	cout << "number8 %= " << number7 << ", number8 = " << number8 << endl;
	number8 = "-98764375";
	cout << number8 << " * -567 = " << number8 * -567 << endl;
	cout << number8 << " / 678 = " << number8 / 678 << endl;
	cout << "number8 / 876 = " << number8 / 876 << " , number8 % 876 = " << number8 % 876 << endl;
	number8 %= 876;
	cout << "number8 %= 876, number8 = " << number8 << endl;
	/*BigInt b1 = "732647216473216487163487632187463274687324618732648721647647364716487362476214876432198764987326481764724687213648179834687648736473647383579823758326587163508765871365832756827516";
	BigInt b2 = "713264732164087321468732164873264735647638428739283912839217409182748638076473648327483746917643798316247150710873647354721750827360176328726472164735437087162870637186377124708263";
	clock_t t1 = clock();
	for (int i = 0; i < 300; ++i)
		b1 / b2;
	clock_t t2 = clock();
	cout << (t2 - t1) / (double)CLOCKS_PER_SEC << endl;*/
	cout << -number8 << endl;
	cout << findGreatestCommonDivisor(-number8, "3") << endl;
	cout << "end" << endl;

	char c;
	cin >> c;
	return 0;
}
