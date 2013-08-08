/******************************************************************************
 * Author: Nguyen Truong Duy
 ******************************************************************************/
#include <cstdio>
#include <queue>
#include <algorithm>
#include <utility>

using namespace std;

#define NUM_DIRECTION 4
#define MAX_SIZE 50
#define NON_HOLE '.'

const int rowOffset[NUM_DIRECTION] = {0, 0, 1, -1};
const int colOffset[NUM_DIRECTION] = {1, -1, 0, 0};

void getAllHoleInOrder(char map[][MAX_SIZE + 1], int numRow, int numCol, vector<pair<int, char> > & holeVect);
pair<int, char> fillHole(char map[][MAX_SIZE + 1], int numRow, int numCol, int startRow, int startCol);
bool isValidCell(int row, int col, int numRow, int numCol);
bool compareHole(const pair<int, char> & one, const pair<int, char> & two);

int main(void)
{
	int numRow, numCol, caseId;
	char map[MAX_SIZE][MAX_SIZE + 1];
	vector<pair<int, char> > holeVect;
	
	caseId = 1;
	while(1)
	{
		scanf("%d %d", &numRow, &numCol);
		if(!(numRow || numCol))
			break;

		for(int row = 0; row < numRow; row++)
			scanf("%s", map[row]);

		getAllHoleInOrder(map, numRow, numCol, holeVect);

		printf("Problem %d:\n", caseId);
		for(int i = 0; i < (int) holeVect.size(); i++)
			printf("%c %d\n", holeVect[i].second, holeVect[i].first);

		caseId++;
	}
	return 0;
}

bool compareHole(const pair<int, char> & one, const pair<int, char> & two)
{
	if(one.first > two.first)
		return true;
	if(one.first < two.first)
		return false;
	return one.second < two.second;
}

void getAllHoleInOrder(char map[][MAX_SIZE + 1], int numRow, int numCol, vector<pair<int, char> > & holeVect)
{
	holeVect.clear();

	pair<int, char> hole;
	for(int row = 0; row < numRow; row++)
		for(int col = 0; col < numCol; col++)
			if(map[row][col] != NON_HOLE)
			{
				hole = fillHole(map, numRow, numCol, row, col);
				holeVect.push_back(hole);
			}

	sort(holeVect.begin(), holeVect.end(), compareHole);
}

pair<int, char> fillHole(char map[][MAX_SIZE + 1], int numRow, int numCol, int startRow, int startCol)
{
	queue<pair<int, int> > vQueue;

	char holeId = map[startRow][startCol];
	vQueue.push(pair<int, int> (startRow, startCol));
	map[startRow][startCol] = NON_HOLE;

	int size = 0, curRow, curCol, nextRow, nextCol;
	while(!vQueue.empty())
	{
		curRow = vQueue.front().first;
		curCol = vQueue.front().second;
		vQueue.pop();

		size++;

		for(int direction = 0; direction < NUM_DIRECTION; direction++)
		{
			nextRow = curRow + rowOffset[direction];
			nextCol = curCol + colOffset[direction];

			if(isValidCell(nextRow, nextCol, numRow, numCol) &&
			   map[nextRow][nextCol] == holeId)
			{
				map[nextRow][nextCol] = NON_HOLE;
				vQueue.push(pair<int, int> (nextRow, nextCol));
			}
		}
	}

	return pair<int, char> (size, holeId);
}

bool isValidCell(int row, int col, int numRow, int numCol)
{
	if(row < 0 || col < 0 || row >= numRow || col >= numCol)
		return false;
	return true;
}
