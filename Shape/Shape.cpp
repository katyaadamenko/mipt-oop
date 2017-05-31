#include "Shape.h"
#include <algorithm>
#include <cstdlib>
#include <cmath>
using namespace std;

const double EPS = 1E-5;

Point::Point(double x, double y) {
	this->x = x;
	this->y = y;
}

ostream & operator<<(ostream & os, const Point& p) {
	os << p.getX() << ' ' << p.getY();
	return os;
}

Point * Point::findIntersectionsWithSegment(int & cnt, const DirectedSegment & s) {
	Point * intersections = new Point;
	if (s.isPointOn(*this)) {
		*intersections = *this;
		cnt = 1;
	}
	else {
		intersections = nullptr;
		cnt = 0;
	}
	return intersections;
}

double findDistanceBetweenPoints(const Point& p1, const Point& p2) {
	return sqrt((p1.getX() - p2.getX()) * (p1.getX() - p2.getX()) +
		(p1.getY() - p2.getY()) * (p1.getY() - p2.getY()));
}

bool Point::isPointOn(const Point& p)const {
	return findDistanceBetweenPoints(*this, p) < EPS;
}

bool Point::isPointIn(const Point& p)const {
	return isPointOn(p);
}

double Vector::findCrossProduct(const Vector& v)const {
	return this->getX() * v.getY() - this->getY() * v.getX();
}

double Vector::findLength()const {
	return sqrt(this->getX() * this->getX() + this->getY() * this->getY());
}

double Vector::findAngleBetweenVectors(const Vector& v2)const {
	return acos((this->getX() * v2.getX() + this->getY() * v2.getY()) / (this->findLength() * v2.findLength()));
}

double findDistanceBetweenPointAndLine(const Point& p, const DirectedSegment& s) {
	DirectedSegment segment(s.getBeginning(), p);
	return fabs(segment.findCrossProduct(s)) / s.findLength();
}

double DirectedSegment::findAngleBetweenSegments(DirectedSegment & s)const {
	return acos(((this->end.getX() - this->beginning.getX()) * (s.end.getX() - s.beginning.getX()) + 
		(this->end.getY() - this->beginning.getY()) * (s.end.getY() - s.beginning.getY())) / (this->findLength() * s.findLength()));
}

double DirectedSegment::findCrossProduct(const DirectedSegment& s)const {
	return ((this->end).getX() - (this->beginning).getX()) * ((s.end).getY() - (s.beginning).getY()) -
		((this->end).getY() - (this->beginning).getY()) * ((s.end).getX() - (s.beginning).getX());
}

double DirectedSegment::findScalarProduct(const DirectedSegment& s)const {
	return ((this->end).getX() - (this->beginning).getX()) * ((s.end).getX() - (s.beginning).getX()) +
		((this->end).getY() - (this->beginning).getY()) * ((s.end).getY() - (s.beginning).getY());
}

double DirectedSegment::findLength()const {
	return findDistanceBetweenPoints(beginning, end);
}

double DirectedSegment::findDistanceBetweenPointAndSegment(const Point& point)const {
	DirectedSegment s(this->getEnd(), this->getEnd());
	DirectedSegment segment1(point, this->beginning);
	DirectedSegment segment2(point, this->end);
	double distance;
	if (this->beginning.isPointIn(this->end))
		distance = findDistanceBetweenPoints(point, this->beginning);
	else {
		distance = findDistanceBetweenPointAndLine(point, *this);
		if (segment1.findScalarProduct(s) * segment2.findScalarProduct(*this) <= 0)
			distance = min(findDistanceBetweenPoints(point, this->beginning), findDistanceBetweenPoints(point, this->end));
	}
	return distance;
}

ostream & operator<<(ostream & os, const DirectedSegment& s) {
	os << s.getBeginning() << ' ' << s.getEnd();
	return os;
}

