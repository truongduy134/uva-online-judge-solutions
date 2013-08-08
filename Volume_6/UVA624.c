/*******************************************************************************
 * Author:  Nguyen Truong Duy
 *******************************************************************************/ 

/* Methodology:
 *	+ Since the input is small (the number of tracks is at most 20), we can use
 *	brute force approach, i.e. examining all 2^20 (without memoization) and then
 *	choosing the best subset
 */
#include <stdio.h>

const int MAX_NUM_TRACK = 20;

int chooseSubsetToFillTapeBest(int totalDuration, int durationArr[], int numTrack, int subsetDurationArr[]);
int getArrSum(int arr[], int size);
int chooseSubsetToFillTapeBest(int totalDuration, int durationArr[], int numTrack, int subsetDurationArr[]);
int getSumFromBitmask(int bitmask, int set[], int sizeSet);
int retrieveSubsetFromBitmask(int bitmask, int set[], int sizeSet, int subSet[]);

int main(void)
{
	int totalDuration, numTrack, durationArr[MAX_NUM_TRACK],
		subsetSize, subsetDurationArr[MAX_NUM_TRACK], i;

	while(scanf("%d", &totalDuration) > 0)
	{
		scanf("%d", &numTrack);

		for(i = 0; i < numTrack; i++)
			scanf("%d", &durationArr[i]);

		subsetSize = chooseSubsetToFillTapeBest(totalDuration, durationArr, numTrack, subsetDurationArr);

		for(i = 0; i < subsetSize; i++)
			printf("%d ", subsetDurationArr[i]);
		printf("sum:%d\n", getArrSum(subsetDurationArr, subsetSize));
	}
	return 0;
}

int getArrSum(int arr[], int size)
{
	int i, sum;

	for(i = 0, sum = 0; i < size; i++)
		sum += arr[i];

	return sum;
}

int chooseSubsetToFillTapeBest(int totalDuration, int durationArr[], int numTrack, int subsetDurationArr[])
{
	int bitmask = 0, minNotFill = totalDuration, bestBitmask, notFill, bestSubsetSize;

	for(bitmask = 1; bitmask < (1 << numTrack); bitmask++)
	{
		notFill = totalDuration - getSumFromBitmask(bitmask, durationArr, numTrack);
		if(notFill >= 0 && notFill < minNotFill)
		{
			bestBitmask = bitmask;
			minNotFill = notFill;
		}
	}

	bestSubsetSize = retrieveSubsetFromBitmask(bestBitmask, durationArr, numTrack, subsetDurationArr);

	return bestSubsetSize;
}

int retrieveSubsetFromBitmask(int bitmask, int set[], int sizeSet, int subSet[])
{
	int ind, sizeSubset = 0;

	for(ind = 0; ind < sizeSet; ind++)
		if(bitmask & (1 << ind))
		{
			subSet[sizeSubset++] = set[ind];
		}

	return sizeSubset;
}

int getSumFromBitmask(int bitmask, int set[], int sizeSet)
{
	int ind, sum = 0;

	for(ind = 0; ind < sizeSet; ind++)
		if(bitmask & (1 << ind))
			sum += set[ind];

	return sum;
}
