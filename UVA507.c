/*******************************************************
 * Author: Nguyen Truong Duy
 *******************************************************/

/* Methodology:
 *  + This problem asks us to find the longest segment [i ... j] such that
 *      - The sum of A[i] + ... + A[j] is positive and maximal
 *  + Corner case: If all A[i] are negative, such [i ... j] does not exist.
 *
 *  + This problem is the maximum subarray problem.
 *    It can be solved in O(n) using Kadane's algorithm.
 */

#include <stdio.h>

const int MAX_SIZE = 20000;

void findLongestPositiveSubarr(int arr[], int mSize, int *maxStart, int *maxEnd);

int main(void)
{
    int numStop, arr[MAX_SIZE], T, caseId, i, mStart, mEnd;

    scanf("%d", &T);
    caseId = 1;

    while(caseId <= T)
    {
        scanf("%d", &numStop);

        for(i = 0; i < numStop - 1; i++)
            scanf("%d", &arr[i]);

        findLongestPositiveSubarr(arr, numStop - 1, &mStart, &mEnd);

        if(mStart < 0)
            printf("Route %d has no nice parts\n", caseId);
        else
            printf("The nicest part of route %d is between stops %d and %d\n",
                   caseId, mStart + 1, mEnd + 2);
        caseId++;
    }

    return 0;
}

void findLongestPositiveSubarr(int arr[], int mSize, int *maxStart, int *maxEnd)
{
    int sum = 0, maxSum = 0, curStart, curEnd, curLen, maxLen, i;

    *maxStart = -1;
    *maxEnd = -1;

    /* Corner case: arr contains negative numbers only */
    int hasPositive = 0;
    for(i = 0; i < mSize; i++)
        if(arr[i] > 0)
        {
            hasPositive = 1;
            break;
        }
    if(!hasPositive)
        return;

    for(curEnd = 0, curStart = 0; curEnd < mSize; curEnd++)
    {
        if(arr[curEnd] < 0)
        {
            curLen = (curEnd - 1) - curStart + 1;
            maxLen = (*maxEnd) - (*maxStart) + 1;

            if(sum > maxSum || (sum == maxSum && curLen > maxLen))
            {
                maxSum = sum;
                *maxStart = curStart;
                *maxEnd = curEnd - 1;
            }

        }

        /* If sum + arr[curEnd] = 0, still accept it because we want to
         *  find the longest maximal subarray.
         */
        if(sum + arr[curEnd] < 0)
        {
            curStart = curEnd + 1;
            sum = 0;
        }
        else
            sum += arr[curEnd];
    }

    curLen = (curEnd - 1) - curStart + 1;
    maxLen = (*maxEnd) - (*maxStart) + 1;
    if(sum > maxSum || (sum == maxSum && curLen > maxLen))
    {
        *maxStart = curStart;
        *maxEnd = curEnd - 1;
    }
}
