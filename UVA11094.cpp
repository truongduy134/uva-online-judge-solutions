#include <cstdio>
#include <utility>
#include <queue>

using namespace std;

#define MAX_SIZE 30
#define NUM_DIRECTION 4

int LAND, WATER;
const int rowOffset[NUM_DIRECTION] = {0, 0, 1, -1};
const int colOffset[NUM_DIRECTION] = {1, -1, 0, 0};

int findBiggestSizeToCapture(char grid[][MAX_SIZE + 1], int numRow, int numCol, int kingRow, int kingCol);
int countAndMarkRegion(char grid[][MAX_SIZE + 1], int numRow, int numCol, int startRow, int startCol);
bool isValidCell(int row, int col, int numRow, int numCol);

int main(void)
{
	int numRow, numCol, kingRow, kingCol;	
	char grid[MAX_SIZE][MAX_SIZE + 1], trash[MAX_SIZE + 1];

	while(scanf("%d %d", &numRow, &numCol) > 0)
	{
		gets(trash);

		for(int row = 0; row < numRow; row++)
			gets(grid[row]);
		scanf("%d %d", &kingRow, &kingCol);

		// Find the symbols denoting LAND and WATER 
		LAND = grid[kingRow][kingCol];
		for(int row = 0; row < numRow; row++)
		{
			bool foundWater = false;
			for(int col = 0; col < numCol; col++)
				if(grid[row][col] != LAND)
				{
					WATER = grid[row][col];
					foundWater = true;
					break;
				}
			if(foundWater)
				break;
		}

		printf("%d\n", findBiggestSizeToCapture(grid, numRow, numCol, kingRow, kingCol));
	}
	return 0;
}

int findBiggestSizeToCapture(char grid[][MAX_SIZE + 1], int numRow, int numCol, int kingRow, int kingCol)
{
	int maxSize = 0, mSize;

	countAndMarkRegion(grid, numRow, numCol, kingRow, kingCol);

	for(int row = 0; row < numRow; row++)
		for(int col = 0; col < numCol; col++)
			if(grid[row][col] == LAND)
			{
				mSize = countAndMarkRegion(grid, numRow, numCol, row, col);
				if(mSize > maxSize)
					maxSize = mSize;
			}

	return maxSize;
}

int countAndMarkRegion(char grid[][MAX_SIZE + 1], int numRow, int numCol, int startRow, int startCol)
{
	queue<pair<int, int> > bfsQueue;
	int regionCount = 0;

	bfsQueue.push(pair<int, int> (startRow, startCol) );
	grid[startRow][startCol] = WATER;
	regionCount++;

	pair<int, int> curCell;
	int curR, curC, nextR, nextC;

	while(!bfsQueue.empty())
	{
		curCell = bfsQueue.front();
		bfsQueue.pop();
		curR = curCell.first;
		curC = curCell.second;

		for(int d = 0; d < NUM_DIRECTION; d++)
		{
			nextR = curR + rowOffset[d];
			nextC = curC + colOffset[d];
			if(nextC == numCol)
				nextC = 0;
			if(nextC < 0)
				nextC = numCol - 1;

			if(isValidCell(nextR, nextC, numRow, numCol) &&
			   grid[nextR][nextC] == LAND)
			{
				grid[nextR][nextC] = WATER;
				regionCount++;
				bfsQueue.push(pair<int, int> (nextR, nextC));
			}			
		}
	}

	return regionCount;
}

bool isValidCell(int row, int col, int numRow, int numCol)
{
	if(row < 0 || col < 0 || row >= numRow || col >= numCol)
		return false;
	return true;
}
