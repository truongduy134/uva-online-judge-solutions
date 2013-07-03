/*******************************************************
 * Author: Nguyen Truong Duy
 *******************************************************/

/* Methodology:
 *  + This problem asks us to compute the number of inversions in the input array.
 *
 *  + We can modify merge sort so that we can count the number of inversions while we do the sorting.
 *  + High-level description:
 *      - Base case: When the array has 1 element or empty, there is no inversion.
 *      - The number of inversion = the number of inversions in the left half + that of the right half +
 *              the number of inversions when we merge the two subarray.
 *
 *      - For each element A[indL] in the left half sorted subarray such that A[indL] > A[indR] (A[indR] is
 *              some value in the right half sorted subarray), it creates (sizeL - indL + 1) inversions
 *              where sizeL is the size of the left half sorted subarray.
 *  + Time complexity: O(n log n)
 *
 *  + NOTE: Since the number of inversions can be O(n^2) and n can be as large as 500000, we should
 *              use 64-bit signed integer to store the number of inversions.
 */

#include <stdio.h>

const int MAX_SIZE = 500000;

long long int mergeSortAndCountInversion(int arr[], int left, int right);
long long int mergeAndCountInversion(int arr[], int left, int mid, int right);

int main(void)
{
    int mSize, arr[MAX_SIZE], i;

    while(1)
    {
        scanf("%d", &mSize);
        if(!mSize)
            break;

        for(i = 0; i < mSize; i++)
            scanf("%d", &arr[i]);

        printf("%lld\n", mergeSortAndCountInversion(arr, 0, mSize - 1));
    }
    return 0;
}

long long int mergeSortAndCountInversion(int arr[], int left, int right)
{
    if(left >= right)
        return 0;

    int mid = left + ((right - left) >> 1);
    long long int numInversion;

    numInversion = mergeSortAndCountInversion(arr, left, mid);
    numInversion += mergeSortAndCountInversion(arr, mid + 1, right);
    numInversion += mergeAndCountInversion(arr, left, mid, right);

    return numInversion;
}

/* Merge two sorted array arr[left ... mid] and arr[mid + 1 ... right] */
long long int mergeAndCountInversion(int arr[], int left, int mid, int right)
{
    int tempArr[MAX_SIZE], mSize = 0, i;

    long long int numInversion = 0;

    int indL = left, indR = mid + 1;

    while(indL <= mid && indR <= right)
    {
        if(arr[indL] <= arr[indR])
        {
            /* No inversion */
            tempArr[mSize] = arr[indL];
            indL++;
            mSize++;
        }
        else
        {
            /* (arr[i], arr[indR]) is an inversion for all i = indL ... mid
             * So there are right - indR + 1 inversions
             */
             numInversion += mid - indL + 1;
             tempArr[mSize] = arr[indR];
             indR++;
             mSize++;
        }
    }

    while(indL <= mid)
    {
        tempArr[mSize] = arr[indL];
        indL++;
        mSize++;
    }
    while(indR <= right)
    {
        tempArr[mSize] = arr[indR];
        indR++;
        mSize++;
    }

    for(i = 0; i < mSize; i++)
        arr[left + i] = tempArr[i];

    return numInversion;
}
