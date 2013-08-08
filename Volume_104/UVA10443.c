#include <stdio.h>

#define MAX_SIZE 100
#define ROCK 'R'
#define PAPER 'P'
#define SCISSOR 'S'

#define NUM_DIRECTION 4

const int rowOffset[NUM_DIRECTION] = {0, 0, 1, -1};
const int colOffset[NUM_DIRECTION] = {1, -1, 0, 0};

void simulateWar(char current[][MAX_SIZE + 1], char result[][MAX_SIZE + 1], int numRow, int numCol, int numDay);
void simulateWarOneDay(char current[][MAX_SIZE + 1], char next[][MAX_SIZE + 1], int numRow, int numCol);
int existNeighbor(char grid[][MAX_SIZE + 1], int numRow, int numCol, int row, int col, char wanted);
int isValidCell(int row, int col, int numRow, int numCol);
int areTheSameGrid(char gridOne[][MAX_SIZE + 1], char gridTwo[][MAX_SIZE + 1], int numRow, int numCol);
void copyGrid(char dest[][MAX_SIZE + 1], char src[][MAX_SIZE + 1], int numRow, int numCol);

int main(void)
{
	int T, numRow, numCol, numDay, row;
	char grid[MAX_SIZE][MAX_SIZE + 1], result[MAX_SIZE][MAX_SIZE + 1], trash[MAX_SIZE + 1];

	scanf("%d", &T);
	while(T)
	{
		scanf("%d %d %d", &numRow, &numCol, &numDay);
		gets(trash);

		for(row = 0; row < numRow; row++)
			gets(grid[row]);

		simulateWar(grid, result, numRow, numCol, numDay);

		for(row = 0; row < numRow; row++)
			printf("%s\n", result[row]);

		if(T != 1)
			printf("\n");
		T--;
	}
	return 0;
}

void simulateWar(char current[][MAX_SIZE + 1], char result[][MAX_SIZE + 1], int numRow, int numCol, int numDay)
{
	int day;

	for(day = 0; day < numDay; day++)
	{
		simulateWarOneDay(current, result, numRow, numCol);

		if(areTheSameGrid(current, result, numRow, numCol))
			break;

		copyGrid(current, result, numRow, numCol);
	}
}

void simulateWarOneDay(char current[][MAX_SIZE + 1], char next[][MAX_SIZE + 1], int numRow, int numCol)
{
	int row, col;
	char enemy;

	for(row = 0; row < numRow; row++)
		for(col = 0; col < numCol; col++)
		{
			switch(current[row][col])
			{
				case ROCK:
					enemy = PAPER;
					break;
				case PAPER:
					enemy = SCISSOR;
					break;
				default:
					enemy = ROCK;
			}

			if(existNeighbor(current, numRow, numCol, row, col, enemy))
				next[row][col] = enemy;
			else
				next[row][col] = current[row][col];
		}
}

int existNeighbor(char grid[][MAX_SIZE + 1], int numRow, int numCol, int row, int col, char wanted)
{
	int d, nextRow, nextCol;

	for(d = 0; d < NUM_DIRECTION; d++)
	{
		nextRow = row + rowOffset[d];
		nextCol = col + colOffset[d];

		if(isValidCell(nextRow, nextCol, numRow, numCol) && grid[nextRow][nextCol] == wanted)
			return 1;
	}

	return 0;
}

int isValidCell(int row, int col, int numRow, int numCol)
{
	if(row < 0 || col < 0 || row >= numRow || col >= numCol)
		return 0;
	return 1;
}

int areTheSameGrid(char gridOne[][MAX_SIZE + 1], char gridTwo[][MAX_SIZE + 1], int numRow, int numCol)
{
	int row, col;

	for(row = 0; row < numRow; row++)
		for(col = 0; col < numCol; col++)
			if(gridOne[row][col] != gridTwo[row][col])
				return 0;

	return 1;
}

void copyGrid(char dest[][MAX_SIZE + 1], char src[][MAX_SIZE + 1], int numRow, int numCol)
{
	int row, col;

	for(row = 0; row < numRow; row++)
		for(col = 0; col < numCol; col++)
			dest[row][col] = src[row][col];

}
