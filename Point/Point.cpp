#include <iostream>
#include "Point.h"
#include <math.h>
using namespace std;

bool coordinateIsInSquare(double newCoordinate) {
	return abs(newCoordinate) <= 10000;
}

/*bool yInSquare(double newY) {
	return abs(newY) <= 10000;
}*/

void Point::setX(double newX) {
	if (coordinateIsInSquare(newX))
		x = newX;
	else
		x = newX / abs(newX) * 10000;
}

void Point::setY(double newY) {
	if (coordinateIsInSquare(newY))
		y = newY;
	else
		y = newY / abs(newY) * 10000;
}

Point::Point(double newX, double newY) {
	setX(newX);
	setY(newY);
}

void Point::print() {
	cout << "x = " << x << ", " << "y = " << y << endl;
}

void Point::moveX(double deltaX) {
	setX(x + deltaX);
}

void Point::moveY(double deltaY) {
	setY(y + deltaY);
}


