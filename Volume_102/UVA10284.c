#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

enum CELL_STATE {
    KING,
    QUEEN,
    ROOK,
    KNIGHT,
    BISHOP,
    BLACK_PAWN,
    WHITE_PAWN,
    ATTACKED,
    FREE
};

#define BOARD_DIMEN 8
#define STR_MAX_LEN 100

void getCellStateFromFen(enum CELL_STATE chessBoard[][BOARD_DIMEN], char *fen);
void getCellStateRow(enum CELL_STATE chessBoard[][BOARD_DIMEN], int rowIndex, char *rowFen);
int countCellState(enum CELL_STATE chessBoard[][BOARD_DIMEN], enum CELL_STATE desiredState);
void findAttackedCell(enum CELL_STATE chessBoard[][BOARD_DIMEN]);
void initChessBoard(enum CELL_STATE chessBoard[][BOARD_DIMEN], enum CELL_STATE initState);
void attackKing(enum CELL_STATE chessBoard[][BOARD_DIMEN], int rowKing, int colKing);
void attackKnight(enum CELL_STATE chessBoard[][BOARD_DIMEN], int rowKnight, int colKnight);
void attackBishop(enum CELL_STATE chessBoard[][BOARD_DIMEN], int rowBishop, int colBishop);
void attackQueen(enum CELL_STATE chessBoard[][BOARD_DIMEN], int rowQueen, int colQueen);
void attackRook(enum CELL_STATE chessBoard[][BOARD_DIMEN], int rowRook, int colRook);
void attackPawn(enum CELL_STATE chessBoard[][BOARD_DIMEN], int rowRook, int colRook, int isWhite);
int isLegalCell(int boardDimen, int row, int col);

int main()
{
    char fen[STR_MAX_LEN];
    enum CELL_STATE chessBoard[BOARD_DIMEN][BOARD_DIMEN];

    while(gets(fen) != NULL)
    {
        initChessBoard(chessBoard, FREE);

        getCellStateFromFen(chessBoard, fen);

        findAttackedCell(chessBoard);

        printf("%d\n", countCellState(chessBoard, FREE));
    }
    return 0;
}

void initChessBoard(enum CELL_STATE chessBoard[][BOARD_DIMEN], enum CELL_STATE initState)
{
    int row, col;

    for(row = 0; row < BOARD_DIMEN; row++)
        for(col = 0; col < BOARD_DIMEN; col++)
            chessBoard[row][col] = initState;
}

void getCellStateFromFen(enum CELL_STATE chessBoard[][BOARD_DIMEN], char *fen)
{
    char *row;
    const char delim[] = "/";
    int rowIndex = 0;

    row = strtok(fen, delim);
    getCellStateRow(chessBoard, rowIndex, row);
    rowIndex++;

    do
    {
        row = strtok(NULL, delim);
        if(row != NULL)
        {
            getCellStateRow(chessBoard, rowIndex, row);
            rowIndex++;
        }
    } while(row != NULL);
}

void getCellStateRow(enum CELL_STATE chessBoard[][BOARD_DIMEN], int rowIndex, char *rowFen)
{
    int len = strlen(rowFen), colIndex, index;

    for(index = 0, colIndex = 0; index < len; index++)
    {
        if(isdigit(rowFen[index]))
        {
            colIndex += (rowFen[index] - '0');
        }
        else
        {
            /* This is a chess pieces */
            switch(rowFen[index])
            {
                case 'k':
                case 'K':
                    chessBoard[rowIndex][colIndex] = KING;
                    break;
                case 'q':
                case 'Q':
                    chessBoard[rowIndex][colIndex] = QUEEN;
                    break;
                case 'n':
                case 'N':
                    chessBoard[rowIndex][colIndex] = KNIGHT;
                    break;
                case 'b':
                case 'B':
                    chessBoard[rowIndex][colIndex] = BISHOP;
                    break;
                case 'r':
                case 'R':
                    chessBoard[rowIndex][colIndex] = ROOK;
                    break;
                case 'p':
                    chessBoard[rowIndex][colIndex] = BLACK_PAWN;
                    break;
                case 'P':
                    chessBoard[rowIndex][colIndex] = WHITE_PAWN;
            }
            colIndex++;
        }
    }
}

void findAttackedCell(enum CELL_STATE chessBoard[][BOARD_DIMEN])
{
    int row, col;

    for(row = 0; row < BOARD_DIMEN; row++)
        for(col = 0; col < BOARD_DIMEN; col++)
        {
            switch(chessBoard[row][col])
            {
                case KING:
                    attackKing(chessBoard, row, col);
                    break;
                case QUEEN:
                    attackQueen(chessBoard, row, col);
                    break;
                case BISHOP:
                    attackBishop(chessBoard, row, col);
                    break;
                case ROOK:
                    attackRook(chessBoard, row, col);
                    break;
                case KNIGHT:
                    attackKnight(chessBoard, row, col);
                    break;
                case BLACK_PAWN:
                    attackPawn(chessBoard, row, col, 0);
                    break;
                case WHITE_PAWN:
                    attackPawn(chessBoard, row, col, 1);
            }
        }
}