Point * DirectedSegment::findIntersectionsWithSegment(int & cnt, const DirectedSegment & s) {
	DirectedSegment segment1(this->beginning, s.beginning);
	DirectedSegment segment2(this->beginning, s.end);
	DirectedSegment segment3(s.beginning, this->beginning);
	DirectedSegment segment4(s.beginning, this->end);
	double x1 = min((this->beginning).getX(), (this->end).getX());
	double x2 = max((this->beginning).getX(), (this->end).getX());
	double x3 = min((s.beginning).getX(), (s.end).getX());
	double x4 = max((s.beginning).getX(), (s.end).getX());
	double y1 = min((this->beginning).getY(), (this->end).getY());
	double y2 = max((this->beginning).getY(), (this->end).getY());
	double y3 = min((s.beginning).getY(), (s.end).getY());
	double y4 = max((s.beginning).getY(), (s.end).getY());
	Point * intersections = new Point;
	if (this->findCrossProduct(segment1) * this->findCrossProduct(segment2) > 0 ||
		s.findCrossProduct(segment3) * s.findCrossProduct(segment4) > 0 ||
		(x2 < x3) || (x4 < x1) || (y2 < y3) || (y4 < y1))
	{
		intersections = nullptr;
		cnt = 0;
		return intersections;
	}
	if (this->findCrossProduct(segment1) == 0 && this->findCrossProduct(segment2) == 0) {
		intersections = nullptr;
		cnt = -1;
		return intersections;
	}
	double a1 = this->end.getY() - this->beginning.getY();
	double b1 = this->beginning.getX() - this->end.getX();
	double c1 = this->beginning.getX() * (this->beginning.getY() - this->end.getY()) + this->beginning.getY() * (this->end.getX() - this->beginning.getX());
	double a2 = s.end.getY() - s.beginning.getY();
	double b2 = s.beginning.getX() - s.end.getX();
	double c2 = s.beginning.getX() * (s.beginning.getY() - s.end.getY()) + s.beginning.getY() * (s.end.getX() - s.beginning.getX());
	double det = a1 * b2 - a2 * b1;
	double detX = -c1 * b2 + c2 * b1;
	double detY = -c2 * a1 + c1 * a2;
	intersections->setX(detX / det);
	intersections->setY(detY / det);
	cnt = 1;
	return intersections;
}

bool DirectedSegment::isPointOn(const Point& p)const {
	DirectedSegment s(this->beginning, p);
	double x1 = min((this->beginning).getX(), (this->end).getX());
	double x2 = max((this->beginning).getX(), (this->end).getX());
	double y1 = min((this->beginning).getY(), (this->end).getY());
	double y2 = max((this->beginning).getY(), (this->end).getY());
	if (this->findCrossProduct(s) == 0 &&
		p.getX() <= x2 && p.getX() >= x1 && 
		p.getY() <= y2 && p.getY() >= y1)
		return true;
	else
		return false;
}

bool DirectedSegment::isPointIn(const Point& p)const {
	return isPointOn(p);
}

ostream & operator<<(ostream & os, const Circle& c) {
	os << c.getCenter() << ' ' << c.getR();
	return os;
}

bool Circle::isPointOn(const Point& p)const {
	return abs(R - findDistanceBetweenPoints(p, center)) < EPS;
}

bool Circle::isPointIn(const Point& p)const {
	return findDistanceBetweenPoints(p, center) <= R - EPS;
}

