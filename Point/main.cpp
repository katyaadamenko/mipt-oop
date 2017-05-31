#include <iostream>
#include "Point.h"
#include "Circle.h"
using namespace std;

int main() {
	Point point(1, 5);//создание точки
	point.print();
	point.setX(100000);
	point.setY(-7);
	point.print();
	point.moveX(-10000);
	point.moveY(-20000);
	point.print();
	cout << endl;

	int n;//создание массива точек
	n = 3;
	Point *points = new Point[n];
	for (int i = 0; i < n; ++i) {
		points[i].print();//показывает, как массив инициализируется по умолчанию
		points[i].setX(i + 1);
		points[i].setY(i + 1);//инициализация массива
	}
	cout << endl;

	for (int i = 0; i < n; ++i)
		cout << "points[" << i << "]: x = " << points[i].getX() << " y = " << points[i].getY() << endl; //вывод элементов массива
	delete[] points;
	cout << endl;

	Point *point1 = new Point(3, 6);
	point1->moveX(1.5);
	point1->moveY(5);
	point1->print();
	delete point1;
	cout << endl;

	Point(-50000, 1);//точка за пределами квадрата
	cout << endl;

	Circle circle;//создание окружности
	circle.print();//как инициализируется по умолчанию
	circle.setX(5);
	circle.setY(-9900);
	circle.setR(200);//изменение радиуса
	circle.print();
	circle.moveX(5);//перемещение окружности
	circle.print();
	circle.setR(100000);//изменение радиуса за пределы квадрата
	circle.print();
	circle.moveX(100000);
	circle.moveY(100000);//большое перемещение окружности
	circle.print();
	cout << endl;

	n = 3;//массив окружностей
	Circle *arrayOfCircles = new Circle[n];
	for (int i = 0; i < n; ++i) {
		arrayOfCircles[i].setX(i + 1);
		arrayOfCircles[i].setY(i + 1);
		arrayOfCircles[i].setR(1);
	}
	for (int i = 0; i < n; ++i)
		cout << "Circle" << i << ": x = " << arrayOfCircles[i].getX() << ' ' << "y = " << arrayOfCircles[i].getY() << " R = " << arrayOfCircles[i].getR() << endl;
	delete[] arrayOfCircles;
	cout << endl;

	Circle *circle3 = new Circle;
	circle3->print();
	delete circle3;
	cout << endl;

	Circle *circle4 = new Circle(1, 2);
	circle4->print();
	delete circle4;

	char c;
	cin >> c;
	return 0;
}