/********************************************************************************
 * WhatIsTheMedian.c
 *
 * UVA Problem ID: 10107 (What is the median?)
 *
 * Input:
 * 	+ The input consists of a series of integers X (0 <= X < 2^31).
 *    The total number of integers is less than 10^5.
 *  + The input is terminated by EOF.
 *
 * Output: For each input, print the current median of the set of integers.
 *
 * Definition:
 * 	+ Consider the SORTED array of integers A[0 ... N - 1]
 *  + If N is odd, then the median of A will be Y = A[(N - 1) / 2].
 *  + If N is even, then the median of A will be Y = (A[N / 2] + A[N / 2 + 1]) / 2
 *    In this problem, we only care the integral part of Y.
 *    Thus, if N is even, then the median of A will be
 *    		Y = floor((A[N / 2] + A[N / 2 - 1]) / 2)
 ********************************************************************************/

#include <stdio.h>
#define MAX 10000

/*******************************************************************************
 * Building the MinHeap data structure:
 *******************************************************************************/
typedef struct
{
	long int arr[MAX], heapSize;
} MinHeap;

long int parentIndex(long int index)
{
	return (index >> 1);
}

long int leftChildIndex(long int index)
{
	return (index << 1);
}

long int rightChildIndex(long int index)
{
	return (index << 1) + 1;
}

void initializeMinHeap(MinHeap *A)
{
	A->heapSize = 0;
}

void MinHeapify(MinHeap *A, long int index)
{
	long int currentIndex = index, minIndex, temp, left, right;

	while(1)
	{
		minIndex = currentIndex;
		left = leftChildIndex(currentIndex);
		right = rightChildIndex(currentIndex);

		/* Find the index of the minimum element */
		if(left <= A->heapSize && A->arr[left] < A->arr[minIndex])
			minIndex = left;
		if(right <= A->heapSize && A->arr[right] < A->arr[minIndex])
			minIndex = right;

		if(minIndex != currentIndex)
		{
			/* Swap the two elements */
			temp = A->arr[minIndex];
			A->arr[minIndex] = A->arr[currentIndex];
			A->arr[currentIndex] = temp;

			currentIndex = minIndex;
		}
		else
			break;
	}
}

int isEmptyMinHeap(MinHeap *A)
{
	if(A->heapSize == 0)
		return 1;
	return 0;
}

long int extractMinHeap(MinHeap *A)
{
	/* We assume that we never call the function when the heap is empty */
	long int min = A->arr[1];

	A->arr[1] = A->arr[A->heapSize];
	(A->heapSize)--;
	MinHeapify(A, 1);

	return min;
}

long int peekMinHeap(MinHeap *A)
{
	return A->arr[1];	/* Note that we use 1-indexing */
}

void decreaseKeyMinHeap(MinHeap *A, long int index, long int key)
{
	long int currentIndex = index, temp, parent;

	/* If the new key is larger than the old key, we do nothing */
	if(key <= A->arr[index])
	{
		A->arr[index] = key;

		while(currentIndex > 1 && A->arr[(parent = parentIndex(currentIndex))] >
								  A->arr[currentIndex])
		{
			/* Swap the two elements */
			temp = A->arr[currentIndex];
			A->arr[currentIndex] = A->arr[parent];
			A->arr[parent] = temp;

			currentIndex = parent;
		}
	}
}

void insertMinHeap(MinHeap *A, long int key)
{
	(A->heapSize)++;
	A->arr[A->heapSize] = key;
	decreaseKeyMinHeap(A, A->heapSize, key);
}

/********************************************************************************
 * Building the MaxHeap data structure:
 ********************************************************************************/
typedef struct
{
	MinHeap A;
} MaxHeap;

void initializeMaxHeap(MaxHeap *M)
{
	initializeMinHeap(&(M->A));
}

void insertMaxHeap(MaxHeap *M, long int key)
{
	insertMinHeap(&(M->A), -key);
}

long int extractMaxHeap(MaxHeap *M)
{
	return -extractMinHeap(&(M->A));
}

int isEmptyMaxHeap(MaxHeap *M)
{
	return isEmptyMinHeap(&(M->A));
}

long int peekMaxHeap(MaxHeap *M)
{
	return -peekMinHeap(&(M->A));
}

/*******************************************************************************
 * Building MedianOnline Data Structure:
 *******************************************************************************/
typedef struct
{
	MaxHeap Max;
	MinHeap Min;
	long int size;
} MedianOnline;

void initializeMedianOnline(MedianOnline *S)
{
	initializeMaxHeap(&(S->Max));
	initializeMinHeap(&(S->Min));
	S->size = 0;
}

void insertMedianOnline(MedianOnline *S, long int key)
{
	long int temp, max, min;

	insertMaxHeap(&(S->Max), key);
	if((S->Max).A.heapSize > (S->Min).heapSize)
	{
		temp = extractMaxHeap(&(S->Max));
		insertMinHeap(&(S->Min), temp);
	}
	if((S->Max).A.heapSize == (S->Min).heapSize)
	{
		if(peekMaxHeap(&(S->Max)) > peekMinHeap(&(S->Min)))
		{
			max = extractMaxHeap(&(S->Max));
			min = extractMinHeap(&(S->Min));
			insertMinHeap(&(S->Min), max);
			insertMaxHeap(&(S->Max), min);
		}
	}
	(S->size)++;
}

long int queryMedian(MedianOnline *S)
{
	if((S->size & 1) == 0)	/* The number of elements is even */
		return (peekMaxHeap(&(S->Max)) + peekMinHeap(&(S->Min))) >> 1;
	else
		return peekMinHeap(&(S->Min));
}

int main(void)
{
	long int newElement;
	MedianOnline mySystem;

	/* Initialization */
	initializeMedianOnline(&mySystem);

	while(scanf("%ld", &newElement) > 0)
	{
		insertMedianOnline(&mySystem, newElement);
		printf("%ld\n", queryMedian(&mySystem));
	}

	return 0;
}