/*Point * Circle::findIntersectionsWithSegment(int & cnt, const DirectedSegment & s) {
	Point * intersections;
	double a, b, c; // коэффициенты квадратного уравнения
	double x1 = s.getBeginning().getX();
	double x2 = s.getEnd().getX();
	double y1 = s.getBeginning().getY();
	double y2 = s.getEnd().getY();
	double x0 = center.getX();
	double y0 = center.getY();
	double deltaX = x2 - x1;
	double deltaY = y2 - y1;
	a = deltaX * deltaX + deltaY * deltaY;
	b = 2 * deltaX * (deltaY * ((y1 - y0) * x2 - (y2 - y0) * x1) - deltaX * x0);
	c = x0 * x0 * deltaX * deltaX + (x2 * (y1 - y0) - x1 * (y2 - y0)) * (x2 * (y1 - y0) - x1 * (y2 - y0)) -
		R * R * deltaX * deltaX;
	double D = b * b - 4 * a * c;
	if (D < 0) {
		intersections = nullptr;
		cnt = 0;
	}
	else if (abs(D) < 0.00001) {
		cnt = 1;
		intersections = new Point;
		*intersections = (-1) * b / (2 * a);
	}

	else {
		cnt = 2;
		intersections = new Point[2];
		intersections[0] = ((-1) * b - sqrt(D)) / (2 * a);
		intersections[1] = ((-1) * b + sqrt(D)) / (2 * a);
	}
	return intersections;
}*/

Point * Circle::findTangentsFromPoint(int & cnt, const Point& point) {
	double x1, y1, x0, y0;
	x0 = this->center.getX();
	y0 = this->center.getY();
	x1 = point.getX();
	y1 = point.getY();
	double x3, y3, x4, y4; // решения 
	double d = findDistanceBetweenPoints(point, this->getCenter());
	if (R < EPS) {
		cnt = 1;
		x3 = this->getCenter().getX();
		y3 = this->getCenter().getY();
	}
	else {
		if (this->isPointIn(point))
			cnt = 0;
		else if (this->isPointOn(point)) {
			cnt = 1;
			x3 = point.getX();
			y3 = point.getY();
		}
		else if (x1 == x0){
			cnt = 2;
			y3 = (y1 + y0) / 2 + (2 * R * R - d * d) / (2 * (y1 - y0));
			y4 = y3;
			x3 = x0 - sqrt(R * R - (y3 - y0) * (y3 - y0));
			x4 = x0 + sqrt(R * R - (y3 - y0) * (y3 - y0));
		}
		else {
			cnt = 2;
			double k = (y0 - y1) / (x1 - x0);
			double f = (y1 * y1 - y0 * y0 + 2 * R * R - d * d) / (2 * (x1 - x0)) + (x1 + x0) / 2;
			double a, b, c;
			a = k * k + 1;
			b = 2 * (k * f - x0 * k - y0);
			c = x0 * x0 - 2 * x0 * f + y0 * y0 - R * R + f * f;
			double D = b * b - 4 * a * c;
			y3 = (-b - sqrt(D)) / (2 * a);
			y4 = (-b + sqrt(D)) / (2 * a);
			x3 = k * y3 + f;
			x4 = k * y4 + f;
		}
	}
	Point * intersections;
	if (cnt == 0)
		intersections = nullptr;
	else if (cnt == 1) {
		intersections = new Point;
		Point point1(x3, y3);
		intersections[0] = point1;
	}
	else {
		intersections = new Point[2];
		Point point1(x3, y3);
		Point point2(x4, y4);
		intersections[0] = point1;
		intersections[1] = point2;
	}
	return intersections;
}

