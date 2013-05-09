#include <stdio.h>

#define MAX_SIZE 20
#define UNPROCESSED -1

long long int calculate(int i, int j, int n, long long int memoTable[][MAX_SIZE + 1]);

int main(void)
{
    long long int memoTable[MAX_SIZE + 1][MAX_SIZE + 1];
    int n, aN1, row, col;

    while(scanf("%d %d", &n, &aN1) > 0)
    {
        /* Initialize the memo table */
        for(row = 0; row <= n; row++)
            for(col = 0; col <= n; col++)
                memoTable[row][col] = UNPROCESSED;

        memoTable[n][1] = (long long int) aN1;

        printf("%lld\n", calculate(1, n, n, memoTable));
    }

    return 0;
}

long long int calculate(int i, int j, int n, long long int memoTable[][MAX_SIZE + 1])
{
    int k;
    long long int maxVal, val, maxValOne, maxValTwo, valOne, valTwo;

    if(memoTable[i][j] != UNPROCESSED)
        return memoTable[i][j];

    if(i >= j)
    {
        if(i < n)
        {
            maxValOne = calculate(i + 1, 1, n, memoTable) + calculate(i + 1, j, n, memoTable);
            for(k = i + 2; k <= n; k++)
            {
                valOne = calculate(k, 1, n, memoTable) + calculate(k, j, n, memoTable);
                if(valOne > maxValOne)
                    maxValOne = valOne;
            }
        }
        else
            maxValOne = 0;

        if(j > 1)
        {
            maxValTwo = calculate(i, 1, n, memoTable) + calculate(n, 1, n, memoTable);
            for(k = 2; k < j; k++)
            {
                valTwo = calculate(i, k, n, memoTable) + calculate(n, k, n, memoTable);
                if(valTwo > maxValTwo)
                    maxValTwo = valTwo;
            }
        }
        else
            maxValTwo = 0;

        maxVal = maxValOne + maxValTwo;
    }
    else
    {
        maxVal = calculate(i, i, n, memoTable) + calculate(i + 1, j, n, memoTable);
        for(k = i + 1; k < j; k++)
        {
            val = calculate(i, k, n, memoTable) + calculate(k + 1, j, n, memoTable);
            if(maxVal < val)
                maxVal = val;
        }
    }

    memoTable[i][j] = maxVal;
    return maxVal;
}
