#include <cstdio>
#include <queue>
#include <utility>

using namespace std;

#define EAGLE '1'
#define NON_EAGLE '0'
#define MAX_SIZE 27
#define NUM_DIRECTION 8

const int rowDirection[NUM_DIRECTION] = {0, 0, 1, -1, 1, 1, -1, -1};
const int colDirection[NUM_DIRECTION] = {1, -1, 0, 0, 1, -1, 1, -1};

int countNumEagle(char image[][MAX_SIZE + 1], int mSize);
void markEagleRegion(char image[][MAX_SIZE + 1], int mSize, int row, int col);
bool isValidCoord(int row, int col, int mSize);

int main(void)
{
    int mSize, imageId;
    char image[MAX_SIZE + 1][MAX_SIZE + 1], trash[MAX_SIZE + 1];

 //   freopen("in.txt", "r", stdin);

    imageId = 1;
    while(scanf("%d", &mSize) > 0)
    {
        gets(trash);
        for(int i = 0; i < mSize; i++)
            gets(image[i]);

        printf("Image number %d contains %d war eagles.\n", imageId, countNumEagle(image, mSize));

        imageId++;
    }

    return 0;
}

int countNumEagle(char image[][MAX_SIZE + 1], int mSize)
{
    int numEagle = 0;

    for(int r = 0; r < mSize; r++)
        for(int c = 0; c < mSize; c++)
            if(image[r][c] == EAGLE)
            {
                numEagle++;
                markEagleRegion(image, mSize, r, c);
            }

    return numEagle;
}

void markEagleRegion(char image[][MAX_SIZE + 1], int mSize, int row, int col)
{
    queue<pair<int, int> > cellQueue;
    cellQueue.push(make_pair(row, col));

    image[row][col] = NON_EAGLE;

    pair<int, int> curCell;
    int nextRow, nextCol;
    while(!cellQueue.empty())
    {
        curCell = cellQueue.front();
        cellQueue.pop();

        for(int direction = 0; direction < NUM_DIRECTION; direction++)
        {
            nextRow = curCell.first + rowDirection[direction];
            nextCol = curCell.second + colDirection[direction];

            if(isValidCoord(nextRow, nextCol, mSize) && image[nextRow][nextCol] == EAGLE)
            {
                image[nextRow][nextCol] = NON_EAGLE;
                cellQueue.push(make_pair(nextRow, nextCol));
            }
        }
    }
}

bool isValidCoord(int row, int col, int mSize)
{
    if(row < 0 || col < 0 || row >= mSize || col >= mSize)
        return false;

    return true;
}