Point * Circle::findIntersectionsWithCircle(int & cnt, const Circle& circle2) {
	double x1, y1, R1, x2, y2, R2;
	x1 = this->center.getX();
	y1 = this->center.getY();
	R1 = this->R;
	x2 = circle2.center.getX();
	y2 = circle2.center.getY();
	R2 = circle2.R;
	double d = findDistanceBetweenPoints(this->getCenter(), circle2.getCenter());
	double x3, y3, x4, y4;
	double a, b;
	double x0, y0;
	double c;
	if (d > (R1 + R2) || (d == 0 && R1 != R2) || (d + R1) < R2 || (d + R2) < R1)
		cnt = 0;
	else if (d == 0 && R1 != 0)
		cnt = 3;
	else if (d == 0) {
		cnt = 1;
		x3 = x1;
		y3 = y1;
	}
	else if (d == (R1 + R2) || (d + R2) == R1 || (d + R1) == R2) {
		cnt = 1;
		x3 = x1 + (x2 - x1) * R1 / d;
		y3 = y1 + (y2 - y1) * R1 / d;
	}
	else if (d >= R1 && d >= R2) {
		cnt = 2;
		a = (R1 * R1 + d * d - R2 * R2) / (2 * d);
		b = d - a;
		c = sqrt(R1 * R1 - a * a);
		x0 = (b * x1 + a * x2) / d;
		y0 = (b * y1 + a * y2) / d;
		x3 = x0 - (y2 - y1) * c / d;
		y3 = y0 + (x2 - x1) * c / d;
		x4 = x0 + (y2 - y1) * c / d;
		y4 = y0 - (x2 - x1) * c / d;
	}
	else if (d < R2) {
		cnt = 2;
		a = (R2 * R2 - d * d - R1 * R1) / (2 * d);
		c = sqrt(R1 * R1 - a * a);
		x0 = (x1 * (d + a) - x2 * a) / d;
		y0 = (y1 * (d + a) - y2 * a) / d;
		x3 = x0 - (y2 - y1) * c / d;
		y3 = y0 + (x2 - x1) * c / d;
		x4 = x0 + (y2 - y1) * c / d;
		y4 = y0 - (x2 - x1) * c / d;
	}
	else if (d < R1) {
		cnt = 2;
		a = (R1 * R1 - d * d - R2 * R2) / (2 * d);
		c = sqrt(R2 * R2 - a * a);
		x0 = (x2 * (d + a) - x1 * a) / d;
		y0 = (y2 * (d + a) - y1 * a) / d;
		x3 = x0 - (y1 - y2) * c / d;
		y3 = y0 + (x1 - x2) * c / d;
		x4 = x0 + (y1 - y2) * c / d;
		y4 = y0 - (x1 - x2) * c / d;
	}
	Point * intersections;
	if (cnt == 0 || cnt == -1)
		intersections = nullptr;
	else if (cnt == 1) {
		intersections = new Point;
		Point point1(x3, y3);
		intersections[0] = point1;
	}
	else {
		intersections = new Point[2];
		Point point1(x3, y3);
		Point point2(x4, y4);
		intersections[0] = point1;
		intersections[1] = point2;
	}
	return intersections;
}

Point * Circle::findIntersectionsWithSegment(int & cnt, const DirectedSegment& s) {
	Point * intersections;
	cnt = 0;
	double x1 = s.getBeginning().getX();
	double x2 = s.getEnd().getX();
	double y1 = s.getBeginning().getY();
	double y2 = s.getEnd().getY();
	double x0 = center.getX();
	double y0 = center.getY();
	double distanceBetweenPointAndSegment = abs((x2 - x0) * (y1 - y0) - (x1 - x0) * (y2 - y0));
	if (distanceBetweenPointAndSegment >= (R + EPS) * findDistanceBetweenPoints(s.getBeginning(), s.getEnd())) {
		intersections = nullptr;
		cnt = 0;
		return intersections;
	}
	double a, b, c;
	double deltaX = x2 - x1;
	double deltaY = y2 - y1;
	a = deltaX * deltaX + deltaY * deltaY;
	b = 2 * deltaX * (deltaY * ((y1 - y0) * x2 - (y2 - y0) * x1) - deltaX * x0);
	c = x0 * x0 * deltaX * deltaX + (x2 * (y1 - y0) - x1 * (y2 - y0)) * (x2 * (y1 - y0) - x1 * (y2 - y0)) -
		R * R * deltaX * deltaX;
	double D = b * b - 4 * a * c;
	double solution1X = ((-1) * b - sqrt(D)) / (2 * a);
	double solution1Y = deltaY / deltaX * solution1X + (y1 * x2 - y2 * x1) / deltaX;
	Point solution1(solution1X, solution1Y);
	double solution2X = ((-1) * b + sqrt(D)) / (2 * a);
	double solution2Y = deltaY / deltaX * solution2X + (y1 * x2 - y2 * x1) / deltaX;
	Point solution2(solution2X, solution2Y);
	x1 = min((s.getBeginning()).getX(), (s.getEnd()).getX());
	x2 = max((s.getBeginning()).getX(), (s.getEnd()).getX());
	if (solution1X >= (x1 - EPS) && solution1X <= (x2 + EPS) &&
		solution2X >= (x1 - EPS) && solution2X <= (x2 + EPS)) {
		cnt = 2;
		intersections = new Point[2];
		intersections[0] = solution1;
		intersections[1] = solution2;
	}
	else if (solution1X >= (x1 - EPS) && solution1X <= (x2 + EPS)) {
		cnt = 1;
		intersections = new Point;
		intersections[0] = solution1;
	}
	else if (solution2X >= (x1 - EPS) && solution2X <= (x2 + EPS)) {
		cnt = 1;
		intersections = new Point;
		intersections[0] = solution2;
	}
	else {
		cnt = 0;
		intersections = nullptr;
	}
	return intersections;
}

