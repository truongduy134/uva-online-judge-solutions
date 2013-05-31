/*******************************************************
 * Author: Nguyen Truong Duy
 *******************************************************/

/* Methodology:
 *  + Because the input array A contains non-negative integers, the minimum
 *      length sub-sequence B of A that has the maximum sum is obtained
 *      by removing redundant 0 from A.
 *  + Corner case: If A contains all zeroes, then the wanted sub-sequence is {0}
 *
 *  + Time complexity: O(N) where N is the size of A
 */

#include <stdio.h>

const int MAX_SIZE = 1000;

int filterZero(int arr[], int mSize, int positiveArr[]);

int main(void)
{
    int arr[MAX_SIZE], positiveArr[MAX_SIZE], mSize, mPositiveSize, i;

    while(1)
    {
        scanf("%d", &mSize);
        if(!mSize)
            break;

        for(i = 0; i < mSize; i++)
            scanf("%d", &arr[i]);

        mPositiveSize = filterZero(arr, mSize, positiveArr);

        if(mPositiveSize == 0)
        {
            printf("0\n");
        }
        else
        {
            for(i = 0; i < mPositiveSize; i++)
            {
                if(i > 0)
                    printf(" ");
                printf("%d", positiveArr[i]);
            }
            printf("\n");
        }
    }
    return 0;
}

int filterZero(int arr[], int mSize, int positiveArr[])
{
    int mPositiveSize = 0, i;

    for(i = 0; i < mSize; i++)
        if(arr[i] > 0)
        {
            positiveArr[mPositiveSize] = arr[i];
            mPositiveSize++;
        }

    return mPositiveSize;
}
