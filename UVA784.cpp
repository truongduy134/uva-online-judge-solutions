#include <cstdio>
#include <queue>
#include <utility>

using namespace std;

#define START_POS '*'
#define END_CHAR '_'
#define MAX_NUM_ROW 30
#define MAX_NUM_COL 80
#define NUM_DIRECTION 4
#define SPACE ' '
#define PAINT_CHAR '#'

const int rowOffset[NUM_DIRECTION] = {0, 0, 1, -1};
const int colOffset[NUM_DIRECTION] = {1, -1, 0, 0};

bool isSeparatorLine(char line[]);
void paintMaze(char maze[][MAX_NUM_COL + 1], int numRow, int numCol, int startRow, int startCol);
bool isValidCell(int row, int col, int numRow, int numCol);
pair<int, int> findStartRoom(char maze[][MAX_NUM_COL + 1], int numRow);

int main(void)
{
	int T, numRow;
	pair<int, int> startPos;
	char maze[MAX_NUM_ROW + 1][MAX_NUM_COL + 1], trash[MAX_NUM_COL + 1];

	scanf("%d", &T);
	gets(trash);

	while(T)
	{
		numRow = 0;
		while(1)
		{
			gets(maze[numRow]);
			numRow++;
			if(isSeparatorLine(maze[numRow - 1]))
				break;
		}

		startPos = findStartRoom(maze, numRow);

		paintMaze(maze, numRow, MAX_NUM_COL, startPos.first, startPos.second);

		for(int row = 0; row < numRow; row++)
			printf("%s\n", maze[row]);

		T--;
	}
	return 0;
}

bool isSeparatorLine(char line[])
{
	for(int ind = 0; line[ind] != '\0'; ind++)
		if(line[ind] != END_CHAR)
			return false;
	return true;
}

void paintMaze(char maze[][MAX_NUM_COL + 1], int numRow, int numCol, int startRow, int startCol)
{
	queue<pair<int, int> > cellQueue;
	cellQueue.push(pair<int, int> (startRow, startCol));
	maze[startRow][startCol] = PAINT_CHAR;

	pair<int, int> curCell;
	int curRow, curCol, nextRow, nextCol;
	while(!cellQueue.empty())
	{
		curCell = cellQueue.front();
		cellQueue.pop();

		curRow = curCell.first;
		curCol = curCell.second;

		for(int direction = 0; direction < NUM_DIRECTION; direction++)
		{
			nextRow = curRow + rowOffset[direction];
			nextCol = curCol + colOffset[direction];

			if(isValidCell(nextRow, nextCol, numRow, numCol) &&
				maze[nextRow][nextCol] == SPACE)
			{
				maze[nextRow][nextCol] = PAINT_CHAR;
				cellQueue.push(pair<int, int> (nextRow, nextCol));
			}
		}
	}
}

bool isValidCell(int row, int col, int numRow, int numCol)
{
	if(row < 0 || col < 0 || row >= numRow || col >= numCol)
		return false;
	return true;
}

pair<int, int> findStartRoom(char maze[][MAX_NUM_COL + 1], int numRow)
{
	for(int row = 0; row < numRow; row++)
		for(int col = 0; maze[row][col] != '\0'; col++)
			if(maze[row][col] == START_POS)
				return pair<int, int> (row, col);

	return pair<int, int> (-1, -1);		// dummy
}
