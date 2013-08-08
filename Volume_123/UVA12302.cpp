#include <cstdio>
#include <cmath>

using namespace std;

const double EPS = 0.0000000001;

class Point {
private:
    double _x, _y;
public:
    Point() : _x(0), _y(0) {}
    Point(double x, double y) : _x(x), _y(y) {}
    Point(const Point & p) : _x(p._x), _y(p._y) {}

    double computeDistance(const Point & another) const;
    Point & operator= (const Point & another);
    Point getMidPoint(const Point & another) const;

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

Point Point::getMidPoint(const Point & another) const
{
    Point mid;
    mid._x = (_x + another._x) / 2.0;
    mid._y = (_y + another._y) / 2.0;

    return mid;
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
    Circle() : _center(0, 0), _radius(0) {}
    Circle(const Point & center, double radius) : _center(center), _radius(radius) {}
    Circle(const Circle & another) : _center(another._center), _radius(another._radius) {}
    Circle(const Point & A, const Point &B, const Point &C);

    Circle & operator= (const Circle & another);

friend int main(void);
};

Circle & Circle::operator= (const Circle & another)
{
    if(this == &another)
        return *this;

    _center = another._center;
    _radius = another._radius;

    return *this;
}

Circle::Circle(const Point & A, const Point & B, const Point & C)
{
    Point origin;

    double a1 = 2.0 * (A._x - B._x),
           b1 = 2.0 * (A._y - B._y),
           c1 = A._x * A._x + A._y * A._y - B._x * B._x - B._y * B._y,
           a2 = 2.0 * (A._x - C._x),
           b2 = 2.0 * (A._y - C._y),
           c2 = A._x * A._x + A._y * A._y - C._x * C._x - C._y * C._y;

    double delta = a1 * b2 - a2 * b1;
    if(fabs(delta) < EPS)
    {
        // 3 points are collinear. Return the dummy empty circle
        _center = origin;
        _radius = 0;
    }

    _center._x = (c1 * b2 - c2 * b1) / delta;
    _center._y = (c1 * a2 - c2 * a1) / (-delta);
    _radius = _center.computeDistance(A);
}

Circle getNinePointCircle(const Point & A, const Point & B, const Point & C);

int main(void)
{
    Point A, B, C;
    Circle ninePointCircle;

    while(1)
    {
        scanf("%lf %lf %lf %lf %lf %lf", &A._x, &A._y, &B._x, &B._y, &C._x, &C._y);
        if(A._x < 0)
            break;

        ninePointCircle = getNinePointCircle(A, B, C);

        printf("%.6lf %.6lf %.6lf\n", ninePointCircle._center._x, ninePointCircle._center._y,
                                    ninePointCircle._radius);
    }

    return 0;
}

Circle getNinePointCircle(const Point & A, const Point & B, const Point & C)
{
    Point midAB = A.getMidPoint(B);
    Point midAC = A.getMidPoint(C);
    Point midBC = B.getMidPoint(C);

    return Circle(midAB, midAC, midBC);
}
