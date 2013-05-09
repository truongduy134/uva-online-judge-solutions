#include <stdio.h>
#include <string.h>

#define MAX_SIZE 500
#define EMPTY 0
#define OCCUPIED 1

typedef struct {
    int row, col;
} Cell;

int countCell(int grid[][MAX_SIZE], int numRow, int numCol, int val);
void markSubgrid(int grid[][MAX_SIZE], Cell * pOne, Cell * pTwo);

int main(void)
{
    int grid[MAX_SIZE][MAX_SIZE], numRow, numCol, numSubgrid, i, numEmpty;
    Cell pOne, pTwo;

    while(1)
    {
        scanf("%d %d %d", &numCol, &numRow, &numSubgrid);
        if(!(numCol || numRow || numSubgrid))
            break;

        memset(grid, 0, MAX_SIZE * MAX_SIZE * sizeof(int));

        for(i = 0; i < numSubgrid; i++)
        {
            scanf("%d %d %d %d", &pOne.col, &pOne.row, &pTwo.col, &pTwo.row);
            /* Convert from 1 to 0-indexing */
            pOne.row--;
            pTwo.row--;
            pOne.col--;
            pTwo.col--;

            markSubgrid(grid, &pOne, &pTwo);
        }

        numEmpty = countCell(grid, numRow, numCol, EMPTY);

        if(numEmpty == 0)
            printf("There is no empty spots.\n");
        else
        {
            if(numEmpty == 1)
                printf("There is one empty spot.\n");
            else
                printf("There are %d empty spots.\n", numEmpty);
        }
    }
    return 0;
}

int countCell(int grid[][MAX_SIZE], int numRow, int numCol, int val)
{
    int row, col, mCount = 0;

    for(row = 0; row < numRow; row++)
        for(col = 0; col < numCol; col++)
            if(grid[row][col] == val)
                mCount++;

    return mCount;
}

void markSubgrid(int grid[][MAX_SIZE], Cell * pOne, Cell * pTwo)
{
    int rowFrom, rowTo, colFrom, colTo, row, col;

    if(pOne->row < pTwo->row)
    {
        rowFrom = pOne->row;
        rowTo = pTwo->row;
    }
    else
    {
        rowFrom = pTwo->row;
        rowTo = pOne->row;
    }

    if(pOne->col < pTwo->col)
    {
        colFrom = pOne->col;
        colTo = pTwo->col;
    }
    else
    {
        colFrom = pTwo->col;
        colTo = pOne->col;
    }

    for(row = rowFrom; row <= rowTo; row++)
        for(col = colFrom; col <= colTo; col++)
            grid[row][col] = OCCUPIED;
}
