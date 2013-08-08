#include <cstdio>
#include <cstring>

using namespace std;

#define NORTH 'N'
#define SOUTH 'S'
#define NOT_PROCESSED '#'
#define FORBID_CELL '.'

#define MAX_SIZE 1000
#define MAX_BRIDGE 100
#define INFINITY 1000000000
#define NUM_DIRECTION 4
const int rowOffset[NUM_DIRECTION] = {0, 0, 1, -1};
const int colOffset[NUM_DIRECTION] = {1, -1, 0, 0};

void markBankOnGrid(char grid[][MAX_SIZE + 1], int numRow, int numCol, int row, int col, char bankId);
int isValidCell(int row, int col, int numRow, int numCol);
void calculateDistanceBetweenBanks(char grid[][MAX_SIZE + 1], int numRow, int numCol, int distanceOnCol[]);
int chooseMinWeightSubsetDP(int mSet[], int mSize, int ind, int mSubsetSize, int minDist,
                            int memoTable[][MAX_BRIDGE + 1]);
int chooseMinWeightSubset(int mSet[], int mSize, int mSubsetSize, int minDist);

int main(void)
{
    int numRow, numCol, numBridge, numSpace, distanceOnCol[MAX_SIZE];
    char grid[MAX_SIZE][MAX_SIZE + 1];

    //freopen("in.txt", "r", stdin);
    while(scanf("%d %d", &numRow, &numCol) > 0)
    {
        scanf("%d %d", &numBridge, &numSpace);

        for(int r = 0; r < numRow; r++)
            scanf("%s", grid[r]);

        markBankOnGrid(grid, numRow, numCol, 0, 0, NORTH);
        markBankOnGrid(grid, numRow, numCol, numRow - 1, 0, SOUTH);

        calculateDistanceBetweenBanks(grid, numRow, numCol, distanceOnCol);

        printf("%d\n", chooseMinWeightSubset(distanceOnCol, numCol, numBridge, numSpace));
    }

    return 0;
}

void markBankOnGrid(char grid[][MAX_SIZE + 1], int numRow, int numCol, int row, int col, char bankId)
{
    grid[row][col] = bankId;

    for(int direction = 0; direction < NUM_DIRECTION; direction++)
    {
        int newRow = row + rowOffset[direction];
        int newCol = col + colOffset[direction];

        if(isValidCell(newRow, newCol, numRow, numCol) && grid[newRow][newCol] == NOT_PROCESSED)
            markBankOnGrid(grid, numRow, numCol, newRow, newCol, bankId);
    }
}

int isValidCell(int row, int col, int numRow, int numCol)
{
    if(row < 0 || col < 0 || row >= numRow || col >= numCol)
        return 0;
    return 1;
}

void calculateDistanceBetweenBanks(char grid[][MAX_SIZE + 1], int numRow, int numCol, int distanceOnCol[])
{
    int col, rowNorth, rowSouth, row;

    for(col = 0; col < numCol; col++)
    {
        // Find the largest rowNorth such that grid[rowNorth][col] is in the NORTH bank.
        for(row = 0; row < numRow && grid[row][col] != SOUTH; row++)
            if(grid[row][col] == NORTH)
                rowNorth = row;

        // Find the smallest rowSouth such that grid[rowSouth][col] is in the SOUTH bank.
        for(row = numRow - 1; row >= 0 && grid[row][col] != NORTH; row--)
            if(grid[row][col] == SOUTH)
                rowSouth = row;

        distanceOnCol[col] = rowSouth - rowNorth - 1;
    }
}

// Return the weight (which is the sum of elements) of the min-weight subset of
//      size mSubsetSize from the original set mSet such that for any two elements
//      mSet[i], mSet[j] of the subset, we have
//                      |j - i| >= minDist
int chooseMinWeightSubset(int mSet[], int mSize, int mSubsetSize, int minDist)
{
    int memoTable[MAX_SIZE][MAX_BRIDGE + 1];

    memset(memoTable, -1, MAX_SIZE * (MAX_BRIDGE + 1) * sizeof(int));

    return chooseMinWeightSubsetDP(mSet, mSize, 0, mSubsetSize, minDist, memoTable);
}

int chooseMinWeightSubsetDP(int mSet[], int mSize, int ind, int mSubsetSize, int minDist,
                            int memoTable[][MAX_BRIDGE + 1])
{
    if(mSubsetSize <= 0)
        return 0;

    if(ind >= mSize)
    {
        if(mSubsetSize > 0)
            return INFINITY;
        return 0;
    }

    if(memoTable[ind][mSubsetSize] >= 0)
        return memoTable[ind][mSubsetSize];

    int minWeight, weight;

    // First do not choose this element
    minWeight = chooseMinWeightSubsetDP(mSet, mSize, ind + 1, mSubsetSize, minDist, memoTable);

    // Choose this element. Then the next one to be considered is at index
    //              ind + minDist + 1 (There are at least minDist columns between them)
    weight = mSet[ind] + chooseMinWeightSubsetDP(mSet, mSize, ind + minDist + 1,
                                                 mSubsetSize - 1, minDist, memoTable);

    if(weight < minWeight)
        minWeight = weight;

    memoTable[ind][mSubsetSize] = minWeight;
    return minWeight;
}
