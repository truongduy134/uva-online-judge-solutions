#include <cstdio>
#include <utility>
using namespace std;

#define MAX_SIZE 102

int main(void)
{
    int T, N, M, totalPrice, priceArr[MAX_SIZE][MAX_SIZE], sum = 0, numCol, curCol, curCase;
    int low, high, maxArea, finalCost, len, area, curCost;

  //  freopen("in.txt", "r", stdin);
  //  freopen("out.txt", "w", stdout);

    scanf("%d", &T);
    curCase = 1;
    while(curCase <= T)
    {
        scanf("%d %d %d", &N, &M, &totalPrice);

        for(int i = 0; i < N; i++)
            for(int j = 0; j < M; j++)
                scanf("%d", &priceArr[i][j]);

        numCol = ((M * (M - 1)) >> 1) + M;
        pair<int, int> sumSubArr[N + 1][numCol];

        for(int i = 0; i < N; i++)
        {
            curCol = 0;
            for(int j = 0; j < M; j++)
            {
                sum = 0;

                for(int k = j; k < M; k++)
                {
                    sum += priceArr[i][k];
                    sumSubArr[i][curCol] = make_pair(sum, k - j + 1);
                    curCol++;
                }
            }
        }

        for(int j = 0; j < numCol; j++)
            sumSubArr[N][j] = make_pair(totalPrice + 1, sumSubArr[0][j].second);

        maxArea = 0;
        for(int i = 0; i < numCol; i++)
        {
            sum = 0;
            for(high = 0, low = 0; high <= N; high++)
            {
                sum += sumSubArr[high][i].first;

                if(sum > totalPrice)
                {
                    // Length of the subarray before adding sumSubArr[high][i].first
                    len = high - low;
                    area = len * sumSubArr[high][i].second;
                    curCost = sum - sumSubArr[high][i].first;
                    if(area >= maxArea)
                    {
                        if(area == maxArea && curCost < finalCost)
                        {
                            finalCost = curCost;
                        }

                        if(area > maxArea)
                        {
                            maxArea = area;
                            finalCost = curCost;
                        }
                    }
                    while(sum > totalPrice)
                    {
                        sum -= sumSubArr[low][i].first;
                        low++;
                    }
                }
            }
        }

        printf("Case #%d: %d %d\n", curCase, maxArea, finalCost);
        curCase++;
    }
    return 0;
}
