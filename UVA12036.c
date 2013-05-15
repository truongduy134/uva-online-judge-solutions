/********************************************************************************
 * Author: Nguyen Truong Duy
 ********************************************************************************/
#include <stdio.h>

/* Methodology:
 *	+ Observation: 
 *		A n x n grid is stable if and only if no element in the grid has frequency larger than n.
 *	+ With this observation, we can check if a grid is stable in O(n^2) time
 */

#define MAX_SIZE 100
#define MAX_VALUE 100

int isStableGrid(int grid[][MAX_SIZE], int mSize);

int main(void)
{
	int grid[MAX_SIZE][MAX_SIZE], T, mSize, caseId, row, col;

	scanf("%d", &T);
	caseId = 1;

	while(caseId <= T)
	{
		scanf("%d", &mSize);

		for(row = 0; row < mSize; row++)
			for(col = 0; col < mSize; col++)
				scanf("%d", &grid[row][col]);

		printf("Case %d: %s\n", caseId, isStableGrid(grid, mSize) ? "yes" : "no");

		caseId++;
	}
	return 0;
}

/* Assumption: all values in the grid are non-negative and at most 100. */
int isStableGrid(int grid[][MAX_SIZE], int mSize)
{
	int freq[MAX_VALUE + 1] = {0}, row, col, n;

	for(row = 0; row < mSize; row++)
		for(col = 0; col < mSize; col++)
			freq[grid[row][col]]++;

	for(n = 0; n <= MAX_VALUE; n++)
		if(freq[n] > mSize)
			return 0;

	return 1;
}
