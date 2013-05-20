/*******************************************************
 * Author: Nguyen Truong Duy
 *******************************************************/

/* Methodology:
 *	+ Use backtracking
 */

#include <stdio.h>

const int MAX_SIZE = 4;
const char WALL = 'X';
const char EMPTY = '.';
const char ROOK = 'R';
const char ATTACKED = 'A';

void updateBoard(char board[][MAX_SIZE + 1], int size, int row, int col);
void findMaxRookPlaced(char board[][MAX_SIZE + 1], int size, int row, int col, int *maxRook);
int countRook(char board[][MAX_SIZE + 1], int size);
void copyBoard(char board[][MAX_SIZE + 1], char cpyBoard[][MAX_SIZE + 1], int size);
void updateBoard(char board[][MAX_SIZE + 1], int size, int row, int col);

int main(void)
{
	char board[MAX_SIZE][MAX_SIZE + 1], trash[MAX_SIZE + 1], r;
	int size, maxRook;

	while(1)
	{
		scanf("%d", &size);
		if(size == 0)
			break;
		gets(trash);

		for(r = 0; r < size; r++)
			gets(board[r]);
	
		maxRook = 0;
		findMaxRookPlaced(board, size, 0, 0, &maxRook);	

		printf("%d\n", maxRook);	
	}
	return 0;
}

void findMaxRookPlaced(char board[][MAX_SIZE + 1], int size, int row, int col, int *maxRook)
{
	int numRook, nextR, nextC, r, c;
	char cpyBoard[MAX_SIZE][MAX_SIZE + 1];

	if(row == size - 1 && col == size - 1)
	{
		if(board[row][col] == EMPTY)
			board[row][col] = ROOK;

		numRook = countRook(board, size);
		if(numRook > *maxRook)
			*maxRook = numRook;

		/* Backtrack */
		if(board[row][col] == ROOK)
			board[row][col] = EMPTY;
		return;
	}

	nextC = col;
	nextR = row;
	nextC++;
	if(nextC == size)
	{
		nextR++;
		nextC = 0;
	}

	/* Choice 1: Ignore this cell */
	findMaxRookPlaced(board, size, nextR, nextC, maxRook);

	/* Choice 2: If this cell is empty, place a rook */
	if(board[row][col] == EMPTY)
	{
		copyBoard(board, cpyBoard, size);

		cpyBoard[row][col] = ROOK;
		/* Update the board */
		updateBoard(cpyBoard, size, row, col);

		findMaxRookPlaced(cpyBoard, size, nextR, nextC, maxRook);
	}
}	

int countRook(char board[][MAX_SIZE + 1], int size)
{
	int r, c, count = 0;

	for(r = 0; r < size; r++)
		for(c = 0; c < size; c++)
		{
			if(board[r][c] == ROOK)
				count++;			
		}

	return count;		
}

void copyBoard(char board[][MAX_SIZE + 1], char cpyBoard[][MAX_SIZE + 1], int size)
{
	int r, c;

	for(r = 0; r < size; r++)
		for(c = 0; c < size; c++)
			cpyBoard[r][c] = board[r][c];

	for(r = 0; r < size; r++)
		cpyBoard[r][size] = '\0';
} 

void updateBoard(char board[][MAX_SIZE + 1], int size, int row, int col)
{
	int r, c;

	for(r = row - 1; r >= 0 && board[r][col] != WALL; r--)
		board[r][col] = ATTACKED;
	for(r = row + 1; r < size && board[r][col] != WALL; r++)
		board[r][col] = ATTACKED;
	for(c = col + 1; c < size && board[row][c] != WALL; c++)
		board[row][c] = ATTACKED;
	for(c = col - 1; c >= 0 && board[row][c] != WALL; c--)
		board[row][c] = ATTACKED;
}
