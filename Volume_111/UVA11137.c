#include <stdio.h>
#include <string.h>

const int NUM_DENOM = 21;
const int UPPER_BOUND_AMOUNT = 10000;

unsigned long long int countNumWayToChange(int amount, int maxCoinInd, int denomArr[], unsigned long long int memoTable[][NUM_DENOM]);
void prepareDenomArr(int denomArr[]);

int main(void)
{
	int denomArr[NUM_DENOM];
	int amount;
	unsigned long long int memoTable[UPPER_BOUND_AMOUNT][NUM_DENOM];

	prepareDenomArr(denomArr);
	memset(memoTable, 0, UPPER_BOUND_AMOUNT * NUM_DENOM * sizeof(unsigned long long int));
	
	while(scanf("%d", &amount) > 0)
	{
		printf("%llu\n", countNumWayToChange(amount, NUM_DENOM - 1, denomArr, memoTable));
	}
	return 0;
}

void prepareDenomArr(int denomArr[])
{
	int i = 1;

	for(i = 1; i <= NUM_DENOM; i++)
		denomArr[i - 1] = i * i * i;
}

unsigned long long int countNumWayToChange(int amount, int maxCoinInd, int denomArr[], unsigned long long int memoTable[][NUM_DENOM])
{
	if(amount < 0)
		return 0;

	if(amount == 0)
		return 1;

	if(maxCoinInd == 0)
	{
		/* That means we can only use denominator 1 */
		return 1;
	}

	if(memoTable[amount][maxCoinInd] > 0)
		return memoTable[amount][maxCoinInd];

	unsigned long long int numWayToChange = 0;

	numWayToChange += countNumWayToChange(amount, maxCoinInd - 1, denomArr, memoTable) +
			  countNumWayToChange(amount - denomArr[maxCoinInd], maxCoinInd, denomArr, memoTable);

	memoTable[amount][maxCoinInd] = numWayToChange;

	return numWayToChange;
}
