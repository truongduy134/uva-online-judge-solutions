/*******************************************************************************
 * Author: Nguyen Truong Duy
 ********************************************************************************/

/* Methodology:
 *	+ This is a very straight-forward problem with the constraint that the
 *		size of the array is at most 1000.
 *	+ Go through i from 1 to n - 1. For each i, count the number of j such that
 *		0 <= j < i and arr[j] <= arr[i].
 *
 *	+ Time complexity: O(n^2)
 */

#include <stdio.h>

const int MAX_SIZE = 1000;

int countNumLessThan(int arr[], int endInd);

int main(void)
{
	int T, mSize, arr[MAX_SIZE], i, sum;

	scanf("%d", &T);
	while(T)
	{
		scanf("%d", &mSize);

		for(i = 0; i < mSize; i++)
			scanf("%d", &arr[i]);

		sum = 0;
		for(i = 1; i < mSize; i++)
			sum += countNumLessThan(arr, i);

		printf("%d\n", sum);

		T--;
	}

	return 0;
}

/*
 * Count the number of arr[j] such that arr[j] <= arr[endInd] for
 *		all 0 <= j < endInd
 */
int countNumLessThan(int arr[], int endInd)
{
	int count = 0, i;

	for(i = 0; i < endInd; i++)
		if(arr[i] <= arr[endInd])
			count++;

	return count;
}
