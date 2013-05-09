#include <stdio.h>

#define MAX_SIZE 100
#define OK 0
#define CAN_FIX 1
#define CORRUPT 2

int checkParity(int mat[][MAX_SIZE], int mSize, int *rowFix, int *colFix);
/* Only care for numOdd = 0, or 1, or numOdd > 1 */
int countOdd(int arr[], int mSize, int *firstOddPos);

int main(void)
{
    int mat[MAX_SIZE][MAX_SIZE], mSize, rowFix, colFix, row, col, result;

    while(1)
    {
        scanf("%d", &mSize);
        if(mSize == 0)
            break;

        for(row = 0; row < mSize; row++)
            for(col = 0; col < mSize; col++)
                scanf("%d", &mat[row][col]);

        result = checkParity(mat, mSize, &rowFix, &colFix);
        switch(result)
        {
            case OK:
                printf("OK\n");
                break;
            case CAN_FIX:
                printf("Change bit (%d,%d)\n", rowFix + 1, colFix + 1);
                break;
            default:
                printf("Corrupt\n");
        }
    }

    return 0;
}

int checkParity(int mat[][MAX_SIZE], int mSize, int *rowFix, int *colFix)
{
    int colParity[MAX_SIZE] = {0}, rowParity[MAX_SIZE] = {0}, row, col, numOddRow, posRow,
        numOddCol, posCol;

    for(row = 0; row < mSize; row++)
        for(col = 0; col < mSize; col++)
        {
            colParity[col] += mat[row][col];
            rowParity[row] += mat[row][col];
        }

    /* Also return the first odd position */
    numOddRow = countOdd(rowParity, mSize, &posRow);
    numOddCol = countOdd(colParity, mSize, &posCol);

    if(numOddRow == 0 && numOddCol == 0)
        return OK;

    if(numOddRow > 1 || numOddCol > 1)
        return CORRUPT;

    *rowFix = posRow;
    *colFix = posCol;
    return CAN_FIX;
}

int countOdd(int arr[], int mSize, int *firstOddPos)
{
    int i, numOdd = 0;

    for(i = 0; i < mSize; i++)
        if(arr[i] & 1)
        {
            numOdd++;
            if(numOdd > 1)
                break;
            *firstOddPos = i;
        }

    return numOdd;
}
