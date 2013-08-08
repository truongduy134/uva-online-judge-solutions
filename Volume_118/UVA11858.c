/*****************************************************************************
 * Author: Nguyen Truong Duy
 *****************************************************************************/
#include <stdio.h>

/* Methodology:
 *	+ The problem requires to compute the number of inversions in an array.
 *	+ We will modify merge sort to compute the number of inversions in O(n log n)
 */

#define MAX_SIZE 1000000

long long int mergeAndCountInversion(int arr[], int start, int mid, int end);
long long int mergeSortAndCountInversion(int arr[], int start, int end);

int main(void)
{
	int arr[MAX_SIZE], mSize, i;

	while(scanf("%d", &mSize) > 0)
	{
		for(i = 0; i < mSize; i++)
			scanf("%d", &arr[i]);

		printf("%lld\n", mergeSortAndCountInversion(arr, 0, mSize - 1));
	}

	return 0;
}

long long int mergeSortAndCountInversion(int arr[], int start, int end)
{
	int temp, mid;
	long long int inversionLeft, inversionRight, inversionMerge;

	if(end <= start)
		return 0;

	if(end - start == 1)
	{
		if(arr[start] > arr[end])
		{
			temp = arr[start];
			arr[start] = arr[end];
			arr[end] = temp;
			return 1;
		}

		return 0;
	}

	mid = start + ((end - start) >> 1);
	
	inversionLeft = mergeSortAndCountInversion(arr, start, mid);
	inversionRight = mergeSortAndCountInversion(arr, mid + 1, end);
	inversionMerge = mergeAndCountInversion(arr, start, mid, end);
	return inversionLeft + inversionRight + inversionMerge;
}

/*
 * Merge two sorted arrays arr[start ... mid] and arr[mid + 1 ... end]
 *	into 1 sorted array AND count the number of inversions.
 */
long long int mergeAndCountInversion(int arr[], int start, int mid, int end)
{
	int tempArr[MAX_SIZE], indTemp, leftInd, rightInd;
	long long int numInversion = 0;

	indTemp = 0;
	leftInd = start;
	rightInd = mid + 1;

	while(leftInd <= mid && rightInd <= end)
	{
		if(arr[leftInd] <= arr[rightInd])
		{
			/* No inversion */
			tempArr[indTemp] = arr[leftInd];
			indTemp++;
			leftInd++;
		}
		else
		{
			/* Number of inversion equals to the current remaining size of
			 * the left sub-array */
			numInversion += (mid - leftInd + 1);
			
			/* Sort */
			tempArr[indTemp] = arr[rightInd];
			indTemp++;
			rightInd++;
		}
	}

	while(leftInd <= mid)
	{
		tempArr[indTemp] = arr[leftInd];
		indTemp++;
		leftInd++;
	}
	while(rightInd <= end)
	{
		tempArr[indTemp] = arr[rightInd];
		indTemp++;
		rightInd++;
	}

	/* Copy back */
	for(leftInd = start, indTemp = 0; leftInd <= end; leftInd++, indTemp++)
		arr[leftInd] = tempArr[indTemp];

	return numInversion;
}
