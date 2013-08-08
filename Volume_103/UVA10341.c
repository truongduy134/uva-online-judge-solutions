/*******************************************************************************
 * Author: Nguyen Truong Duy
 ********************************************************************************/

/* Methodology:
 *	+ We use bisection method (similar to binary search algorithm) to find
 *	  the root of the following function
 *		f(x) = p * e^(-x) + q * sin(x) + r * cos(x) + s * tan(x) + t * x^2 + u
 *	  for x in [0, 1]
 *
 *	+ Note that 0 <= p, r and q, s, t <= 0
 *	+ Note that f(x) in monotone on [0, 1]. Hence, we can use bisection method
 *		to find the root
 *
 *	+ Detail:
 *		- If f(0) = 0 or f(0) = 1, then we are done.
 *		- If f(0) * f(1) > 0, then there is no solution
 *		- Consider the last cases: f(0) * f(1) < 0:
 *			- Then let mid = (0 + 1) / 2 = 0.5
 *			- If f(mid) = 0 then we are done.
 *			- Otherwise, if f(0) * f(mid) < 0, we search a root in (0, mid).
 *			  Otherwise, we search a root in (mid, 1)
 */

#include <stdio.h>
#include <math.h>

int binarySearchSolution(int p, int q, int r, int s, int t, int u, double * solution);
double f(int p, int q, int r, int s, int t, int u, double x);

const double EPSILON = 0.00000000001;

int main(void)
{
	int p, q, r, s, t, u;
	double solution;

	while(scanf("%d %d %d %d %d %d", &p, &q, &r, &s, &t, &u) > 0)
	{
		if(binarySearchSolution(p, q, r, s, t, u, &solution))
			printf("%.4lf\n", solution);
		else
			printf("No solution\n");
	}
	return 0;
}

int binarySearchSolution(int p, int q, int r, int s, int t, int u, double * solution)
{
	double leftX = 0, rightX = 1, midX;

	if(fabs(f(p, q, r, s, t, u, leftX)) < EPSILON)
	{
		*solution = leftX;
		return;
	}

	if(fabs(f(p, q, r, s, t, u, rightX)) < EPSILON)
	{
		*solution = rightX;
		return;
	}

	if(!(f(p, q, r, s, t, u, leftX) * f(p, q, r, s, t, u, rightX) < 0))
		return 0;

	while(!(leftX > rightX))
	{
		midX = (leftX + rightX) / 2.0;
		if(fabs(f(p, q, r, s, t, u, midX)) < EPSILON)
		{
			*solution = midX;
			return 1;
		}

		if(f(p, q, r, s, t, u, leftX) * f(p, q, r, s, t, u, midX) < 0)
			rightX = midX;
		else
			leftX = midX;
	}

	return 0;
}

double f(int p, int q, int r, int s, int t, int u, double x)
{
	return p * exp(-x) + q * sin(x) + r * cos(x) + s * tan(x) + t * x * x + u;
}
