/*******************************************************
 * Author: Nguyen Truong Duy
 *******************************************************/

/* Methodology:
 *  + This is a implicit graph problem.
 *  + Note: Since it is ensured there is a winner, we just need to check if BLACK_PLAYER wins.
 *      If not, WHITE_PLAYER wins.
 *  + In row 1, we consider each cell from left to right (from column 1 to column N), if
 *      that cell is a BLACK_MOVE (and not visited yet), we explore the connected component
 *      containing that cell using DFS or BFS. If we can reach row N, BLACK_PLAYER wins.
 *
 *  + Time complexity: O(N^2) where N is the size of the game board
 */

#include <stdio.h>

const int MAX_SIZE = 200;
#define NUM_DIRECTION 6
const int COORD_OFFSET[NUM_DIRECTION][2] = { {-1, -1}, {-1, 0}, {0, -1}, {0, 1}, {1, 0}, {1, 1}};
const char BLACK_PLAYER = 'b';
const char WHITE_PLAYER = 'w';
const char CHECK_BLACK = 'B';

void runDFS(char board[][MAX_SIZE + 1], int mSize, int row, int col, int * hasWon);
char determineWinner(char board[][MAX_SIZE + 1], int mSize);
int isValidCell(int row, int col, int mSize);

int main(void)
{
    char board[MAX_SIZE][MAX_SIZE + 1];
    int mSize, caseId, i;
    char winner;

    caseId = 1;
    while(1)
    {
        scanf("%d", &mSize);
        if(!mSize)
            break;

        for(i = 0; i < mSize; i++)
            scanf("%s", board[i]);

        winner = determineWinner(board, mSize);
        if(winner == BLACK_PLAYER)
            winner = 'B';
        else
            winner = 'W';
        printf("%d %c\n", caseId, winner);

        caseId++;
    }
    return 0;
}

char determineWinner(char board[][MAX_SIZE + 1], int mSize)
{
    /* Check if BLACK wins. BLACK wins if he can join row 0 to row mSize - 1 */
    int hasWon, col;

    for(col = 0; col < mSize; col++)
        if(board[0][col] == BLACK_PLAYER)
        {
            hasWon = 0;
            runDFS(board, mSize, 0, col, &hasWon);
            if(hasWon)
                return BLACK_PLAYER;
        }

    /* If BLACK does not win, WHITE wins (since there must be a winner */
    return WHITE_PLAYER;
}

/* Consider the black player only */
void runDFS(char board[][MAX_SIZE + 1], int mSize, int row, int col, int * hasWon)
{
    board[row][col] = CHECK_BLACK;

    if(row == mSize - 1)
    {
        *hasWon = 1;
        return;
    }

    int direction, nextR, nextC;
    for(direction = 0; direction < NUM_DIRECTION; direction++)
    {
        nextR = row + COORD_OFFSET[direction][0];
        nextC = col + COORD_OFFSET[direction][1];

        if(isValidCell(nextR, nextC, mSize) && board[nextR][nextC] == BLACK_PLAYER)
        {
            runDFS(board, mSize, nextR, nextC, hasWon);
            if(*hasWon)
                return;
        }
    }
}

int isValidCell(int row, int col, int mSize)
{
    if(row < 0 || col < 0 || row >= mSize || col >= mSize)
        return 0;
    return 1;
}
