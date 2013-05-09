#include <stdio.h>
#include <string.h>

const int NUM_DENOM = 5;
const int DENOM_ARR[] = {1, 5, 10, 25, 50};
const int MAX_AMOUNT = 30000;

unsigned long long int countNumWayToChange(int amount, int maxCoinInd, unsigned long long int memoTable[][NUM_DENOM]);

int main(void)
{
	int amount;
	unsigned long long int memoTable[MAX_AMOUNT + 1][NUM_DENOM], numWay;

	memset(memoTable, 0, (MAX_AMOUNT + 1) * NUM_DENOM * sizeof(unsigned long long int));

	while(scanf("%d", &amount) > 0)
	{
		numWay = countNumWayToChange(amount, NUM_DENOM - 1, memoTable);

		if(numWay > 1)
			printf("There are %llu ways to produce %d cents change.\n", numWay, amount);
		else
			printf("There is only 1 way to produce %d cents change.\n", amount);		
	}
	 
	return 0;
}

unsigned long long int countNumWayToChange(int amount, int maxCoinInd, unsigned long long int memoTable[][NUM_DENOM])
{
	if(amount < 0)
		return 0;
	if(amount == 0 || maxCoinInd == 0)
		return 1;

	if(memoTable[amount][maxCoinInd] > 0)
		return memoTable[amount][maxCoinInd];

	unsigned long long int numWay = 0;

	numWay += countNumWayToChange(amount, maxCoinInd - 1, memoTable) +
		  countNumWayToChange(amount - DENOM_ARR[maxCoinInd], maxCoinInd, memoTable);
	
	memoTable[amount][maxCoinInd] = numWay;
	return numWay;
}

