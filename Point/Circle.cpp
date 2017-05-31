#include <iostream>
#include "Circle.h"
#include <algorithm>
using namespace std;

void Circle::setX(double newX) {
	if (coordinateIsInSquare(abs(newX) + R))
		center.setX(newX);
	else
		center.setX(newX / abs(newX) * (10000 - R));
}

void Circle::setY(double newY) {
	if (coordinateIsInSquare(abs(newY) + R))
		center.setY(newY);
	else
		center.setY(newY / abs(newY) * (10000 - R));
}

void Circle::setR(double newR) {
	double maxXOfCircle;//максимальное значение модуля координаты X в окружности, с новым радиусом
	maxXOfCircle = abs(center.getX()) + newR;
	double maxYOfCircle;//максимальное значение модуля координаты Y в окружности, с новым радиусом
	maxYOfCircle = abs(center.getY()) + newR;
	if (coordinateIsInSquare(maxXOfCircle) && coordinateIsInSquare(maxYOfCircle))
		R = newR;
	else {
		double distanceToBorderX;//расстояние от центра окружности до границы квадрата по оси X
		distanceToBorderX = 10000 - abs(center.getX());
		double distanceToBorderY;//расстояние от центра окружности до границы квадрата по оси Y
		distanceToBorderY = 10000 - abs(center.getY());
		R = min(distanceToBorderX, distanceToBorderY);
	}
}

Circle::Circle(double newX, double newY, double newR) {
	R = newR;
	setX(newX);
	setY(newY);
}

void Circle::moveX(double deltaX) {
	setX(center.getX() + deltaX);
}

void Circle::moveY(double deltaY) {
	setY(center.getY() + deltaY);
}

void Circle::print() {
	center.print();
	cout << "R = " << R << endl;
}