Polygon:: Polygon(int numberOfVertices) : numberOfVertices(numberOfVertices) {
	this->vertices = new Point[numberOfVertices];
}

Polygon::Polygon(int numberOfVertices, Point * vertices): numberOfVertices(numberOfVertices) {
	this->vertices = new Point[numberOfVertices];
	for (int i = 0; i < numberOfVertices; ++i)
		this->vertices[i] = vertices[i];
}

void Polygon::copy(const Polygon& p) {
	this->numberOfVertices = p.numberOfVertices;
	this->vertices = new Point[p.numberOfVertices];
	for (int i = 0; i < p.numberOfVertices; ++i)
		vertices[i] = p.vertices[i];
}

Polygon::Polygon(const Polygon& p) {
	copy(p);
}

Polygon & Polygon:: operator =(const Polygon& p) {
	if (this != &p) {
		delete[] vertices;
		copy(p);
	}
	return *this;
}

DirectedSegment Polygon::getSide(int i)const {
	int indexOfEndPoint;
	if (i != numberOfVertices - 1)
		indexOfEndPoint = i + 1;
	else
		indexOfEndPoint = 0;
	DirectedSegment side(vertices[i], vertices[indexOfEndPoint]);
	return side;
}

double Polygon::findPerimeter()const {
	double perimeter = 0;
	for (int i = 0; i < numberOfVertices; ++i)
		perimeter += getSide(i).findLength();
	return perimeter;
}

double Polygon::findArea()const {
	double area = 0;
	Polygon polygon(*this);
	double minY = vertices[0].getY();
	for (int i = 1; i < numberOfVertices; ++i)
		if (vertices[i].getY() < minY)
			minY = vertices[i].getY();
	for (int i = 0; i < numberOfVertices; ++i)
		polygon.getVertice(i).setY(polygon.getVertice(i).getY() - minY);
	double x1, x2, y1, y2;
	for (int i = 0; i < numberOfVertices; ++i) {
		x1 = polygon.getSide(i).getBeginning().getX();
		y1 = polygon.getSide(i).getBeginning().getY();
		x2 = polygon.getSide(i).getEnd().getX();
		y2 = polygon.getSide(i).getEnd().getY();
		area += (x2 - x1) * (y1 + y2) / 2;
	}
	return fabs(area);
}

ostream & operator<<(ostream & os, const Polygon& p) {
	for (int i = 0; i < p.getNumberOfVertices(); ++i)
		os << p.getVertice(i) << endl;
	return os;
}

