#include <stdio.h>
#include <math.h>

/* Methodology:
 *	+ Let A, B, C denote the area of a single piece of the crossed, dotted and
 *			striped region.
 *	+ Then we have
 *		4A + 4B + C = a^2
 *		2A + 3B + C = PI * a^2 / 4
 *
 *	+ Using the integration to find the area under the curve, we have
 *		A / 2 = integration(0 <= x <= a / 2) (a - sqrt(a^2 - x^2) dx
 *
 *	  Computing this, we have A = a^2 (1 - sqrt(3) / 4 - PI / 6)
 *
 *	+ Then B = a^2 (sqrt(3) / 2 - 1 + PI / 12)
 *	       C = a^2 (1 - sqrt(3) + PI / 3)
 *
 *	+ Final results: C = a^2 (1 - sqrt(3) + PI / 3)
 *			4B = a^2 (2 * sqrt(3) - 4 + PI / 3)
 *			4A = a^2 (4 - sqrt(3) - 2 * PI / 3)
 */
int main(void)
{
	const double PI = 2 * acos(0);
	const double SQUARE_ROOT_THREE = sqrt(3);

	double squareSide, stripedArea, dottedArea, rest, squareArea;

	while(scanf("%lf", &squareSide) > 0)
	{
		squareArea = squareSide * squareSide;
		stripedArea = squareArea * (1 - SQUARE_ROOT_THREE + PI / 3.0);
		dottedArea = squareArea * (2 * SQUARE_ROOT_THREE - 4 + PI / 3.0);
		rest = squareArea - stripedArea - dottedArea;

		printf("%.3lf %.3lf %.3lf\n", stripedArea, dottedArea, rest);
	}
	return 0;	
}
