#include <stdio.h>

typedef struct
{
    int row, col;
} ChessCoordinate;

int abs(int x);
int findMinNumQueenMove(ChessCoordinate * from, ChessCoordinate * to);

int main(void)
{
    ChessCoordinate from, to;

    while(1)
    {
        scanf("%d %d %d %d", &from.row, &from.col, &to.row, &to.col);
        if(from.row == 0)
            break;

        printf("%d\n", findMinNumQueenMove(&from, &to));
    }
    return 0;
}

int abs(int x)
{
    if(x < 0)
        return -x;
    return x;
}

int findMinNumQueenMove(ChessCoordinate * from, ChessCoordinate * to)
{
    if(from->row == to->row && from->col == to->col)
        /* Start and destination cells are the same */
        return 0;

    if(from->row == to->row || from->col == to->col)
        /* On same row or column */
        return 1;

    if(abs(from->row - to->row) == abs(from->col - to->col))
        /* On the same diagonal */
        return 1;

    return 2;
}
