/*******************************************************
 * Author: Nguyen Truong Duy
 *******************************************************/

/* Methodology:
 *  + Let T be the difference table constructed using the original array.
 *    Clearly T will have n columns where n is the size of the original array.
 *  + Let M be an 1 x n array such that M[i] = the last element in column i of T.
 *  + We can construct M using an O(n^2) straightforward algorithm.
 *
 *  + To add a new element (extrapolation) to the sequence, we perform
 *          M[i] = M[i] + M[i + 1]
 *    The new element is M[0].
 *  + To add the second new element, perform similar procedure on the updated array M obtained
 *      after finding the previous added element.
 *
 *  + Time complexity: O(n^2 + n * k) where k is the number of elements added.
 */

#include <stdio.h>

const int MAX_SIZE = 10;

int findLastAddEle(int lastDiffRow[], int mSize, int numAdd);
void getLastDiffRow(int arr[MAX_SIZE], int mSize, int lastDiffRow[MAX_SIZE]);

int main(void)
{
        int arr[MAX_SIZE], lastDiffRow[MAX_SIZE];
        int mSize, numAdd, ind;

        while(1)
        {
            scanf("%d", &mSize);
            if(!mSize)
                break;

            for(ind = 0; ind < mSize; ind++)
                scanf("%d", &arr[ind]);
            scanf("%d", &numAdd);

            /* Find the last row in the difference table of the original array */
            getLastDiffRow(arr, mSize, lastDiffRow);

            printf("Term %d of the sequence is %d\n", mSize + numAdd,
                   findLastAddEle(lastDiffRow, mSize, numAdd));
        }

        return 0;
}

 /* Find the last row in the difference table of the original array, i.e.
  *     lastDiffRow[i] = the last element in the i-th column of the difference table
  *         built on the original arr
  */
void getLastDiffRow(int arr[MAX_SIZE], int mSize, int lastDiffRow[MAX_SIZE])
{
    int diffSize = mSize, ind, curCol;

    curCol = 0;
    while(diffSize)
    {
        lastDiffRow[curCol] = arr[diffSize - 1];
        curCol++;

        for(ind = 0; ind < mSize - 1; ind++)
            arr[ind] = arr[ind + 1] - arr[ind];
        diffSize--;
    }
}

int findLastAddEle(int lastDiffRow[], int mSize, int numAdd)
{
    int ind;

    while(numAdd)
    {
        for(ind = mSize - 2; ind >= 0; ind--)
            lastDiffRow[ind] += lastDiffRow[ind + 1];

        numAdd--;
    }

    return lastDiffRow[0];
}
