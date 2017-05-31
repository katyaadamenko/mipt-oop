#ifndef CIRCLE
#define CIRCLE

#include "Point.h"

class Circle {
	Point center;
	double R;
public:
	Circle(double newX = 0, double newY = 0, double newR = 0);
	double getX() {
		return center.getX();
	}
	double getY() {
		return center.getY();
	}
	double getR() {
		return R;
	}
	void setX(double newX);
	void setY(double newY);
	void setR(double newR);
	void print();
	void moveX(double deltaX);
	void moveY(double deltaY);
};

#endif