#include <stdio.h>
#include <math.h>

/* Formula:
 *	If h - l * tan(radianTheta) > 0
 *		The bottle is more than half full
 *	Else
 *		The bottle is more than half empty
 *
 *	If the bottle is more than half full
 *		Remaining soya milk = w * l * (h - 1/2 * l * tan (theta * PI / 180) )
 *	Else
 *		Remaining soya milk = 1/2 * w * h * h * tan (PI / 2 - theta * PI / 180)
 * where theta is in degrees.
 */
#define PI 3.141592654
int main(void)
{
	int w, l, h, theta, isMoreHalfFull; 
	double temp, volume, radianTheta;
	
	while(scanf("%d %d %d %d", &l, &w, &h, &theta) > 0)
	{
		radianTheta = theta * PI / 180;

		if(h - l * tan(radianTheta) > 0)
			isMoreHalfFull = 1;
		else
			isMoreHalfFull = 0;
		
		if(isMoreHalfFull)
			volume = w * l * (h - l * tan(radianTheta) / 2);
		else
			volume = w * h * h * tan(PI / 2 - radianTheta) / 2;

		printf("%.3lf mL\n", volume); 
	}
	return 0;
} 
