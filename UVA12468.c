#include <stdio.h>

#define MAX_CHANNEL 99

int main(void)
{
	int start, end, temp, minPress;

	while(1)
	{
		scanf("%d %d", &start, &end);
		if(start < 0 && end < 0)
			break;
		
		if(start > end)
		{
			temp = start;
			start = end;
			end = temp;
		}

		minPress = end - start;		/* Go from start -> end */
		/* Second way: go from start -> 0 -> MAX_CHANNEL -> end */
		temp = start + 1 + (MAX_CHANNEL - end);
		if(temp < minPress)
			minPress = temp;

		printf("%d\n", minPress);
	}
	return 0;
}
