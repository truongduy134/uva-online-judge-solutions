#include <cstdio>
#include <cmath>
#include <vector>

using namespace std;

class Point {
private:
	double _xCoord, _yCoord;
public:
	Point() : _xCoord(0), _yCoord(0) {}
	Point(double xCoord, double yCoord) : _xCoord(xCoord), _yCoord(yCoord) {}
	Point(const Point & another) : _xCoord(another._xCoord), _yCoord(another._yCoord) {}
	~Point() {}

friend class Rectangle;
};

class Rectangle {
private:
	Point _upperLeft, _lowerRight;
public:
	Rectangle() {}
	Rectangle(const Point & upperLeft, const Point & lowerRight) : _upperLeft(upperLeft), _lowerRight(lowerRight) {}
	Rectangle(double xUpLeft, double yUpLeft, double xLowRight, double yLowRight) : _upperLeft(xUpLeft, yUpLeft), _lowerRight(xLowRight, yLowRight) {}
	Rectangle(const Rectangle & another) : _upperLeft(another._upperLeft), _lowerRight(another._lowerRight) {}
	~Rectangle() {}

	bool containStrictlyInside(const Point & point);
};

bool Rectangle::containStrictlyInside(const Point & point)
{
	return _upperLeft._xCoord < point._xCoord && point._xCoord < _lowerRight._xCoord && _lowerRight._yCoord < point._yCoord && point._yCoord < _upperLeft._yCoord; 
}

#define MAX_VAL 9999.9
#define PRECISION 0.00000000001

#define MAX_SIZE 1000
int main(void)
{
	double xUpLeft, yUpLeft, xLowRight, yLowRight, xCoord, yCoord;
	vector<Rectangle> rectList;
	vector<Point> pointList;
	char str[MAX_SIZE + 1];

	while(1)
	{
		scanf("%s", str);
		if(str[0] == '*')
			break;

		scanf("%lf %lf %lf %lf", &xUpLeft, &yUpLeft, &xLowRight, &yLowRight);
		rectList.push_back(Rectangle(xUpLeft, yUpLeft, xLowRight, yLowRight));
	}

	while(1)
	{
		scanf("%lf %lf", &xCoord, &yCoord);
		if(fabs(xCoord - MAX_VAL) < PRECISION &&
		   fabs(yCoord - MAX_VAL) < PRECISION)
			break;

		pointList.push_back(Point(xCoord, yCoord));
	}

	bool feasible;
	for(int p = 0; p < (int) pointList.size(); p++)
	{
		feasible = false;

		for(int r = 0; r < (int) rectList.size(); r++)
			if(rectList[r].containStrictlyInside(pointList[p]))
			{
				feasible = true;
				printf("Point %d is contained in figure %d\n", p + 1, r + 1);
			}

		if(!feasible)
			printf("Point %d is not contained in any figure\n", p + 1);
	}	
	return 0;
}
