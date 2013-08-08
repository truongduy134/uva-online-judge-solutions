#include <stdio.h>

/* Methodology:
 *  + Let (r, c) be a cell on a N x N chessboard.
 *  + We color the chessboard as follows:
 *      + If r + c is even, the cell is white.
 *      + If r + c is odd, the cell is odd.
 *
 *  + Let (r1, c1), (r2, c2) be the start and end positions of the bishop. Assume they are
 *    distinct and the size of the chessboard N >= 2 first.
 *  + If the two positions are on the same diagonal, i.e. |r1 - r2| = |c1 - c2|,
 *    there is only 1 move needed to move the bishop from (r1, c1) to (r2, c2).
 *  + Otherwise, if the two cells have the same color, 2 moves are required.
 *  + Otherwise, the bishop cannot move from (r1, c1), to (r2, c2)
 *
 *  + Corner case:
 *      - if (r1, c1) = (r2, c2), then no move is required.
 *      - if (r1, c1) != (r2, c2) and N = 1, then the bishop cannot move from (r1, c1), to (r2, c2)
 *
 *  + Side note: If the board is rectangular (not square), then the above approach is wrong.
 */

typedef struct
{
    int row, col;
} Cell;

int determineMinBishopMove(Cell * cellStart, Cell * cellEnd);
int absInt(int x);

int main(void)
{
    int numCase, numTest, boardSize, numMove;
    Cell cellStart, cellEnd;

    scanf("%d", &numCase);
    while(numCase)
    {
        scanf("%d %d", &numTest, &boardSize);

        while(numTest)
        {
            scanf("%d %d %d %d", &cellStart.row, &cellStart.col, &cellEnd.row, &cellEnd.col);

            numMove = determineMinBishopMove(&cellStart, &cellEnd);

            if(numMove < 0)
                printf("no move\n");
            else
                printf("%d\n", numMove);

            numTest--;
        }
        numCase--;
    }
    return 0;
}

int determineMinBishopMove(Cell * cellStart, Cell * cellEnd)
{
    if(cellStart->row == cellEnd->row && cellStart->col == cellEnd->col)
        return 0;

    if(absInt(cellStart->row - cellEnd->row) == absInt(cellStart->col - cellEnd->col))
        return 1;

    int sumStart = cellStart->row + cellStart->col,
        sumEnd = cellEnd->row + cellEnd->col;

    if((sumStart & 1) == 0 && (sumEnd & 1) == 0)
        return 2;
    if((sumStart & 1) && (sumEnd & 1))
        return 2;
    return -1;
}

int absInt(int x)
{
    return (x < 0) ? -x : x;
}
