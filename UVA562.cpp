#include <cstdio>

#define MAX_COIN 100
#define MAX_HALF_VALUE 25001

#define MINUS_INFINITY -1000000

int memoTable[MAX_COIN][MAX_HALF_VALUE];

int runKnapsackDP(int coinArr[], int curCoinInd, int maxSizeLeft)
{
    if(maxSizeLeft < 0)
        return MINUS_INFINITY;
    if(curCoinInd < 0)
        return 0;

    if(memoTable[curCoinInd][maxSizeLeft] >= 0)
        return memoTable[curCoinInd][maxSizeLeft];

    int maxVal = runKnapsackDP(coinArr, curCoinInd - 1, maxSizeLeft);
    int valTaken = coinArr[curCoinInd] + runKnapsackDP(coinArr, curCoinInd - 1,
                                                       maxSizeLeft - coinArr[curCoinInd]);
    if(valTaken > maxVal)
        maxVal = valTaken;

    memoTable[curCoinInd][maxSizeLeft] = maxVal;

    return maxVal;
}

int main(void)
{
    int N, coinArr[MAX_COIN], T, sumVal = 0, upperbound, maxOfSmallerSet;

  //  freopen("in.txt", "r", stdin);

    scanf("%d", &T);
    while(T)
    {
        scanf("%d", &N);

        sumVal = 0;
        for(int i = 0; i < N; i++)
        {
            scanf("%d", &coinArr[i]);
            sumVal += coinArr[i];
        }

        upperbound = sumVal >> 1;

        for(int i = 0; i < N; i++)
            for(int j = 0; j <= upperbound; j++)
                memoTable[i][j] = -1;

        maxOfSmallerSet = runKnapsackDP(coinArr, N - 1, upperbound);
        printf("%d\n", sumVal - (maxOfSmallerSet << 1));

        T--;
    }
    return 0;
}
