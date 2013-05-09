#include <stdio.h>
#include <string.h>

/* Methodology:
 *	f(i, j) = the longest run on a snowboard starting at cell (i, j)
 *
 *	Let S = {(k, l) | (k, l) is at left, right, above, or below cell (i, j)
 *			and height(i, j) > height(k, l)
 *	Then f(i, j) = 1 if S is empty
 *	Otherwise, f(i, j) = 1 + max {f(k, l) | (k, l) in S }
 *
 * Time complexity: O(M * N) to compute all f(i, j) in an M x N grid 
 */

#define MAX_SIZE 100
#define MAX_LEN_STR 1000
#define NUM_DIRECTION 4

const int rowOffset[NUM_DIRECTION] = {0, 0, 1, -1};
const int colOffset[NUM_DIRECTION] = {1, -1, 0, 0};

int findLongestLengthDP(int heightArr[][MAX_SIZE], int numRow, int numCol, int row, int col, int longestLengthMemo[][MAX_SIZE]);
int isValidCell(int row, int col, int numRow, int numCol);

int main(void)
{
	char name[MAX_LEN_STR + 1];
	int heightArr[MAX_SIZE][MAX_SIZE], longestLength[MAX_SIZE][MAX_SIZE],
		numRow, numCol, T, row, col, maxLength, length;

	scanf("%d", &T);
	while(T)
	{
		scanf("%s %d %d", name, &numRow, &numCol);
		
		for(row = 0; row < numRow; row++)
			for(col = 0; col < numCol; col++)
				scanf("%d", &heightArr[row][col]);

		memset(longestLength, 0, MAX_SIZE * MAX_SIZE * sizeof(int));

		maxLength = 0;
		for(row = 0; row < numRow; row++)
			for(col = 0; col < numCol; col++)
			{
				length = findLongestLengthDP(heightArr, numRow, numCol, row, col, longestLength);
				if(length > maxLength)
					maxLength = length;
			}

		printf("%s: %d\n", name, maxLength);

		T--;
	}
	return 0;
}

int findLongestLengthDP(int heightArr[][MAX_SIZE], int numRow, int numCol, int row, int col, int longestLengthMemo[][MAX_SIZE])
{
	if(longestLengthMemo[row][col] > 0)
		return longestLengthMemo[row][col];

	int nextRow, nextCol, maxLength = 0, length, direction;

	for(direction = 0; direction < NUM_DIRECTION; direction++)
	{
		nextRow = row + rowOffset[direction];
		nextCol = col + colOffset[direction];

		if(isValidCell(nextRow, nextCol, numRow, numCol) &&
		   heightArr[nextRow][nextCol] < heightArr[row][col])
		{
			length = findLongestLengthDP(heightArr, numRow, numCol, nextRow, nextCol, longestLengthMemo);
			if(maxLength < length)
				maxLength = length;
		}
	}

	longestLengthMemo[row][col] = 1 + maxLength;
	return longestLengthMemo[row][col];
}

int isValidCell(int row, int col, int numRow, int numCol)
{
	if(row < 0 || col < 0 || row >= numRow || col >= numCol)
		return 0;
	return 1;
}
