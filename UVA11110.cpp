#include <cstdio>
#include <queue>
#include <utility>
#include <cstring>
#include <cstdlib>

using namespace std;

#define MAX_SIZE 100
#define MAX_LEN_LINE 30000
#define FILLED -1
#define NUM_DIRECTION 4

const int rowOffset[NUM_DIRECTION] = {0, 0, 1, -1};
const int colOffset[NUM_DIRECTION] = {1, -1, 0, 0};

bool isGoodEquidivision(int squareMat[][MAX_SIZE], int order);
int fillRegion(int squareMat[][MAX_SIZE], int order, int startRow, int startCol);
bool isValidCell(int order, int row, int col);
int parseLine(int squareMat[][MAX_SIZE], char line[], int regionId);

/* Important note:
 *	+ A cell may be listed more than once in the same partition!
 */
int main(void)
{
	int squareMat[MAX_SIZE][MAX_SIZE], order, numEle;
	char line[MAX_LEN_LINE + 1], trash[MAX_LEN_LINE + 1];

	while(1)
	{
		scanf("%d", &order);
		gets(trash);
		if(!order)
			break;

		memset(squareMat, 0, MAX_SIZE * MAX_SIZE * sizeof(int) );

		for(int id = 1; id < order; id++)
		{
			gets(line);

			numEle = parseLine(squareMat, line, id);
		}

		if(isGoodEquidivision(squareMat, order))
			printf("good\n");
		else
			printf("wrong\n");
	}
	return 0;
}

int parseLine(int squareMat[][MAX_SIZE], char line[], int regionId)
{
	char *token, delim[] = " ";
	int row, col, numEle = 0;

	token = strtok(line, delim);
	while(token != NULL)
	{
		row = atoi(token);
		token = strtok(NULL, delim);
		col = atoi(token);

		numEle++;
		squareMat[row - 1][col - 1] = regionId;

		token = strtok(NULL, delim);
	}
	
	return numEle;
}
bool isGoodEquidivision(int squareMat[][MAX_SIZE], int order)
{
	int sizeRegion;
	for(int row = 0; row < order; row++)
		for(int col = 0; col < order; col++)
			if(squareMat[row][col] != FILLED)
			{
				sizeRegion = fillRegion(squareMat, order, row, col);
				if(sizeRegion != order)
					return false;
			}

	return true;
}

int fillRegion(int squareMat[][MAX_SIZE], int order, int startRow, int startCol)
{
	queue<pair<int, int> > vQueue;

	int val = squareMat[startRow][startCol];

	squareMat[startRow][startCol] = FILLED;
	vQueue.push(pair<int, int> (startRow, startCol));

	int curRow, curCol, nextRow, nextCol, sizeRegion = 0;

	while(!vQueue.empty())
	{
		curRow = vQueue.front().first;
		curCol = vQueue.front().second;
		vQueue.pop();

		sizeRegion++;

		for(int direction = 0; direction < NUM_DIRECTION; direction++)
		{
			nextRow = curRow + rowOffset[direction];
			nextCol = curCol + colOffset[direction];

			if(isValidCell(order, nextRow, nextCol) && squareMat[nextRow][nextCol] == val)
			{
				squareMat[nextRow][nextCol] = FILLED;
				vQueue.push(pair<int, int> (nextRow, nextCol));
			}
		}
	}

	return sizeRegion; 
}

bool isValidCell(int order, int row, int col)
{
	if(row < 0 || col < 0 || row >= order || col >= order)
		return false;
	return true;
}
