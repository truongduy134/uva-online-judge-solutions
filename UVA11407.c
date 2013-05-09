#include <stdio.h>
#include <string.h>

#define MAX_VALUE 10000

int getMinSizeSquareSum(int n, int memoTable[]);

int main(void)
{
    int memoTable[MAX_VALUE + 1], T, n;

    memset(memoTable, -1, (MAX_VALUE + 1) * sizeof(int));

    scanf("%d", &T);
    while(T)
    {
        scanf("%d", &n);

        printf("%d\n", getMinSizeSquareSum(n, memoTable));

        T--;
    }
    return 0;
}

int getMinSizeSquareSum(int n, int memoTable[])
{
    if(n <= 0)
        return 0;
    if(n == 1)
        return 1;

    if(memoTable[n] >= 0)
        return memoTable[n];

    /* Trivially, n can be expressed as the sum of 1^2 */
    int minSize = n, nextN, curSize, square;
    for(nextN = 2; (square = nextN * nextN) <= n; nextN++)
    {
        curSize = 1 + getMinSizeSquareSum(n - square, memoTable);
        if(curSize < minSize)
            minSize = curSize;
    }

    memoTable[n] = minSize;
    return minSize;
}
