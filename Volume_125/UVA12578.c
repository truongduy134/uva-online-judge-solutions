#include <stdio.h>
#include <math.h>

const double PI = acos(-1);
const double WIDTH_TO_LENGTH_RATIO = 0.6;
const double RADIUS_TO_LENGTH_RATIO = 0.2;

double computeRectangleArea(double length, double width);
double computeCircleArea(double radius);

int main(void)
{
	int T;
	double length, width, radius, recArea, circleArea;

	scanf("%d", &T);
	while(T)
	{
		scanf("%lf", &length);
		width = length * WIDTH_TO_LENGTH_RATIO;
		radius = length * RADIUS_TO_LENGTH_RATIO;

		recArea = computeRectangleArea(length, width);
		circleArea = computeCircleArea(radius);
		printf("%.2lf %.2lf\n", circleArea, recArea - circleArea);
		T--;
	}
	return 0;
}

double computeRectangleArea(double length, double width)
{
	return length * width;
}

double computeCircleArea(double radius)
{
	return PI * radius * radius;
}
