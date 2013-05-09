#include <stdio.h>
#include <string.h>

#define MAX_VALUE 1000

void prepareMapSumFactorToNum(int mapSumFactorToNum[]);
void calculateSumFactorSieve(int sumFactorSieve[]);

int main(void)
{
    int n, mapSumFactorToNum[MAX_VALUE + 1], caseId;

    prepareMapSumFactorToNum(mapSumFactorToNum);

    caseId = 1;
    while(1)
    {
        scanf("%d", &n);
        if(n == 0)
            break;

        printf("Case %d: %d\n", caseId, mapSumFactorToNum[n]);
        caseId++;
    }

    return 0;
}

void prepareMapSumFactorToNum(int mapSumFactorToNum[])
{
    int sumFactorSieve[MAX_VALUE + 1], n;

    memset(mapSumFactorToNum, -1, (MAX_VALUE + 1) * sizeof(int));
    calculateSumFactorSieve(sumFactorSieve);

    for(n = 1; n <= MAX_VALUE; n++) {
        if(sumFactorSieve[n] <= MAX_VALUE &&
           n > mapSumFactorToNum[sumFactorSieve[n]])
            mapSumFactorToNum[sumFactorSieve[n]] = n;
    }
}

void calculateSumFactorSieve(int sumFactorSieve[])
{
    int n, multipleN;

    sumFactorSieve[0] = -1;     /* Undefined! */
    /* 1 is a factor of every number */
    for(n = 1; n <= MAX_VALUE; n++)
        sumFactorSieve[n] = 1;

    for(n = 2; n <= MAX_VALUE; n++)
        for(multipleN = n; multipleN <= MAX_VALUE; multipleN += n)
            sumFactorSieve[multipleN] += n;
}
