#include <cstdio>
#include <cstring>

#define MAX_NUM 10002

int main(void)
{
    int sievePosition[MAX_NUM], N, Q, caseId, x, numX, numPrev, maxVal;

   // freopen("in.txt", "r", stdin);

    caseId = 1;
    while(1)
    {
        scanf("%d %d", &N, &Q);
        if(N == 0 && Q == 0)
            break;

        memset(sievePosition, 0, sizeof(int) * MAX_NUM);

        maxVal = 0;
        for(int i = 0; i < N; i++)
        {
            scanf("%d", &x);
            sievePosition[x]++;
            if(x > maxVal)
                maxVal = x;
        }


        for(int i = 1; i <= maxVal; i++)
            sievePosition[i] += sievePosition[i - 1];

        printf("CASE# %d:\n", caseId);

        for(int i = 0; i < Q; i++)
        {
            scanf("%d", &x);
            numX = sievePosition[x];
            if(x > 0)
                numX -= sievePosition[x - 1];
            if(numX <= 0)
                printf("%d not found\n", x);
            else
            {
                numPrev = 0;
                if(x > 0)
                    numPrev = sievePosition[x - 1];
                printf("%d found at %d\n", x, numPrev + 1);
            }
        }

        caseId++;
    }
    return 0;
}
