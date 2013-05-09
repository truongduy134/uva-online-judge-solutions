#include <stdio.h>
#include <string.h>

#define EXCHANGE_RATE 3
#define MAX_SIZE 100

int main(void)
{
	int numEmpty, numExchange, numFull, memoTable[MAX_SIZE + 1], cpyEmpty;

	memset(memoTable, -1, (MAX_SIZE + 1) * sizeof(int));

	while(1)
	{
		scanf("%d", &numEmpty);
		if(!numEmpty)
			break;

		if(memoTable[numEmpty] >= 0)
		{
			printf("%d\n", memoTable[numEmpty]);
			continue;
		}

		numFull = 0;
		cpyEmpty = numEmpty;

		while(numEmpty >= EXCHANGE_RATE)
		{
			/* Exchange */
			numExchange = numEmpty / EXCHANGE_RATE;
			numEmpty = numEmpty % EXCHANGE_RATE;

			numFull += numExchange;

			/* Drink -> have new empty bottles */
			numEmpty += numExchange;
		}

		if(numEmpty == EXCHANGE_RATE - 1)
		{
			/* Borrow one empty bottle from the shop.
			 * Exchange. Drink. Return that empty bottle */
			numFull++;
		}

		printf("%d\n", numFull);
		memoTable[cpyEmpty] = numFull;
	}
	return 0;
}
