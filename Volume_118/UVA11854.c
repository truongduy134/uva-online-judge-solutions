#include <stdio.h>

#define MAX_SIDE 3

int main(void)
{
	long long int side[3], maxSide, sum;
	int i;

	while(1)
	{
		for(i = 0; i < MAX_SIDE; i++)
			scanf("%lld", &side[i]);

		if(side[0] == 0 && side[1] == 0 && side[2] == 0)
			break;

		maxSide = 0;
		for(i = 1; i < MAX_SIDE; i++)
			if(side[maxSide] < side[i])
				maxSide = i;

		sum = 0;
		for(i = 0; i < MAX_SIDE; i++)
			if(i != maxSide)
				sum += side[i] * side[i];

		if(sum == side[maxSide] * side[maxSide])
			printf("right\n");
		else
			printf("wrong\n");
	}

	return 0;
}
