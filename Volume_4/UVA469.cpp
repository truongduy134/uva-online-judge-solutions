/*******************************************************************************
 * Author: Nguyen Truong Duy
 ********************************************************************************/

/* Methodology
 *	+ This can be solved using flood-fill technique, which can be implemented
 *		either by DFS (Depth-First Search) or BFS (Breadth-First Search)
 *
 *	+ Time complexity: O(m * n)
 */

#include <cstdio>
#include <queue>
#include <utility>
#include <cstring>

using namespace std;

const int MAX_SIZE = 100;
const char LAND = 'L';
const char WATER = 'W';
const int NUM_DIRECTION = 8;
const int COORD_OFFSET[][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}, {1, 1}, {-1, -1}, {-1, 1}, {1, -1}};

bool IsValidCell(int row, int col, int numr, int numc);
int ComputeSizeWaterRegion(char grid[MAX_SIZE][MAX_SIZE], int numr, int numc, int srow, int scol);

int main(void)
{
	int numcase, numr, numc, row, col;
	char grid[MAX_SIZE][MAX_SIZE], trash[MAX_SIZE + 1], queryline[MAX_SIZE + 1];

	scanf("%d", &numcase);
	gets(trash);
	gets(trash);
	while(numcase)
	{
		numr = 0;
		while(1)
		{
			gets(grid[numr]);
			if(grid[numr][0] != LAND && grid[numr][0] != WATER)
			{
				strcpy(queryline, grid[numr]);
				break;
			}
			numr++;
		}
		numc = strlen(grid[0]);

		do
		{
			sscanf(queryline, "%d %d", &row, &col);
			row--;
			col--;
			printf("%d\n", ComputeSizeWaterRegion(grid, numr, numc, row, col));
		} while(gets(queryline) != NULL && queryline[0] != '\0');

		if(numcase > 1)
			printf("\n");
		numcase--;
	}

	return 0;
}

int ComputeSizeWaterRegion(char grid[MAX_SIZE][MAX_SIZE], int numr, int numc, int srow, int scol)
{
	if(grid[srow][scol] != WATER)
		return 0;

	bool visited[MAX_SIZE][MAX_SIZE];
	for(int row = 0; row < numr; row++)
		for(int col = 0; col < numc; col++)
			visited[row][col] = false;

	queue<pair<int, int> > qcell;
	visited[srow][scol] = true;
	qcell.push(pair<int, int> (srow, scol));

	int area = 1;
	while(!qcell.empty())
	{
		pair<int, int> coord = qcell.front();
		qcell.pop();
		int crow = coord.first;
		int ccol = coord.second;

		for(int direction = 0; direction < NUM_DIRECTION; direction++)
		{
			int nrow = crow + COORD_OFFSET[direction][0];
			int ncol = ccol + COORD_OFFSET[direction][1];
			if(IsValidCell(nrow, ncol, numr, numc) && visited[nrow][ncol] == false &&
			   grid[nrow][ncol] == WATER)
			{
				visited[nrow][ncol] = true;
				qcell.push(pair<int, int>(nrow, ncol));
				area++;
			}
		}
	}

	return area;
}

bool IsValidCell(int row, int col, int numr, int numc)
{
	if(row < 0 || col < 0 || row >= numr || col >= numc)
		return false;
	return true;
}
