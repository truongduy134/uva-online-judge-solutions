/*
 * UVA 10327: Flip Sort
 *
 * Flip operation: to exchange two adjacent elements.
 *
 * Input:
 *  + There will be multiple test cases.
 *  + Each test case starts with a positive integer N (N < 1000), followed by N integers.
 *  + Input will be terminated by EOF.
 *
 * Output:
 *  + Print "Minimum exchange operations : M" where M is the minimum flip operations required to
 *      perform sorting an array in ascending order.
 *  + Use a seperate line for each case.
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX 1000

int countMinNumFlipByInsertionSort(int [], int);
int countMinNumFlipByInversion(int [], int);

int main()
{
    int lenArr, arr[MAX], index;

    while(scanf("%d", &lenArr) > 0)
    {
        for(index = 0; index < lenArr; index++)
            scanf("%d", &arr[index]);

        /* Ouput for each test case */
        printf("Minimum exchange operations : %d\n", countMinNumFlipByInversion(arr, lenArr));
    }

    return 0;
}

/*
 * Count the minimum number of flip operations to sort the input array in ascending order.
 *
 * Note that the minimum number of flips operations to sort the input array in ascending order is
 * EQUAL to the number of inversions in the array.
 *
 * Input:
 *  + arr: an array of integers.
 *  + len: the number of elements in the input array.
 *
 * Output:
 *  + minNumFlip: the minimum number of flip operations to sort the input array in ascending order.
 *
 * Assumption: inputs are correct (e.g. arr != null and len >= 1)
 *
 * Methodology:
 *  + Count the number of inversions.
 *
 * Time complexity: O(N^2) where N is the length of the array. This can be done in O(N * logN) using
 *      MergeSort.
 */
int countMinNumFlipByInversion(int arr[], int len)
{
    int minNumFlip = 0, i, j;

    for(i = 0; i < len - 1; i++)
        for(j = i + 1; j < len; j++)
            if(arr[i] > arr[j])
                minNumFlip++;

    return minNumFlip;
}

/*
 * Count the minimum number of flip operations to sort the input array in ascending order.
 *
 * Input:
 *  + arr: an array of integers.
 *  + len: the number of elements in the input array.
 *
 * Output:
 *  + minNumFlip: the minimum number of flip operations to sort the input array in ascending order.
 *
 * Assumption: inputs are correct (e.g. arr != null and len >= 1)
 *
 * Methodology:
 *  + Use Insertion Sort to sort the input array in ascending order.
 *  + Count the number of flip operations used by Insertion Sort.
 *
 * Time complexity: O(N^2) where N is the length of the array.
 */
int countMinNumFlipByInsertionSort(int arr[], int len)
{
    int minNumFlip = 0, maxSortedIndex, curEleIndex, curEle;


    for(maxSortedIndex = 0; maxSortedIndex < len - 1; maxSortedIndex++)
    {
        curEleIndex = maxSortedIndex;
        curEle = arr[curEleIndex + 1];

        while(curEleIndex >= 0 && arr[curEleIndex] > curEle)
        {
            arr[curEleIndex + 1] = arr[curEleIndex];
            curEleIndex--;

            /* Increment the flip counter */
            minNumFlip++;
        }

        arr[curEleIndex + 1] = curEle;
    }

    return minNumFlip;
}
