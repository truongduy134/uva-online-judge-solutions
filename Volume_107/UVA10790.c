/*******************************************************************************
 * Author: Nguyen Truong Duy
 ********************************************************************************/

/* Methodology:
 *	+ Let P(a, b) be the maximum number of intersections between row 1 with a points
 *		and row 2 with b points.
 *
 *	+ Key observation: Choose any two points A1, A2 on row 1 and any two points
 *		B1, B2 on row 2.
 *	  By connecting A1 and B2, B1 and A2 (assuming A2 is to the right of A1, and
 *		B2 is to the right of B1), then we have an intersection.
 *	+ Therefore, we have a formula for P(a, b):
 *		P(a, b) = (a C 2) * (b C 2)
 *			= (a * (a - 1) * b * (b - 1)) / 4
 */

#include <stdio.h>

int main(void)
{
	unsigned long long int a, b, maxNumIntersection;
	int caseId = 1;

	while(1)
	{
		scanf("%llu %llu", &a, &b);
		if(a == 0 && b == 0)
			break;

		maxNumIntersection = ((a * (a - 1)) >> 1) * ((b * (b - 1)) >> 1);
		printf("Case %d: %llu\n", caseId, maxNumIntersection);
		caseId++;
	}

	return 0;
}
