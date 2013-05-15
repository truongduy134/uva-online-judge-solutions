/************************************************************
 * Author: Nguyen Truong Duy
 ************************************************************/
#include <stdio.h>

/*
 * Methodology:
 *	+ Let k be the strength factor.
 *	+ Let h be the maximum height difference between 2 consecutive rungs.
 *	+ Clearly, k >= h.
 *	  When k = h + 1, clearly we can reach the top (the strength factor
 *		will remain the same during the process)
 *	+ Therefore, min k = h if we can reach the top successfully with strength factor as h.
 *		     min k = h + 1
 *	+ Time complexity: O(n)
 */

#define MAX_SIZE 100001

int determineMinStrengthFactor(int heightArr[], int mSize);
int simulateProcess(int heightArr[], int mSize, int strength);

int main(void)
{
	int heightArr[MAX_SIZE], mSize, T, caseId, i;

	scanf("%d", &T);
	caseId = 1;
	while(caseId <= T)
	{
		scanf("%d", &mSize);
		mSize++;	/* Include the ground */

		heightArr[0] = 0;
		for(i = 1; i < mSize; i++)
			scanf("%d", &heightArr[i]);

		printf("Case %d: %d\n", caseId, determineMinStrengthFactor(heightArr, mSize));
		caseId++;
	}

	return 0;
}

int determineMinStrengthFactor(int heightArr[], int mSize)
{
	int maxDiff = 0, i, diff;

	for(i = 1; i < mSize; i++)
	{
		diff = heightArr[i] - heightArr[i - 1];
		if(diff > maxDiff)
			maxDiff = diff;
	}

	if(simulateProcess(heightArr, mSize, maxDiff))
		return maxDiff;
	return maxDiff + 1;
}

int simulateProcess(int heightArr[], int mSize, int strength)
{
	int diff, i;

	for(i = 1; i < mSize; i++)
	{
		diff = heightArr[i] - heightArr[i - 1];

		if(diff > strength)
			return 0;
		if(diff == strength)
			strength--;
	}

	return 1;
}
