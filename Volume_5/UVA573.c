#include <stdio.h>

int main(void)
{
	int maxHeight, height, upDist, decDist, fatigueFactor, downDist, day;

	while(1)
	{
		scanf("%d", &maxHeight);
		if(!maxHeight)
			break;

		scanf("%d %d %d", &upDist, &downDist, &fatigueFactor);
		
		maxHeight *= 100;
		upDist *= 100;
		downDist *= 100;
		decDist = fatigueFactor * upDist / 100;

		day = 0;
		height = 0;
		while(height >= 0 && height <= maxHeight)
		{
			day++;
			/* During the day */
			height += upDist;
			if(height > maxHeight)
				break;

			/* During the night */
			height -= downDist;

			upDist -= decDist;
			if(upDist < 0)
				upDist = 0;
		}

		if(height < 0)
			printf("failure on day %d\n", day);
		else
			printf("success on day %d\n", day);
	}
	return 0;
}
