#ifndef POINT
#define POINT

class Point {
	double x;
	double y;
public:
	Point(double newX = 0, double newY = 0);
	double getX() {
		return x;
	}
	double getY() {
		return y;
	}
	void setX(double newX);
	void setY(double newY);
	void print();
	void moveX(double deltaX);
	void moveY(double deltaY);
};

bool coordinateIsInSquare(double newCoordinate);

#endif