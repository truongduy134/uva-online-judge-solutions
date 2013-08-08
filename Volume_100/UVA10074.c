#include <stdio.h>

#define MAX_SIZE 100
#define FREE 0
#define OCCUPIED 1

int findMaxLandCanTakeOnAColumn(int maxLandOnARow[][MAX_SIZE], int startRow, int col, int numRow);
int findMaxLandCanTake(int landMap[][MAX_SIZE], int numRow, int numCol);

int main(void)
{
	int numRow, numCol, landMap[MAX_SIZE][MAX_SIZE], row, col;

	while(1)
	{
		scanf("%d %d", &numRow, &numCol);
		if(!(numRow || numCol))
			break;

		for(row = 0; row < numRow; row++)
			for(col = 0; col < numCol; col++)
				scanf("%d", &landMap[row][col]);

		printf("%d\n", findMaxLandCanTake(landMap, numRow, numCol));
	}
	return 0;
}

int findMaxLandCanTake(int landMap[][MAX_SIZE], int numRow, int numCol)
{
	int row, col, maxLandOnARow[MAX_SIZE][MAX_SIZE], numLandTake, maxLand;

	/* maxLandOnARow[i][j] = the number of lands which can take on the i-th row
  	 *		starting from the j-th columns to the right until we hit
	 *		a tree-occupied land
 	 */
	for(row = 0; row < numRow; row++)
	{
		if(landMap[row][numCol - 1] == FREE)
			maxLandOnARow[row][numCol - 1] = 1;
		else
			maxLandOnARow[row][numCol - 1] = 0;

		for(col = numCol - 2; col >= 0; col--)
			if(landMap[row][col] == FREE)
				maxLandOnARow[row][col] = 1 + maxLandOnARow[row][col + 1];
			else
				maxLandOnARow[row][col] = 0;
	}

	maxLand = 0;
	for(col = 0; col < numCol; col++)
		for(row = 0; row < numRow; row++)
		{
			/* Find the number of land we can take if the top left corner of the region
			 *	is at (row, col)
			 */
			numLandTake = findMaxLandCanTakeOnAColumn(maxLandOnARow, row, col, numRow);
			if(numLandTake > maxLand)
				maxLand = numLandTake;
		}

	return maxLand;
}

int findMaxLandCanTakeOnAColumn(int maxLandOnARow[][MAX_SIZE], int startRow, int col, int numRow)
{
	int minLandAmongRows = maxLandOnARow[startRow][col], maxLandTaken = maxLandOnARow[startRow][col], endRow, numLand;

	for(endRow = startRow + 1; endRow < numRow; endRow++)
	{
		if(maxLandOnARow[endRow][col] < minLandAmongRows)
			minLandAmongRows = maxLandOnARow[endRow][col];
		if(minLandAmongRows == 0)
			break;

		numLand = (endRow - startRow + 1) * minLandAmongRows;
		if(numLand > maxLandTaken)
			maxLandTaken = numLand;
	}

	return maxLandTaken;
}
