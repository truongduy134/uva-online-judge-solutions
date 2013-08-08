#include <stdio.h>

#define NUM_DENOM 11
#define MAX_AMOUNT 6001
const int denomArr[NUM_DENOM] = {10000, 5000, 2000, 1000, 500, 200, 100, 50, 20, 10, 5};
unsigned long long int memoTable[MAX_AMOUNT][NUM_DENOM];

unsigned long long int countNumChange(int amount, int maxDenomInd)
{
    /* Base case */
    if(amount == 0 || maxDenomInd == NUM_DENOM - 1)
        return 1;
    if(maxDenomInd >= NUM_DENOM)
        return 0;

    if(memoTable[amount / 5][maxDenomInd] != (unsigned long long int) (-1))
        return memoTable[amount / 5][maxDenomInd];

    unsigned long long int numWay = 0;
    int amountLeft = amount;
    while(amountLeft >= 0)
    {
        numWay += countNumChange(amountLeft, maxDenomInd + 1);
        amountLeft -= denomArr[maxDenomInd];
    }

    memoTable[amount / 5][maxDenomInd] = numWay;

    return numWay;
}
int main(void)
{
    int dollarPart, centPart, amount, i, j;
    unsigned long long int numWay;

    for(i = 0; i < MAX_AMOUNT; i++)
            for(j = 0; j < NUM_DENOM; j++)
                memoTable[i][j] = (unsigned long long int) -1;

    while(1)
    {
        scanf("%d.%d", &dollarPart, &centPart);
        if(dollarPart == 0 && centPart == 0)
            break;

        amount = dollarPart * 100 + centPart;

        if(centPart % 5)
            numWay = 0;
        else
            numWay = countNumChange(amount, 0);

        printf("%3d.%02d%17llu\n", dollarPart, centPart, numWay);
    }
    return 0;
}
