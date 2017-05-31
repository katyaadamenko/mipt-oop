#ifndef SHAPE
#define SHAPE

#include <iostream>
using namespace std;

class Point;
class DirectedSegment;

class Shape {
public:
	virtual Point * findIntersectionsWithSegment(int & cnt, const DirectedSegment & s) = 0;
	virtual bool isPointOn(const Point& p)const = 0;
	virtual bool isPointIn(const Point& p)const = 0;
};

class Point : public Shape {
	double x;
	double y;
public:
	double getX()const {
		return x;
	}
	double getY()const {
		return y;
	}
	void setX(double x) {
		this->x = x;
	}
	void setY(double y) {
		this->y = y;
	}
	Point(double x = 0, double y = 0);
	Point * findIntersectionsWithSegment(int & cnt, const DirectedSegment & s);
	bool isPointOn(const Point& p)const;
	bool isPointIn(const Point& p)const;
	friend ostream & operator<<(ostream & os, const Point& p);
};

class Vector : public Point {
public:
	Vector(double x, double y) :Point(x, y){}
	double findCrossProduct(const Vector& v)const;
	double findLength()const;
	double findAngleBetweenVectors(const Vector& v2)const;
};

class DirectedSegment : public Shape {
	Point beginning;
	Point end;
public:
	DirectedSegment(double x1, double y1, double x2, double y2) : beginning(x1, y1), end(x2, y2) {}
	DirectedSegment(Point p1, Point p2) : beginning(p1), end(p2){}
	Point getBeginning()const {
		return beginning;
	}
	Point getEnd()const {
		return end;
	}
	void setBeginning(Point beginning){
		this->beginning = beginning;
	}
	void setEnd(Point end) {
		this->end = end;
	}
	double findCrossProduct(const DirectedSegment& s)const;
	double findScalarProduct(const DirectedSegment& s)const;
	double findLength()const;
	friend ostream & operator<<(ostream & os, const DirectedSegment& s);
	Point * findIntersectionsWithSegment(int & cnt, const DirectedSegment & s);
	bool isPointOn(const Point& p)const;
	bool isPointIn(const Point& p)const;
	double findAngleBetweenSegments(DirectedSegment & s)const;
	double findDistanceBetweenPointAndSegment(const Point& p)const;
};

class Circle : public Shape {
	Point center;
	double R;
public:
	Circle(double x, double y, double R) : center(x, y), R(R) {}
	Circle(Point c, double R) : center(c), R(R) {}
	Point getCenter()const {
		return center;
	}
	double getR()const {
		return R;
	}
	void setCenter(Point center) {
		this->center = center;
	}
	void setR(double R) {
		this->R = R;
	}
	friend ostream & operator<<(ostream & os, const Circle& c);
	Point * findTangentsFromPoint(int & cnt, const Point& point);
	Point * findIntersectionsWithCircle(int & cnt, const Circle& circle2);
	Point * findIntersectionsWithSegment(int & cnt, const DirectedSegment & s);
	bool isPointOn(const Point& p)const;
	bool isPointIn(const Point& p)const;
};

class Polygon : public Shape {
	int numberOfVertices;
	Point * vertices;
	void copy(const Polygon& p);
public:
	Polygon(int numberOfVertices);
	Polygon(int numberOfVertices, Point * vertices);
	Polygon(const Polygon& p);
	~Polygon() {
		delete[] vertices;
	}
	Polygon& operator = (const Polygon& p);
	int getNumberOfVertices()const {
		return numberOfVertices;
	}
	Point getVertice(int i)const {
		return vertices[i];
	}
	DirectedSegment getSide(int i)const; //сторона с вершинами i и i + 1 (при i = n - 1 с вершинами i и 0)
	void setVertice(int i, Point newVertice) {
		this->vertices[i] = newVertice;
	}
	void setNumberOfVertices(int number) {
		numberOfVertices = number;
	}
	bool isConvex()const;
	double findPerimeter()const;
	double findArea()const;
	friend ostream & operator<<(ostream & os, const Polygon& p);
	bool isPointOn(const Point& p)const;
	bool isPointIn(const Point& p)const;
	Point * findIntersectionsWithSegment(int & cnt, const DirectedSegment & s);
};

double findDistanceBetweenPoints(const Point& p1, const Point& p2);
double findDistanceBetweenPointAndLine(const Point& p, const DirectedSegment& s);//прямая задается через лежащий на ней отрезок
Polygon findConvexHull(int numberOfPoints, Point * points);
Point findMinPoint(int numberOfPoints, Point * points);

#endif