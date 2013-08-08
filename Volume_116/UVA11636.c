#include <stdio.h>

#define MAX_NUM 10001

/* arr[i] = k where k is the smallest natural number such that
 *	2 ^ k >= N */
void prepareNearestPowerOfTwoSieve(int arr[])
{
	int n = 0, power = 1, exponent = 0;

	for(n = 0; n < MAX_NUM; n++)
	{
		if(n > power)
		{
			power <<= 1;
			exponent++;
		}

		arr[n] = exponent;
	}
}

int main(void)
{
	int caseId = 1, numLine, nearestPowerOfTwoArr[MAX_NUM];

	prepareNearestPowerOfTwoSieve(nearestPowerOfTwoArr);

	while(1)
	{
		scanf("%d", &numLine);
		if(numLine < 0)
			break;

		/* The minimum number of pastes to have N lines
		 * is K where K is the smallest number such that
		 * 2 ^ K >= N */
		printf("Case %d: %d\n", caseId, nearestPowerOfTwoArr[numLine]); 
		caseId++;
	}

	return 0;
}
