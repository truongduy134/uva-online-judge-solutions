/*******************************************************************************
 * Author: Nguyen Truong Duy
 *******************************************************************************/

/* Methodology:
 *	+ The problem aks us to check if the given configuration of tic-tac-toe is
 *		is valid or not.
 *
 *	+ Invalid cases:
 *		- The number of X < The number of O
 *		- The number of X - The number of O > 2
 *		- X and O both win
 *		- When O win, the number of X != the number of O
 *		- When X win, the number of X - the number of O = 1
 *	  Note that the case
 *		XXX
 *		OOO
 *		XXX
 *	  falls in the first two circumstances.
 *
 *	+ Gotcha:
 *        The following configuration is valid:
 *		XXX
 *		XOO
 *		XOO
 *	+ Time complexity: O(1)
 */

#include <stdio.h>

const int BOARD_SIZE = 3;
const char X_PLAYER = 'X';
const char O_PLAYER = 'O';

int isValidGame(char board[][BOARD_SIZE + 1]);
int countNumMove(char board[][BOARD_SIZE + 1], char player);
int countNumWinningMove(char board[][BOARD_SIZE + 1], char player);

int main(void)
{
	char board[BOARD_SIZE][BOARD_SIZE + 1];
	int T, i;

	scanf("%d", &T);
	while(T)
	{
		for(i = 0; i < BOARD_SIZE; i++)
			scanf("%s", board[i]);

		if(isValidGame(board))
			printf("yes\n");
		else
			printf("no\n");

		T--;
	}
	return 0;
}

int isValidGame(char board[][BOARD_SIZE + 1])
{
	int numMoveX = countNumMove(board, X_PLAYER),
	    numMoveO = countNumMove(board, O_PLAYER);
	
	if(numMoveX < numMoveO || numMoveX - numMoveO > 1)
		return 0;

	int numWinMoveX = countNumWinningMove(board, X_PLAYER),
	    numWinMoveO = countNumWinningMove(board, O_PLAYER);
	
	if(numWinMoveX > 0 && numWinMoveO > 0)
		return 0;

	if(numWinMoveX > 0 && numMoveX - numMoveO != 1)
		return 0;
	if(numWinMoveO > 0 && numMoveO != numMoveX)
		return 0;

	return 1;
}

int countNumMove(char board[][BOARD_SIZE + 1], char player)
{
	int row, col, count = 0;

	for(row = 0; row < BOARD_SIZE; row++)
		for(col = 0; col < BOARD_SIZE; col++)
			if(board[row][col] == player)
				count++;

	return count;
}

int countNumWinningMove(char board[][BOARD_SIZE + 1], char player)
{
	int numWinMove = 0, row, col, count;

	/* Count winning moves on a row */
	for(row = 0; row < BOARD_SIZE; row++)
	{
		count = 0;
		for(col = 0; col < BOARD_SIZE; col++)
			if(board[row][col] == player)
				count++;

		if(count == BOARD_SIZE)
			numWinMove++;
	}

	/* Count winning moves on a column */
	for(col = 0; col < BOARD_SIZE; col++)
	{
		count = 0;
		for(row = 0; row < BOARD_SIZE; row++)
			if(board[row][col] == player)
				count++;

		if(count == BOARD_SIZE)
			numWinMove++;
	}

	/* Check if winning move is on main diagonal */
	count = 0;
	for(row = 0; row < BOARD_SIZE; row++)
		if(board[row][row] == player)
			count++;
	if(count == BOARD_SIZE)
		numWinMove++;

	/* Check if winning move is on the other diagonal */
	count = 0;
	for(row = 0; row < BOARD_SIZE; row++)
		if(board[row][BOARD_SIZE - row - 1] == player)
			count++;
	if(count == BOARD_SIZE)
		numWinMove++;

	return numWinMove;
}
