#include <stdio.h>
#include <stdlib.h>

#define CHESSBOARD_DIMENSION 8

enum STATE
{
    ILLEGAL_STATE,
    ILLEGAL_MOVE,
    MOVE_NOT_ALLOWED,
    CONTINUE,
    STOP
};

int getCellIdLeft(int cellId);
int getCellIdAbove(int cellId);
int getCellIdBelow(int cellId);
int getCellIdRight(int cellId);
enum STATE determineState(int kingCellId, int queenCellId, int newQueenCellId);
int isLegalMoveQueen(int kingCellId, int queenCellId, int newQueenCellId);
int isAllowedMoveQueen(int kingCellId, int newQueenCellId);
int onSameRow(int cellOne, int cellTwo);
int onSameCol(int cellOne, int cellTwo);
int isOnQueenRoute(int cellId, int queenCellId);
int isKingLockedByQueen(int kingCellId, int queenCellId);
int isBetween(int value, int endPointOne, int endPointTwo);

/* The chessboard cells are numbered from 0 to 63. The numbering starts from top to bottom, from left to right. */
int main()
{
    int kingCellId, queenCellId, newQueenCellId;
    enum STATE result;
    while(scanf("%d %d %d", &kingCellId, &queenCellId, &newQueenCellId) > 0)
    {
        result = determineState(kingCellId, queenCellId, newQueenCellId);

        switch(result)
        {
            case ILLEGAL_STATE:
                printf("Illegal state\n");
                break;
            case ILLEGAL_MOVE:
                printf("Illegal move\n");
                break;
            case MOVE_NOT_ALLOWED:
                printf("Move not allowed\n");
                break;
            case CONTINUE:
                printf("Continue\n");
                break;
            case STOP:
                printf("Stop\n");
        }
    }

    return 0;
}

int getCellIdLeft(int cellId)
{
    if(cellId % CHESSBOARD_DIMENSION == 0)
        return -1;      /* This cell does not have a left neighbor */

    return cellId - 1;
}

int getCellIdRight(int cellId)
{
    if((cellId + 1) % CHESSBOARD_DIMENSION == 0)
        return -1;      /* This cell does not have a right neighbor */

    return cellId + 1;
}

int getCellIdAbove(int cellId)
{
    if(cellId < CHESSBOARD_DIMENSION)
        return -1;      /* Because this cell is already on the top */

    return cellId - CHESSBOARD_DIMENSION;
}

int getCellIdBelow(int cellId)
{
    if((cellId + CHESSBOARD_DIMENSION) >= CHESSBOARD_DIMENSION * CHESSBOARD_DIMENSION)
        return -1;      /* Because this cell is already on the last row */

    return cellId + CHESSBOARD_DIMENSION;
}

enum STATE determineState(int kingCellId, int queenCellId, int newQueenCellId)
{
    if(kingCellId == queenCellId)
        return ILLEGAL_STATE;

    if(!isLegalMoveQueen(kingCellId, queenCellId, newQueenCellId))
        return ILLEGAL_MOVE;

    if(!isAllowedMoveQueen(kingCellId, newQueenCellId))
        return MOVE_NOT_ALLOWED;

    if(isKingLockedByQueen(kingCellId, newQueenCellId))
        return STOP;

    return CONTINUE;
}

int isLegalMoveQueen(int kingCellId, int queenCellId, int newQueenCellId)
{
    if(kingCellId == newQueenCellId)
        return 0;
    if(newQueenCellId == queenCellId)
        return 0;   /* The queen is not moved at all */

    if(onSameCol(newQueenCellId, queenCellId))
    {
        /* The two positions are in the same column */
        if(onSameCol(kingCellId, queenCellId))
            return !isBetween(kingCellId, queenCellId, newQueenCellId);

        return 1;
    }

    if(onSameRow(newQueenCellId, queenCellId))
    {
        /* The two positions are in the same row */
        if(onSameRow(kingCellId, queenCellId))
            return !isBetween(kingCellId, queenCellId, newQueenCellId);

        return 1;
    }

    return 0;
}

int isAllowedMoveQueen(int kingCellId, int newQueenCellId)
{
    /* Assume: newQueenCellId is a legal move */
    if(newQueenCellId == getCellIdLeft(kingCellId) || newQueenCellId == getCellIdRight(kingCellId) ||
       newQueenCellId == getCellIdAbove(kingCellId) || newQueenCellId == getCellIdBelow(kingCellId))
       return 0;

    return 1;
}

int onSameRow(int cellOne, int cellTwo)
{
    if(cellOne / CHESSBOARD_DIMENSION == cellTwo / CHESSBOARD_DIMENSION)
        return 1;
    return 0;
}

int onSameCol(int cellOne, int cellTwo)
{
    if(cellOne % CHESSBOARD_DIMENSION == cellTwo % CHESSBOARD_DIMENSION)
        return 1;
    return 0;
}

int isOnQueenRoute(int cellId, int queenCellId)
{
    return onSameCol(cellId, queenCellId) | onSameRow(cellId, queenCellId);
}

int isKingLockedByQueen(int kingCellId, int queenCellId)
{
    int kingNeighborId[4];
    int numCanMove = 0, index;


    kingNeighborId[0] = getCellIdLeft(kingCellId);
    kingNeighborId[1] = getCellIdRight(kingCellId);
    kingNeighborId[2] = getCellIdAbove(kingCellId);
    kingNeighborId[3] = getCellIdBelow(kingCellId);


    for(index = 0; index < 4; index++)
        if(kingNeighborId[index] >= 0 && !isOnQueenRoute(kingNeighborId[index], queenCellId))
            return 0;   /* There is at least 1 possible move for the king */

    return 1;
}
int isBetween(int value, int endPointOne, int endPointTwo)
{
    if(endPointOne < value && value < endPointTwo)
        return 1;
    if(endPointTwo < value && value < endPointOne)
        return 1;

    return 0;
}

