#include <stdio.h>
#include <math.h>

const double PI = 2 * acos(0); 

double computeCircumCircleArea(double a, double b, double c);
double computeInCircleArea(double a, double b, double c);
double computeCircleArea(double radius);
double computeTriangleArea(double a, double b, double c);

int main(void)
{
	double a, b, c, inCircleArea, triangleArea, circumCircleArea;

	while(scanf("%lf %lf %lf", &a, &b, &c) > 0)
	{
		triangleArea = computeTriangleArea(a, b, c);
		inCircleArea = computeInCircleArea(a, b, c);
		circumCircleArea = computeCircumCircleArea(a, b, c);

		printf("%.4lf %.4lf %.4lf\n", circumCircleArea - triangleArea,
			triangleArea - inCircleArea, inCircleArea);
	}
	return 0;
}

double computeTriangleArea(double a, double b, double c)
{
	double semiPerimeter = (a + b + c) / 2;

	return sqrt(semiPerimeter * (semiPerimeter - a) * (semiPerimeter - b) * (semiPerimeter - c)); 
}

double computeCircleArea(double radius)
{
	return PI * radius * radius;
}

double computeInCircleArea(double a, double b, double c)
{
	double semiPerimeter = (a + b + c) / 2;

	return computeCircleArea(computeTriangleArea(a, b, c) / semiPerimeter);
}

double computeCircumCircleArea(double a, double b, double c)
{
	return computeCircleArea(a * b * c / (4 * computeTriangleArea(a, b, c)));
}
