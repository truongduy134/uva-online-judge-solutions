#include <cstdio>
#include <queue>
#include <utility>

using namespace std;

#define NUM_DIRECTION 6
#define MAX_SIZE 30
#define START 'S'
#define END 'E'
#define EMPTY '.'
#define ROCK '#'

const int rowOffset[NUM_DIRECTION] = {0, 0, 0, 0, -1, 1};
const int colOffset[NUM_DIRECTION] = {1, -1, 0, 0, 0, 0};
const int heightOffset[NUM_DIRECTION] = {0, 0, 1, -1, 0, 0};

struct Position 
{
	int height, row, col;

	Position() : height(0), row(0), col(0) {}
	Position(int mHeight, int mRow, int mCol) : height(mHeight), row(mRow), col(mCol) {}
	Position(const Position & another) : height(another.height), row(another.row), col(another.col) {}

	Position & operator= (const Position & another);
	bool operator== (const Position & another) const;
};

Position & Position::operator= (const Position & another)
{
	if(this == &another)
		return *this;
	height = another.height;
	row = another.row;
	col = another.col;

	return *this;
}

bool Position::operator== (const Position & another) const
{
	return height == another.height && row == another.row && col == another.col;
}

Position findPosition(char dungeon[][MAX_SIZE][MAX_SIZE + 1], int numHeight, int numRow, int numCol, char pos);
int findShortestPathBFS(char dungeon[][MAX_SIZE][MAX_SIZE + 1], int numHeight, int numRow, int numCol, Position & startPos);
bool isValidPosition(const Position & pos, int numHeight, int numRow, int numCol);

int main(void)
{
	char dungeon[MAX_SIZE][MAX_SIZE][MAX_SIZE + 1];
	int numRow, numCol, numHeight, timeEscape;

	while(1)
	{
		scanf("%d %d %d", &numHeight, &numRow, &numCol);
		if(numHeight == 0 && numRow == 0 && numCol == 0)
			break;

		for(int height = 0; height < numHeight; height++)
			for(int row = 0; row < numRow; row++)
				scanf("%s", dungeon[height][row]);

		Position startPos = findPosition(dungeon, numHeight, numRow, numCol, START);

		timeEscape = findShortestPathBFS(dungeon, numHeight, numRow, numCol, startPos);
		if(timeEscape < 0)
			printf("Trapped!\n");
		else
			printf("Escaped in %d minute(s).\n", timeEscape);
	}
	return 0;
}

Position findPosition(char dungeon[][MAX_SIZE][MAX_SIZE + 1], int numHeight, int numRow, int numCol, char pos)
{
	for(int height = 0; height < numHeight; height++)
		for(int row = 0; row < numRow; row++)
			for(int col = 0; col < numCol; col++)
				if(dungeon[height][row][col] == pos)
					return Position(height, row, col);

	return Position(-1, -1, -1); 	// Dummy
}

int findShortestPathBFS(char dungeon[][MAX_SIZE][MAX_SIZE + 1], int numHeight, int numRow, int numCol, Position & startPos)
{
	int timeEscape;

	queue<pair<Position, int> > posQueue;
	posQueue.push(pair<Position, int> (startPos, 0));
	dungeon[startPos.height][startPos.row][startPos.col] = ROCK;

	Position curPos, nextPos;

	while(!posQueue.empty())
	{
		curPos = posQueue.front().first;
		timeEscape = posQueue.front().second;
		posQueue.pop();

		for(int direction = 0; direction < NUM_DIRECTION; direction++)
		{
			nextPos = Position(curPos.height + heightOffset[direction],
					   curPos.row + rowOffset[direction],
					   curPos.col + colOffset[direction]);

			if(isValidPosition(nextPos, numHeight, numRow, numCol) &&
			   dungeon[nextPos.height][nextPos.row][nextPos.col] != ROCK)
			{
				if(dungeon[nextPos.height][nextPos.row][nextPos.col] == END)
					return timeEscape + 1;
				
				dungeon[nextPos.height][nextPos.row][nextPos.col] = ROCK;
				posQueue.push(pair<Position, int> (nextPos, timeEscape + 1));
			}   
		}		
	}
	return -1;
}

bool isValidPosition(const Position & pos, int numHeight, int numRow, int numCol)
{
	if(pos.height < 0 || pos.row < 0 || pos.col < 0)
		return false;
	if(pos.height >= numHeight || pos.row >= numRow || pos.col >= numCol)
		return false;
	return true;
}
