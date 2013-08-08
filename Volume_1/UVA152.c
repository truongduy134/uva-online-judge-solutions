/*******************************************************************************
 * Author: Nguyen Truong Duy
 ********************************************************************************/

/* Methodology
 *	+ We can use the O(n^2) straightforward algorithm to solve this problem.
 */

#include <stdio.h>
#include <math.h>

typedef struct
{
	double x, y, z;
} Point3D;

double computeDistance(Point3D * one, Point3D * two)
{
	return sqrt((one->x - two->x) * (one->x - two->x) 
		  + (one->y - two->y) * (one->y - two->y)
		  + (one->z - two->z) * (one->z - two->z));
}

#define THRESHOLD 0.0000000000001
#define INF 1000000000.0
#define MAX_NUM_POINT 5000
#define NUM_CATEGORY 10

void countPointInCategory(Point3D arr[MAX_NUM_POINT], int numPoint, int categoryCount[NUM_CATEGORY]);

int main(void)
{
	Point3D arr[MAX_NUM_POINT];
	int categoryCount[NUM_CATEGORY], numPoint;
	double x, y, z;

	numPoint = 0;
	while(1)
	{
		scanf("%lf %lf %lf", &x, &y, &z);
		if(x < THRESHOLD && y < THRESHOLD && z < THRESHOLD)
			break;
		arr[numPoint].x = x;
		arr[numPoint].y = y;
		arr[numPoint].z = z;
		numPoint++;
	}
	
	countPointInCategory(arr, numPoint, categoryCount);

	int i;
	for(i = 0; i < NUM_CATEGORY; i++)
		printf("%4d", categoryCount[i]);
	printf("\n");

	return 0;
}

void countPointInCategory(Point3D arr[MAX_NUM_POINT], int numPoint, int categoryCount[NUM_CATEGORY])
{
	int i, j, unitMeasure;
	double minDistance[MAX_NUM_POINT], dist;

	for(i = 0; i < NUM_CATEGORY; i++)
		categoryCount[i] = 0;
	for(i = 0; i < numPoint; i++)
		minDistance[i] = INF;

	for(i = 0; i < numPoint; i++)
		for(j = i + 1; j < numPoint; j++)
		{
			dist = computeDistance(&arr[i], &arr[j]);
			if(dist < minDistance[i])
				minDistance[i] = dist;
			if(dist < minDistance[j])
				minDistance[j] = dist;
		}

	for(i = 0; i < numPoint; i++)
		for(unitMeasure = 1; unitMeasure <= NUM_CATEGORY; unitMeasure++)
			if(minDistance[i] < (double) unitMeasure)
			{
				categoryCount[unitMeasure - 1]++;
				break;
			}
}
