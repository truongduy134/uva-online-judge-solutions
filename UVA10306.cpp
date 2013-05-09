#include <cstdio>

using namespace std;

#define MAX_SIZE 310
#define INFINITY 1000000

int findMinCoinTopDownDB(int minCoinExchange[][MAX_SIZE], int oldVal[], int newVal[], int numCoinType, int totalOldVal, int totalNewVal)
{
   // printf("totalOldVal = %d\n", totalOldVal);
   // printf("totalNewVal = %d\n", totalNewVal);
    if(totalOldVal == 0 && totalNewVal == 0)
        return 0;
    if(totalOldVal < 0 || totalNewVal < 0)
    {
  //      printf("Return here INIFINITY\n");
        return INFINITY;
    }

    if(minCoinExchange[totalOldVal][totalNewVal] >= 0)
        return minCoinExchange[totalOldVal][totalNewVal];

    int minCoin = INFINITY, numCoin;
    for(int i = 0; i < numCoinType; i++)
    {
    //    printf("numCoinType = %d\n", numCoinType);
    //    printf("oldVal[i] = %d\n", oldVal[i]);
        numCoin = 1 + findMinCoinTopDownDB(minCoinExchange, oldVal, newVal, numCoinType, totalOldVal - oldVal[i], totalNewVal - newVal[i]);
        if(minCoin > numCoin)
            minCoin = numCoin;
    }

    minCoinExchange[totalOldVal][totalNewVal] = minCoin;

    return minCoin;
}
int main(void)
{
    int T, numCoinType, modulus, oldVal[MAX_SIZE], newVal[MAX_SIZE], minCoin, numCoin;
    int minCoinExchange[MAX_SIZE][MAX_SIZE];

  // freopen("in.txt", "r", stdin);
  //  freopen("out.txt", "w", stdout);

    scanf("%d", &T);

    while(T)
    {
        scanf("%d %d", &numCoinType, &modulus);

        for(int i = 0; i < numCoinType; i++)
            scanf("%d %d", &oldVal[i], &newVal[i]);

        // Initialize the memo table
        for(int i = 0; i < MAX_SIZE; i++)
            for(int j = 0; j < MAX_SIZE; j++)
                minCoinExchange[i][j] = -1;

        minCoin = INFINITY;
        for(int x = 0; x <= modulus; x++)
            for(int y = 0; y <= modulus; y++)
                if(x * x + y * y == modulus * modulus)
                {
                    numCoin = findMinCoinTopDownDB(minCoinExchange, oldVal, newVal, numCoinType, x, y);
                    if(minCoin > numCoin)
                        minCoin = numCoin;
                }

        if(minCoin >= INFINITY)
            printf("not possible\n");
        else
            printf("%d\n", minCoin);

        T--;
    }
}
