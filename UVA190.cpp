#include <cstdio>
#include <cmath>

using namespace std;

const double EPS = 0.00000000001;

class Point {
private:
	double _x, _y;
public:
	Point() : _x(0), _y(0) {}
	Point(double x, double y) : _x(x), _y(y) {}
	Point(const Point & another) : _x(another._x), _y(another._y) {}
	~Point() {}

	Point & operator= (const Point & another);
	double computeDistance(const Point & another) const;

friend class Circle;
friend int main(void);
};

Point & Point::operator= (const Point & another)
{
	if(this == &another)
		return *this;

	_x = another._x;
	_y = another._y;

	return *this;
}

double Point::computeDistance(const Point & another) const
{
	return sqrt((_x - another._x) * (_x - another._x) + (_y - another._y) * (_y - another._y));
}

class Circle {
private:
	Point _center;
	double _radius;
public:
	Circle() : _center(Point(0, 0)), _radius(0) {}
	Circle(const Point & A, const Point & B, const Point &C);
	~Circle() {}

	Circle & operator= (const Circle & another);
	void printCompactEquation();
	void printExpandEquation();
};

Circle & Circle::operator= (const Circle & another)
{
	if(this != &another)
	{
		_center = another._center;
		_radius = another._radius;
	}

	return *this;
}

Circle::Circle(const Point & A, const Point & B, const Point & C)
{
	double a1 = 2 * (B._x - A._x),
	       b1 = 2 * (B._y - A._y),
	       c1 = B._x * B._x + B._y * B._y - A._x * A._x - A._y * A._y,
	       a2 = 2 * (C._x - A._x),
	       b2 = 2 * (C._y - A._y),
	       c2 = C._x * C._x + C._y * C._y - A._x * A._x - A._y * A._y;
	double delta = a1 * b2 - a2 * b1;

	if(fabs(delta) < EPS)
	{
		_center = Point(0, 0);
		_radius = 0;
	}
	else
	{
		_center._x = (c1 * b2 - c2 * b1) / delta;
		_center._y = (c2 * a1 - c1 * a2) / delta;
		_radius = _center.computeDistance(A);
	}

}

void Circle::printCompactEquation()
{
	char signX = '-';
	if(_center._x < 0)
		signX = '+';
	char signY = '-';
	if(_center._y < 0)
		signY = '+';

	printf("(x %c %.3lf)^2 + (y %c %.3lf)^2 = %.3lf^2\n", signX, fabs(_center._x), signY, fabs(_center._y), _radius);
}

void Circle::printExpandEquation()
{
	double c, d, e;
	char signC, signD, signE;

	signC = signD = signE = '+';
	c = -2 * _center._x;
	if(c < 0)
	{
		c = -c;
		signC = '-';
	}
	d = -2 * _center._y;
	if(d < 0)
	{
		d = -d;
		signD = '-';
	}
	e = _center._x * _center._x + _center._y * _center._y - _radius * _radius;
	if(e < 0)
	{
		e = -e;
		signE = '-';
	}

	printf("x^2 + y^2 %c %.3lfx %c %.3lfy %c %.3lf = 0\n", signC, c, signD, d, signE, e);
}

int main(void)
{
	Point A, B, C;
	Circle circumCircle;

	while(scanf("%lf %lf %lf %lf %lf %lf", &A._x, &A._y, &B._x, &B._y, &C._x, &C._y) > 0)
	{
		circumCircle = Circle(A, B, C);

		circumCircle.printCompactEquation();
		circumCircle.printExpandEquation();
		printf("\n");
	}
	return 0;
}
