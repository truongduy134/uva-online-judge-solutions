#include <cstdio>
#include <cctype>

using namespace std;

#define MAX_COL 15
unsigned long long memoTable[MAX_COL][MAX_COL];

unsigned long long countNumArrange(int pos[], int numCol, int col, int row)
{
    if(col == numCol - 1)
        return 1;

    if(memoTable[row][col] != (unsigned long long) (-1))
        return memoTable[row][col];

    unsigned long long numWay = 0;
    int startR = 0;
    int endR = numCol - 1;
    if(pos[col + 1] >= 0)
    {
        startR = pos[col + 1];
        endR = startR;
    }

    for(int r = startR; r <= endR; r++)
        if(r < row - 1 || r > row + 1)
            numWay += countNumArrange(pos, numCol, col + 1, r);

    memoTable[row][col] = numWay;

    return numWay;
}
int main(void)
{
    int numCol, pos[MAX_COL], numRow;
    char line[MAX_COL << 1];
    unsigned long long numArrange;

   // freopen("in.txt", "r", stdin);
   // freopen("out.txt", "w", stdout);

    while(gets(line) != NULL)
    {
        if(line[0] == '\0')
            continue;
        for(numCol = 0; line[numCol] != '\0'; numCol++)
        {
            if(line[numCol] == '?')
                pos[numCol] = -1;
            else
            {
                if(isdigit(line[numCol]))
                    pos[numCol] = line[numCol] - '1';
                else
                    pos[numCol] = line[numCol] - 'A' + 9;
            }
        }
        numRow = numCol;

        for(int i = 0; i < numCol; i++)
            for(int j = 0; j < numCol; j++)
                memoTable[i][j] = (unsigned long long) (-1);

        numArrange = 0;
        if(pos[0] < 0)
        {
            for(int r = 0; r < numRow; r++)
                numArrange += countNumArrange(pos, numCol, 0, r);
        }
        else
            numArrange = countNumArrange(pos, numCol, 0, pos[0]);

        printf("%llu\n", numArrange);
    }
    return 0;
}
