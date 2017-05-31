#include <iostream>
#include "Shape.h"
using namespace std;

int main() {
	Circle circle(0, 0, 1);
	Point point(0.5, 0.5);
	cout << circle.isPointOn(point) << ' ' << circle.isPointIn(point) << endl;
	DirectedSegment s(1, 0, 2, 3);
	DirectedSegment s1(-1, -3, 0, 0);
	int cnt;
	Point * intersections = circle.findIntersectionsWithSegment(cnt, s);
	cout << cnt << endl;
	for (int i = 0; i < cnt; ++i)
		cout << intersections[i] << endl;
	delete[] intersections;
	intersections = s.findIntersectionsWithSegment(cnt, s1);
	cout << cnt << endl;
	for (int i = 0; i < cnt; ++i)
		cout << intersections[i] << endl;
	delete[] intersections;
	DirectedSegment s2(1, 0, 3, 6);
	intersections = s.findIntersectionsWithSegment(cnt, s2);
	cout << cnt << endl;
	for (int i = 0; i < cnt; ++i)
		cout << intersections[i] << endl;
	delete[] intersections;
	DirectedSegment s3(-2, 0, 1, -1);
	intersections = s.findIntersectionsWithSegment(cnt, s3);
	cout << cnt << endl;
	for (int i = 0; i < cnt; ++i)
		cout << intersections[i] << endl;
	delete[] intersections;
	Point point1(1.6, 1.5);
	cout << s.isPointOn(point1) << endl;
	DirectedSegment s4(0, 0, 1, 1);
	Point point2(1.000001, 1.000001);
	cout << s.isPointIn(point2) << endl;
	Polygon polygon(4);
	Point * points = new Point[4];
	points[0].setX(0);
	points[0].setY(0);
	points[1].setX(4);
	points[1].setY(0);
	points[2].setX(4);
	points[2].setY(4);
	points[3].setX(0);
	points[3].setY(4);
	for (int i = 0; i < 4; ++i)
		polygon.setVertice(i, points[i]);
	delete[] points;
	Point point3(1, 0);
	cout << "in " << polygon.isPointIn(point3) << ' ' << polygon.isPointOn(point3) << endl;
	cout << "perimeter = " << polygon.findPerimeter() << endl;
	cout << "area = " << polygon.findArea() << endl;
	DirectedSegment s5(1, -1, 3, 3);
	intersections = polygon.findIntersectionsWithSegment(cnt, s5);
	cout << cnt << endl;
	for (int i = 0; i < cnt; ++i)
		cout << intersections[i] << endl;
	delete[] intersections;
	Point point5(1.5, 1.5);
	cout << polygon.isPointIn(point5) << endl;
	Polygon polygon1(4);
	points = new Point[4];
	points[0].setX(1);
	points[0].setY(-1);
	points[1].setX(2);
	points[1].setY(0);
	points[2].setX(1);
	points[2].setY(1);
	points[3].setX(0);
	points[3].setY(0);
	for (int i = 0; i < 4; ++i) {
		cout << fixed;
		cout << "p[i]  = " << points[i] << endl;
	}
	cout << findMinPoint(4, points) << endl;
	Polygon p = findConvexHull(4, points);
	for (int i = 0; i < 4; ++i) {
		cout << fixed;
		cout << "p[i]  = " << p.getVertice(i) << endl;
	}

	for (int i = 0; i < 4; ++i)
		polygon1.setVertice(i, points[i]);
	cout << "in " << polygon1.isPointIn(point3) << ' ' << polygon1.isPointOn(point3) << endl;
	delete[] points;
	Polygon polygon2(5);
	points = new Point[5];
	points[0].setX(1);
	points[0].setY(-1);
	points[1].setX(3);
	points[1].setY(0);
	points[2].setX(2);
	points[2].setY(0);
	points[3].setX(1);
	points[3].setY(1);
	points[4].setX(0);
	points[4].setY(0);
	for (int i = 0; i < 5; ++i)
		polygon2.setVertice(i, points[i]);
	cout << "in " << polygon1.isPointIn(point3) << ' ' << polygon1.isPointOn(point3) << endl;
	delete[] points;
	points = new Point[4];
	points[0].setX(0);
	points[0].setY(0);
	points[1].setX(1);
	points[1].setY(0);
	points[2].setX(2);
	points[2].setY(0);
	points[3].setX(1);
	points[3].setY(1);
	Polygon polygon3 = findConvexHull(4, points);
	for (int i = 0; i < polygon3.getNumberOfVertices(); ++i) {
		cout << fixed;
		cout << "p[i]  = " << polygon3.getVertice(i) << endl;
	}
	return 0;
}