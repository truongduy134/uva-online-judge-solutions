/*******************************************************************************
 * Author: Nguyen Truong Duy
 ********************************************************************************/

/* Methodology:
 *	+ We can use greedy approach to solve this problem.
 *	+ We traverse the grid from left to right, from top to bottom.
 *	+ For each entry G[i][j], if it is empty, we choose a letter L which is the
 *		smallest alphabet that is different from non-empty neighbors of G[i][j]
 *		(there are at most 4 non-empty neighbors)
 *	  Then we let G[i][j] = L.
 *
 * 	+ Time complexity: O(N^2)
 */

#include <stdio.h>

#define MAX_SIZE 10
#define EMPTY '.'
#define NUM_ALPHA 26
#define NUM_DIRECTION 4

int DIRECTION_OFFSET[NUM_DIRECTION][4] = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};

void FillGrid(char grid[MAX_SIZE][MAX_SIZE + 1], int msize);
char GetMinChar(char grid[MAX_SIZE][MAX_SIZE + 1], int msize, int row, int col);
int IsValidCell(int msize, int row, int col);

int main(void)
{
	char grid[MAX_SIZE][MAX_SIZE + 1];
	int numcase, caseid, msize;

	scanf("%d", &numcase);
	caseid = 1;
	while(caseid <= numcase)
	{
		scanf("%d", &msize);
		int row;
		for(row = 0; row < msize; row++)
			scanf("%s", grid[row]);

		FillGrid(grid, msize);

		printf("Case %d:\n", caseid);
		for(row = 0; row < msize; row++)
			printf("%s\n", grid[row]);

		caseid++;
	}

	return 0;
}

void FillGrid(char grid[MAX_SIZE][MAX_SIZE + 1], int msize)
{
	int row, col;

	for(row = 0; row < msize; row++)
		for(col = 0; col < msize; col++)
			if(grid[row][col] == EMPTY)
				grid[row][col] = GetMinChar(grid, msize, row, col);
}

char GetMinChar(char grid[MAX_SIZE][MAX_SIZE + 1], int msize, int row, int col)
{
	int ispresent[NUM_ALPHA] = {0}, direction, nextrow, nextcol, i;

	for(direction = 0;  direction < NUM_DIRECTION; direction++)
	{
		nextrow = row + DIRECTION_OFFSET[direction][0];
		nextcol = col + DIRECTION_OFFSET[direction][1];

		if(IsValidCell(msize, nextrow, nextcol) && grid[nextrow][nextcol] != EMPTY)
			ispresent[(int) grid[nextrow][nextcol] - 'A'] = 1;
	}

	for(i = 0; i < NUM_ALPHA; i++)
		if(!ispresent[i])
			return i + 'A';
	return '\0';	/* Dummy value */
}

int IsValidCell(int msize, int row, int col)
{
	if(row < 0 || col < 0 || row >= msize || col >= msize)
		return 0;
	return 1;
}
