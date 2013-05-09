#include <stdio.h>
#include <math.h>

/*
 * Let P be an n-vertex polygon of equal sides inside a circle of radius R.
 *
 * Let P = A(1)A(2) ... A(n) A(1)	(A(i) is a vertex)
 * Let O be the center of a circle.
 *
 * area(P) = n * area(OA(1)A(2))
 *
 * The angle A(1) O A(2) is 2 * pi / n in radian
 * 
 * So area(O A(1) A(2) ) = 1/2 * R^2 * sin (A(1) O A(2))
 *
 * So area(P) = 1/2 * n * R^2 * sin (2 * pi / n)
 */

#define PI 3.14159265359

double computeAreaEnclosedEqualSidePolygon(double radius, int numV);

int main(void)
{
	int numV;
	double radius;

	while(scanf("%lf %d", &radius, &numV) > 0)
	{
		printf("%.3lf\n", computeAreaEnclosedEqualSidePolygon(radius, numV));
	}

	return 0;
}

double computeAreaEnclosedEqualSidePolygon(double radius, int numV)
{
	return 0.5 * numV * radius * radius * sin(2 * PI / numV);
}
