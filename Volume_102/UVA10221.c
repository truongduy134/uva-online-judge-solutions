#include <stdio.h>
#include <math.h>
#include <string.h>

const double PI = acos(-1);
const int DEG_TO_MIN = 60;
const double EARTH_RADIUS = 6440;

#define DEG "deg"
#define MAX_LEN 10

double convertFromMinToDeg(double min);
double convertFromDegToRad(double deg);
double computeArcDist(double radius, double deg);
double computeChordDist(double radius, double deg);

/* Important note:
 *	+ The input angle alpha can be larger than 180 degree.
 *	+ In that case, we must consider the smaller angle (360 - alpha) to
 *		determine the distances.
 */
int main(void)
{
	double dist, angle, realRadius;
	char typeAngle[MAX_LEN + 1];

	while(scanf("%lf %lf %s", &dist, &angle, typeAngle) > 0)
	{
		if(strcmp(typeAngle, DEG) != 0)
			angle = convertFromMinToDeg(angle);

		if(angle > 180)
			angle = 360 - angle;

		realRadius = EARTH_RADIUS + dist;

		printf("%.6lf %.6lf\n", computeArcDist(realRadius, angle),
					computeChordDist(realRadius, angle)); 
	}
	return 0;
}

double convertFromMinToDeg(double min)
{
	return min / DEG_TO_MIN; 
}

double convertFromDegToRad(double deg)
{
	return PI * deg / 180;
}
/* 360 degree corresponding to 2 * PI * R arc distance */
double computeArcDist(double radius, double deg)
{
	return 2 * PI * radius * deg / 360.0;
}

double computeChordDist(double radius, double deg)
{
	double rad = convertFromDegToRad(deg);

	return 2.0 * radius * sin(rad / 2);
}
