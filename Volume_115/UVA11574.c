#include <stdio.h>
#include <math.h>
#include <limits.h>

#define MAX_NUM_BOAT 1000

typedef struct {
	long double xCoord, yCoord, radAngle, velo;	
} Boat;

const long double PI = 2 * acos(0);
const long double INF = (const long double) LONG_MAX;
const long double EPS = 0.000000000000001;

long double square(long double x)
{
	return x * x;
}

long double computeSquareDistance(Boat * one, Boat * two)
{
	return square(one->xCoord - two->xCoord) + square(one->yCoord - two->yCoord); 
}

long double roundToNearestInteger(long double x)
{
	return floor(x + 0.5);
}

long double computeMinTimeBeforeCollide(Boat * one, Boat * two, long double collideDist)
{
	long double A, B, C, delta, lowerBound;

	C = computeSquareDistance(one, two) - square(collideDist);
	/* If the two boats are already within (strictly less than) the collide distance, return 0 */
	if(C < 0)
		return 0;
	
	A = square(one->velo) - 2.0 * one->velo * two->velo * (cos(one->radAngle) * cos(two->radAngle) + sin(one->radAngle) * sin(two->radAngle)) + square(two->velo);

	B = (one->xCoord - two->xCoord) * (one->velo * sin(one->radAngle) - two->velo * sin(two->radAngle)) + (one->yCoord - two->yCoord) * (one->velo * cos(one->radAngle) - two->velo * cos(two->radAngle));
	
	/* The original problem: Finding the number of seconds (rounded to the nearest integer) before the two boats collide.
	 *
	 * This is equivalent to finding largest postive integer t such that
	 *		A * t^2 + 2 * B * t + C >= 0 where (A, C > 0)
	 *	and there exists t' > t such that A * (t')^2 + 2 * B * (t') + C < 0
	 *
 	 * Solution:
	 * 	+ delta = B^2 - A * C.
 	 * 	+ If delta >= 0, A * x^2 + 2 * B * x + C >= 0 for all x. Hence, t -> INFINITY.
	 *
	 *	+ If delta < 0, let x1, x2 (x1 < x2) be the two roots. Then
	 *		A * x^2 + 2 * B * x + C < 0 iff x1 < x < x2
 	 *
	 *	  If x1 < 0, x2 < 0 (because A, C > 0); hence, A * x^2 + 2 * B * x + C >= 0 for all x >= 0. Hence, t -> INFINITY as well.
	 *
	 *	+ Otherwise, t = the nearest integer of x1. And x1 can be computed by 
	 *		(-B - sqrt(delta)) / A
	 */
	delta = square(B) - A * C;

	if(delta < EPS)
		return INF;
	
	lowerBound = roundToNearestInteger((-B - sqrt(delta)) / A);

	/* If x1 < 0 (strictly negative) */
	if(lowerBound < 0)
		return INF;

	return lowerBound;	
} 

long double convertToRadFromDegree(long double degree)
{
	return degree * PI / 180;
}

long double determineMinTimeBeforeCollide(Boat boatList[], int numBoat, long double collideDistance);

int main(void)
{
	int T, numBoat, i;
	long double minTime, collideDistance, degree;
	Boat boatList[MAX_NUM_BOAT];

	scanf("%d", &T);
	
	while(T)
	{
		scanf("%d %Lf", &numBoat, &collideDistance);
		
		for(i = 0; i < numBoat; i++)
		{
			scanf("%Lf %Lf %Lf %Lf", &boatList[i].xCoord, &boatList[i].yCoord,
					&degree, &boatList[i].velo);
			boatList[i].radAngle = convertToRadFromDegree(degree);
		}

		minTime = determineMinTimeBeforeCollide(boatList, numBoat, collideDistance);
		if(fabs(minTime - INF) < EPS)
			printf("No collision.\n");
		else				
			printf("%.0Lf\n", minTime);

		T--;
	}
	
	return 0;
}

long double determineMinTimeBeforeCollide(Boat boatList[], int numBoat, long double collideDistance)
{
	long double minTime = INF, minTimeCollide;
	int i, j;

	for(i = 0 ; i < numBoat; i++)
		for(j = i + 1; j < numBoat; j++)
		{
			minTimeCollide = computeMinTimeBeforeCollide(&boatList[i], &boatList[j], collideDistance);
			if(minTimeCollide < EPS)
				return 0;

			if(minTimeCollide < minTime)
				minTime = minTimeCollide;
		}

	return minTime;
}