int countCellState(enum CELL_STATE chessBoard[][BOARD_DIMEN], enum CELL_STATE desiredState)
{
    int count = 0, row, col;

    for(row = 0; row < BOARD_DIMEN; row++)
        for(col = 0; col < BOARD_DIMEN; col++)
            if(chessBoard[row][col] == desiredState)
                count++;

    return count;
}

void attackKing(enum CELL_STATE chessBoard[][BOARD_DIMEN], int rowKing, int colKing)
{
    int rowOffset, colOffset, newRow, newCol;

    for(rowOffset = -1; rowOffset <= 1; rowOffset++)
        for(colOffset = -1; colOffset <= 1; colOffset++)
        {
            newRow = rowKing + rowOffset;
            newCol = colKing + colOffset;
            if(newRow != rowKing || newCol != colKing)
            {
                if(isLegalCell(BOARD_DIMEN, newRow, newCol) && chessBoard[newRow][newCol] == FREE)
                    chessBoard[newRow][newCol] = ATTACKED;
            }
        }
}

void attackKnight(enum CELL_STATE chessBoard[][BOARD_DIMEN], int rowKnight, int colKnight)
{
    const int numDirect = 8;
    int directVer[] = {-1, 1, -1, 1, -2, 2, -2, 2}, directHor[] = {-2, 2, 2, -2, -1, 1, 1, -1}, index, newRow, newCol;

    for(index = 0; index < numDirect; index++)
    {
        newRow = rowKnight + directVer[index];
        newCol = colKnight + directHor[index];

        if(isLegalCell(BOARD_DIMEN, newRow, newCol) && chessBoard[newRow][newCol] == FREE)
            chessBoard[newRow][newCol] = ATTACKED;
    }
}

void attackBishop(enum CELL_STATE chessBoard[][BOARD_DIMEN], int rowBishop, int colBishop)
{
    const int numDirect = 4;
    int directVer[] = {-1, 1, -1, 1}, directHor[] = {-1, 1, 1, -1}, index, newRow, newCol;

    for(index = 0; index < numDirect; index++)
    {
        newRow = rowBishop;
        newCol = colBishop;

        while(1)
        {
            newRow += directVer[index];
            newCol += directHor[index];

            if(!isLegalCell(BOARD_DIMEN, newRow, newCol))
                break;

            if(chessBoard[newRow][newCol] != FREE && chessBoard[newRow][newCol] != ATTACKED)
                /* The bishop cannot attack through another piece which is on its way */
                break;

            chessBoard[newRow][newCol] = ATTACKED;
        }
    }
}

void attackQueen(enum CELL_STATE chessBoard[][BOARD_DIMEN], int rowQueen, int colQueen)
{
    attackBishop(chessBoard, rowQueen, colQueen);
    attackRook(chessBoard, rowQueen, colQueen);
}

void attackRook(enum CELL_STATE chessBoard[][BOARD_DIMEN], int rowRook, int colRook)
{
    const int numDirect = 4;
    int directVer[] = {-1, 1, 0, 0},
        directHor[] = {0, 0, 1, -1}, index, newRow, newCol;

    for(index = 0; index < numDirect; index++)
    {
        newRow = rowRook;
        newCol = colRook;

        while(1)
        {
            newRow += directVer[index];
            newCol += directHor[index];

            if(!isLegalCell(BOARD_DIMEN, newRow, newCol))
                break;

            if(chessBoard[newRow][newCol] != FREE && chessBoard[newRow][newCol] != ATTACKED)
                /* The rook cannot attack through another piece which is on its way */
                break;

            chessBoard[newRow][newCol] = ATTACKED;
        }
    }
}

void attackPawn(enum CELL_STATE chessBoard[][BOARD_DIMEN], int rowPawn, int colPawn, int isWhite)
{
    const int numDirect = 2;
    int verOffset, direct[] = {-1, 1}, index, newRow, newCol;

    if(isWhite)
        verOffset = -1;      /* White pawns go up */
    else
        verOffset = 1;

    newRow = rowPawn + verOffset;

    for(index = 0; index < numDirect; index++)
    {
        newCol = colPawn + direct[index];

        if(isLegalCell(BOARD_DIMEN, newRow, newCol) && chessBoard[newRow][newCol] == FREE)
            chessBoard[newRow][newCol] = ATTACKED;
    }
}

int isLegalCell(int boardDimen, int row, int col)
{
    if(row < 0 || col < 0 || row >= boardDimen || col >= boardDimen)
        return 0;
    return 1;
}
