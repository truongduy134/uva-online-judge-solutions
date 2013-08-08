#include <stdio.h>
#include <string.h>

#define MAX_SIZE 3
#define MAX_LEN 300
#define MAX_VALUE 10
#define NUM_DIRECTION 5

const int rowOffset[NUM_DIRECTION] = {0, 0, 0, 1, -1};
const int colOffset[NUM_DIRECTION] = {0, 1, -1, 0, 0};

void printBoard(int gameBoard[][MAX_SIZE]);
void reconstructInitBoard(int gameBoard[][MAX_SIZE], char moveSeq[]);
int isValidCell(int row, int col);

int main(void)
{
	int gameBoard[MAX_SIZE][MAX_SIZE], caseId;
	char line[MAX_LEN + 2];

	caseId = 1;
	while(gets(line) != NULL)
	{
		memset(gameBoard, 0, MAX_SIZE * MAX_SIZE * sizeof(int));

		reconstructInitBoard(gameBoard, line);

		printf("Case #%d:\n", caseId);
		printBoard(gameBoard);

		caseId++;
	}

	return 0;
}

void printBoard(int gameBoard[][MAX_SIZE])
{
	int row, col;

	for(row = 0; row < MAX_SIZE; row++)
	{
		printf("%d", gameBoard[row][0]);
		for(col = 1; col < MAX_SIZE; col++)
			printf(" %d", gameBoard[row][col]);
		printf("\n");
	}
}

void reconstructInitBoard(int gameBoard[][MAX_SIZE], char moveSeq[])
{
	int ind, row, col, cellId, direct, newRow, newCol;

	for(ind = 0; moveSeq[ind] != '\0'; ind++)
	{
		cellId = (int) moveSeq[ind] - 'a';
		col = cellId % MAX_SIZE;
		row = cellId / MAX_SIZE;

		for(direct = 0; direct < NUM_DIRECTION; direct++)
		{
			newRow = row + rowOffset[direct];
			newCol = col + colOffset[direct];
			if(isValidCell(newRow, newCol))
				gameBoard[newRow][newCol] = (gameBoard[newRow][newCol] + 1) % MAX_VALUE;
		}	
	}
}

int isValidCell(int row, int col)
{
	if(row < 0 || col < 0 || row >= MAX_SIZE || col >= MAX_SIZE)
		return 0;

	return 1;
}