Point * Polygon::findIntersectionsWithSegment(int & cnt, const DirectedSegment& s) {
	Point * intersections = new Point[numberOfVertices];
	cnt = 0;
	bool isIntersectionWithCommonVertice = false;
	bool isIntersectionWithVertice0 = false;
	Point * intersectionsWithSide;
	int indexOfEndPoint;
	for (int i = 0; i < numberOfVertices; ++i) {
		if (i != numberOfVertices - 1)
			indexOfEndPoint = i + 1;
		else
			indexOfEndPoint = 0;
		DirectedSegment side(vertices[i], vertices[indexOfEndPoint]);
		int cntForSide;
		intersectionsWithSide = side.findIntersectionsWithSegment(cntForSide, s);
		if (cntForSide == -1) {
			cnt = -1;
			delete[] intersections;
			intersections = nullptr;
			break;
		}
		else if (cntForSide == 1) {
			if (i == 0) {
				if (vertices[0].isPointIn(*intersectionsWithSide))
					isIntersectionWithVertice0 = true;
				intersections[cnt] = *intersectionsWithSide;
				++cnt;
			}
			else if (i == numberOfVertices - 1) {
				if ((!isIntersectionWithVertice0 || !vertices[0].isPointIn(*intersectionsWithSide)) && 
					(!isIntersectionWithCommonVertice || !vertices[i].isPointIn(*intersectionsWithSide))) {
					intersections[cnt] = *intersectionsWithSide;
					++cnt;
				}
			}
			else  {
				if (!vertices[i].isPointIn(*intersectionsWithSide) || !isIntersectionWithCommonVertice) {
					intersections[cnt] = *intersectionsWithSide;
					++cnt;
					if (vertices[indexOfEndPoint].isPointIn(*intersectionsWithSide))
						isIntersectionWithCommonVertice = true;
					else
						isIntersectionWithCommonVertice = false;
				}
				else
					isIntersectionWithCommonVertice = false;
			}
			delete intersectionsWithSide;
		}
		else
			isIntersectionWithCommonVertice = false;
	}
	Point * intersectionsWithPolygon;
	if (cnt != 0 && cnt != -1) {
		intersectionsWithPolygon = new Point[cnt];
		for (int i = 0; i < cnt; ++i)
			intersectionsWithPolygon[i] = intersections[i];
	}
	else
		intersectionsWithPolygon = nullptr;
	delete[] intersections;
	return intersectionsWithPolygon;
}

bool Polygon::isPointOn(const Point& p)const {
	bool isOn = false;
	int indexOfEndPoint;
	for (int i = 0; i < numberOfVertices; ++i) {
		if (i == numberOfVertices - 1)
			indexOfEndPoint = 0;
		else
			indexOfEndPoint = i + 1;
		DirectedSegment side(vertices[i], vertices[indexOfEndPoint]);
		if (side.isPointOn(p)) {
			isOn = true;
			break;
		}
	}
	return isOn;
}

bool Polygon::isPointIn(const Point& p)const {
	if (isPointOn(p))
		return true;
	int numberOfIntersections = 0;
	int cnt = 0;
	int indexOfPreviousPoint;
	double maxX = vertices[0].getX();
	for (int i = 0; i < numberOfVertices; ++i)
		if (vertices[i].getX() > maxX)
			maxX = vertices[i].getX();
	if (maxX < p.getX())
		return false;
	Point endPoint(maxX + 1, p.getY());
	DirectedSegment segment(p, endPoint);
	for (int i = 0; i < numberOfVertices; ++i) {
		if (i == 0)
			indexOfPreviousPoint = numberOfVertices - 1;
		else
			indexOfPreviousPoint = i - 1;
		DirectedSegment side = getSide(i);
		int cnt1;
		Point * intersectionsWithSide = side.findIntersectionsWithSegment(cnt1, segment);
		if (cnt1 == 1) {
			++numberOfIntersections;
			if (vertices[i].isPointIn(*intersectionsWithSide)) {
				DirectedSegment previousSide(vertices[i], vertices[indexOfPreviousPoint]);
				if (segment.findCrossProduct(side) * segment.findCrossProduct(previousSide) <= 0)
					++cnt;
			}
			delete intersectionsWithSide;
		}
		else if (cnt1 == -1) {
			++numberOfIntersections;
			++cnt;
		}
	}
	if ((numberOfIntersections - cnt) % 2 != 0)
		return true;
	else
		return false;
}

