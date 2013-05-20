/*******************************************************
 * Author: Nguyen Truong Duy
 *******************************************************/

/* Methodology:
 *	+ Use dynamic programming.
 *	+ Define:
 *		f(i, j) = the minimum weight of paths going from column i to n - 1 (There are n columns, numbered from 0 to n - 1) and that we are currently at row j.
 *
 *	+ Base case: f(n - 1, j) = M[n - 1][j].
 *	+ Recurrence relation:
 *		f(i, j) = min (f(i + 1, j), f(i + 1, g(j + 1, m)), f(i + 1, g(j - 1, m)))
 *	where g(i, m) = i if 0 <= i < m - 1. And g(-1, m) = m - 1, and g(m, m) = 0
 *
 *	+ The answer for the original problem is:
 *		min(f(0, 0), f(0, 1), ..., f(0, m - 1))
 *	+ Time complexity: O(m * n) when using dynamic programming (or memoization) technique
 */

#include <stdio.h>
#include <string.h>

const int MAX_NUM_ROW = 10;
const int MAX_NUM_COL = 100;
const int INFINITY = (1 << 30) + ((1 << 30) - 1);

int findOpPathAndCost(int grid[][MAX_NUM_COL], int numR, int numC, int opPath[MAX_NUM_COL]);
int findMinCostDP(int grid[][MAX_NUM_COL], int numR, int numC, int row, int col, int memoTable[][MAX_NUM_COL]);
void getOpPath(int grid[][MAX_NUM_COL], int numR, int numC, int opCost, int memoTable[][MAX_NUM_COL], int opPath[MAX_NUM_COL]);

int main(void)
{
	int grid[MAX_NUM_ROW][MAX_NUM_COL], opPath[MAX_NUM_COL],
		opCost, numR, numC, r, c;

	while(scanf("%d %d", &numR, &numC) > 0)
	{
		for(r = 0; r < numR; r++)
			for(c = 0; c < numC; c++)
				scanf("%d", &grid[r][c]);

		opCost = findOpPathAndCost(grid, numR, numC, opPath);

		for(c = 0; c < numC; c++)
		{
			if(c > 0)
				printf(" ");
			printf("%d", opPath[c]);
		}
		printf("\n%d\n", opCost);
	}

	return 0;
}

int findOpPathAndCost(int grid[][MAX_NUM_COL], int numR, int numC, int opPath[MAX_NUM_COL])
{
	int memoTable[MAX_NUM_ROW][MAX_NUM_COL], r, c;

	for(r = 0; r < numR; r++)
		for(c = 0; c < numC; c++)
			memoTable[r][c] = INFINITY;

	int minCost = INFINITY, cost;
	for(r = 0; r < numR; r++)
	{
		cost = findMinCostDP(grid, numR, numC, r, 0, memoTable);
		if(cost < minCost)
			minCost = cost;
	}

	/* Print optimal path */
	getOpPath(grid, numR, numC, minCost, memoTable, opPath);

	return minCost; 	
}

int findMinCostDP(int grid[][MAX_NUM_COL], int numR, int numC, int row, int col, int memoTable[][MAX_NUM_COL])
{
	if(col == (numC - 1))
	{
		memoTable[row][col] = grid[row][col];
		return grid[row][col];
	}

	if(memoTable[row][col] != INFINITY)
		return memoTable[row][col];

	int nextR = row, minCost = INFINITY, cost, offset;
	
	for(offset = -1; offset <= 1; offset++)
	{
		nextR = row + offset;
		if(nextR < 0)
			nextR = numR - 1;
		if(nextR >= numR)
			nextR = 0;

		cost = findMinCostDP(grid, numR, numC, nextR, col + 1, memoTable);
		if(cost < minCost)
			minCost = cost;
	}
	minCost += grid[row][col];

	memoTable[row][col] = minCost;
	return minCost;		
}

void getOpPath(int grid[][MAX_NUM_COL], int numR, int numC, int opCost, int memoTable[][MAX_NUM_COL], int opPath[MAX_NUM_COL])
{
	int row, col, minR, prevRow;

	for(row = 0; row < numR; row++)
		if(memoTable[row][0] == opCost)
		{
			opPath[0] = row;
			break;
		}

	for(col = 1; col < numC; col++)
	{
		opCost -= grid[opPath[col - 1]][col - 1];
		
		minR = numR;
		prevRow = opPath[col - 1];
		row = prevRow;
		if(memoTable[row][col] == opCost && row < minR)
			minR = row;
		row = prevRow - 1;
		if(row < 0)
			row = numR - 1;
		if(memoTable[row][col] == opCost && row < minR)
			minR = row;
		row = prevRow + 1;
		if(row >= numR)
			row = 0;
		if(memoTable[row][col] == opCost && row < minR)
			minR = row;

		opPath[col] = minR;
	}
	
	/* The output is 1-indexing */
	for(col = 0; col < numC; col++)
		opPath[col]++;
}
