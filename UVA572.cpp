#include <cstdio>
#include <queue>
#include <utility>

using namespace std;

#define MAX_SIZE 100
#define OIL '@'
#define NON_OIL '*'
#define NUM_DIRECTION 8

const int rowDirect[NUM_DIRECTION] = {0, 0, 1, 1, 1, -1, -1, -1};
const int colDirect[NUM_DIRECTION] = {1, -1, 1, -1, 0, 1, -1, 0};

int countNumOilDeposit(char oilMap[][MAX_SIZE + 1], int numRow, int numCol);
void breadthFirstSearch(char oilMap[][MAX_SIZE + 1], int numRow, int numCol, int sRow, int sCol);
bool isValid(int numRow, int numCol, int row, int col);

int main(void)
{
    int numRow, numCol;
    char oilMap[MAX_SIZE][MAX_SIZE + 1], trash[3];

    //freopen("in.txt", "r", stdin);

    while(1)
    {
        scanf("%d %d", &numRow, &numCol);
        gets(trash);
        if(numRow == 0 && numCol == 0)
            break;

        for(int i = 0; i < numRow; i++)
            gets(oilMap[i]);

        printf("%d\n", countNumOilDeposit(oilMap, numRow, numCol));
    }

    return 0;
}

int countNumOilDeposit(char oilMap[][MAX_SIZE + 1], int numRow, int numCol)
{
    int numDeposit = 0;

    for(int row = 0; row < numRow; row++)
        for(int col = 0; col < numCol; col++)
            if(oilMap[row][col] == OIL)
            {
                numDeposit++;
                // Explore and eliminate this oild deposit
                breadthFirstSearch(oilMap, numRow, numCol, row, col);
            }

    return numDeposit;
}

void breadthFirstSearch(char oilMap[][MAX_SIZE + 1], int numRow, int numCol, int sRow, int sCol)
{
    queue<pair<int, int> > vQueue;

    vQueue.push(make_pair(sRow, sCol));
    oilMap[sRow][sCol] = NON_OIL;

    pair<int, int> curLoc;
    int nextR, nextC;

    while(!vQueue.empty())
    {
        curLoc = vQueue.front();
        vQueue.pop();

        for(int direct = 0; direct < NUM_DIRECTION; direct++)
        {
            nextR = curLoc.first + rowDirect[direct];
            nextC = curLoc.second + colDirect[direct];

            if(isValid(numRow, numCol, nextR, nextC) && oilMap[nextR][nextC] == OIL)
            {
                oilMap[nextR][nextC] = NON_OIL;
                vQueue.push(make_pair(nextR, nextC));
            }
        }
    }
}

bool isValid(int numRow, int numCol, int row, int col)
{
    if(row < 0 || col < 0 || row >= numRow || col >= numCol)
        return false;

    return true;
}
