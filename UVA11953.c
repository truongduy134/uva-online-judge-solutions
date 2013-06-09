/*******************************************************
 * Author: Nguyen Truong Duy
 *******************************************************/

/* Methodology:
 *  + This problem can be solved in O(N^2) where N is the size of the grid.
 *  + Traverse the graph from left to right, top to bottom.
 *    If we encounter an 'x' character (good part of a ship), then we
 *          * increment the number of ships (initially this variable is set to 0)
 *          * mark this cell, and its neighbors on the right, and its neighbors below it as VISITED
 *            (we stop the marking when we encounter a '.' character). In other words, we mark
 *            the entire ship containing this cell so that we do not double-count it later.
 *
 *  + Since each cell is visited at most twice, the time complexity is O(N^2)
 */

#include <stdio.h>

const char GOOD_PART = 'x';
const char DAMAGED_PART = '@';
const char VISITED = 'V';
const int MARK_VERTICALLY = 0;
const int MARK_HORIZONTALLY = 1;
const int MAX_SIZE = 100;

int countNumShip(char grid[][MAX_SIZE + 1], int mSize);
void markEntireShip(char grid[][MAX_SIZE + 1], int mSize, int row, int col, int direction);

int main(void)
{
    char grid[MAX_SIZE][MAX_SIZE + 1];
    int T, mSize, caseId, i;

    scanf("%d", &T);
    caseId = 1;
    while(caseId <= T)
    {
        scanf("%d", &mSize);

        for(i = 0; i < mSize; i++)
            scanf("%s", grid[i]);

        printf("Case %d: %d\n", caseId, countNumShip(grid, mSize));
        caseId++;
    }
    return 0;
}

int countNumShip(char grid[][MAX_SIZE + 1], int mSize)
{
    int numShip = 0, row, col;

    for(row = 0; row < mSize; row++)
        for(col = 0; col < mSize; col++)
            if(grid[row][col] == GOOD_PART)
            {
                markEntireShip(grid, mSize, row, col, MARK_VERTICALLY);
                markEntireShip(grid, mSize, row, col, MARK_HORIZONTALLY);
                numShip++;
            }

    return numShip;
}

void markEntireShip(char grid[][MAX_SIZE + 1], int mSize, int row, int col, int direction)
{
    int nextInd;
    char * ch;

    if(direction == MARK_HORIZONTALLY)
        nextInd = col + 1;
    else
        nextInd = row + 1;

    while(nextInd < mSize)
    {
        if(direction == MARK_HORIZONTALLY)
            ch = &grid[row][nextInd];
        else
            ch = &grid[nextInd][col];

        if((*ch != GOOD_PART) && (*ch != DAMAGED_PART))
            break;
        *ch = VISITED;

        nextInd++;
    }
}