bool Polygon::isConvex()const {
	bool isConvex = true;
	DirectedSegment previousSide = this->getSide(0);
	DirectedSegment side = this->getSide(1);
	int sign;
	if (previousSide.findCrossProduct(side) > 0)
		sign = -1;
	else
		sign = 1;
	previousSide = side;
	for (int i = 2; i < this->getNumberOfVertices(); ++i) {
		side = this->getSide(i);
		if (previousSide.findCrossProduct(side) * sign < 0) {
			isConvex = false;
			break;
		}
		previousSide = side;
	}
	if (isConvex && this->getSide(numberOfVertices - 1).findCrossProduct(this->getSide(0)) * sign < 0)
		isConvex = false;
	return isConvex;
}

Point findMinPoint(int numberOfPoints, Point * points) {
	Point minPoint = points[0];
	for (int i = 1; i < numberOfPoints; ++i) {
		if (points[i].getY() < minPoint.getY())
			minPoint = points[i];
		else if (points[i].getY() == minPoint.getY())
			if (points[i].getX() < minPoint.getX())
				minPoint = points[i];
	}
	return minPoint;
}

Point p0;

int angleCmp(const void* p1, const void* p2) {
	const Point* a = reinterpret_cast<const Point*>(p1);
	const Point* b = reinterpret_cast<const Point*>(p2);
	Point endPoint(p0.getX(), p0.getY() + 1);
	DirectedSegment segment(p0, endPoint);
	if (p0.isPointIn(*a))
		return -1;
	else if (p0.isPointIn(*b))
		return 1;
	DirectedSegment segment1(p0, *a);
	DirectedSegment segment2(p0, *b);
	int result;
	if (segment2.findCrossProduct(segment1) < 0)
		result = - 1;
	else if (segment2.findCrossProduct(segment1) == 0)
		result = 0;
	else
		result = 1;
	return result;
}

Polygon findConvexHull(int numberOfPoints, Point * points) {
	p0 = findMinPoint(numberOfPoints, points);
	qsort(points, numberOfPoints, sizeof(Point), angleCmp);
	Point * pointsSort = new Point[numberOfPoints];
	pointsSort[0] = points[0];
	pointsSort[1] = points[1];
	int number = 2;
	DirectedSegment s(points[0], points[1]);
	DirectedSegment s1(points[0], points[2]);
	for (int i = 2; i < numberOfPoints; ++i) {
		if (s.findCrossProduct(s1) != 0) {
			++number;
			pointsSort[number - 1] = points[i];
		}
		else if (s1.findLength() > s.findLength()) {
			pointsSort[number - 1] = points[i];
		}
		s.setEnd(pointsSort[number - 1]);
		if (i != numberOfPoints - 1)
			s1.setEnd(points[i + 1]);
	}
	Point * vertices = new Point[number];
	for (int i = 0; i < 3; ++i)
		vertices[i] = pointsSort[i];
	int numberOfVertices = 3;
	for (int i = 3; i < number; ++i) {
		DirectedSegment segment1(vertices[numberOfVertices - 2], vertices[numberOfVertices - 1]);
		DirectedSegment segment2(vertices[numberOfVertices - 1], pointsSort[i]);
		while (!(segment1.findCrossProduct(segment2) > 0)) {
			--numberOfVertices;
			segment1.setBeginning(vertices[numberOfVertices - 2]);
			segment1.setEnd(vertices[numberOfVertices - 1]);
			segment2.setBeginning(vertices[numberOfVertices - 1]);
		}
		++numberOfVertices;
		vertices[numberOfVertices - 1] = pointsSort[i];
	}
	Polygon polygon(numberOfVertices, vertices);
	delete[]pointsSort;
	delete[]vertices;
	return polygon;
}
