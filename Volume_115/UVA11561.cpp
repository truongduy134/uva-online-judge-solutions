#include <cstdio>
#include <queue>
#include <utility>

using namespace std;

#define START_POS 'P'
#define GOLD 'G'
#define TRAP 'T'
#define WALL '#'
#define MAX_SIZE 55
#define NUM_DIRECTION 4

const int rowOffset[NUM_DIRECTION] = {0, 0, 1, -1};
const int colOffset[NUM_DIRECTION] = {1, -1, 0, 0};

int findNumGoldWithoutRisking(char grid[][MAX_SIZE + 1], int numRow, int numCol);
pair<int, int> findStartPosition(char grid[][MAX_SIZE + 1], int numRow, int numCol);
int breadthFirstSearchToFindGold(char grid[][MAX_SIZE + 1], int numRow, int numCol,
                                 int startRow, int startCol);
bool isValidCell(int numRow, int numCol, int row, int col);
bool isSafeToContinue(char grid[][MAX_SIZE + 1], int numRow, int numCol, int row, int col);

int main(void)
{
    int numRow, numCol;
    char grid[MAX_SIZE][MAX_SIZE + 1], trash[MAX_SIZE];

    //freopen("in.txt", "r", stdin);

    while(scanf("%d %d", &numCol, &numRow) > 0)
    {
        gets(trash);
        for(int row = 0; row < numRow; row++)
            gets(grid[row]);

        printf("%d\n", findNumGoldWithoutRisking(grid, numRow, numCol));
    }
    return 0;
}

int findNumGoldWithoutRisking(char grid[][MAX_SIZE + 1], int numRow, int numCol)
{
    pair<int, int> startPos = findStartPosition(grid, numRow, numCol);

    if(startPos.first < 0)
        return 0;

    return breadthFirstSearchToFindGold(grid, numRow, numCol, startPos.first, startPos.second);
}

pair<int, int> findStartPosition(char grid[][MAX_SIZE + 1], int numRow, int numCol)
{
    int row, col;

    for(row = 0; row < numRow; row++)
        for(col = 0; col < numCol; col++)
            if(grid[row][col] == START_POS)
                return pair<int, int>(row, col);

    return pair<int, int>(-1, -1);
}

int breadthFirstSearchToFindGold(char grid[][MAX_SIZE + 1], int numRow, int numCol,
                                 int startRow, int startCol)
{
    queue<pair<int, int> > bfsQueue;
    int numGold = 0;

    bfsQueue.push(pair<int, int> (startRow, startCol));
    grid[startRow][startCol] = WALL;

    pair<int, int> curPos;
    int row, col, nextRow, nextCol;
    while(!bfsQueue.empty())
    {
        curPos = bfsQueue.front();
        bfsQueue.pop();
        row = curPos.first;
        col = curPos.second;

        if(isSafeToContinue(grid, numRow, numCol, row, col))
        {
            for(int d = 0; d < NUM_DIRECTION; d++)
            {
                nextRow = row + rowOffset[d];
                nextCol = col + colOffset[d];

                if(isValidCell(numRow, numCol, nextRow, nextCol) &&
                   grid[nextRow][nextCol] != WALL)
                {
                    if(grid[nextRow][nextCol] == GOLD)
                        numGold++;

                    grid[nextRow][nextCol] = WALL;
                    bfsQueue.push(pair<int, int> (nextRow, nextCol));
                }
            }
        }
    }

    return numGold;
}

bool isValidCell(int numRow, int numCol, int row, int col)
{
    if(row < 0 || col < 0 || row >= numRow || col >= numCol)
        return false;
    return true;
}

bool isSafeToContinue(char grid[][MAX_SIZE + 1], int numRow, int numCol, int row, int col)
{
    int newRow, newCol;

    for(int d = 0; d < NUM_DIRECTION; d++)
    {
        newRow = row + rowOffset[d];
        newCol = col + colOffset[d];

        if(isValidCell(numRow, numCol, newRow, newCol) && grid[newRow][newCol] == TRAP)
            return false;
    }

    return true;
}
