#include <stdio.h>
#include <string.h>

#define MAX_SIZE 100
#define MAX_N 60

unsigned long long int countNumCall(int n, int k, unsigned long long int memoTable[][MAX_SIZE]);

int main(void)
{
	unsigned long long int memoTable[MAX_SIZE][MAX_SIZE] = {{0}};
	int n, k, caseId;

	caseId = 1;
	
	while(1)
	{
		scanf("%d %d", &n, &k);
		if(n > MAX_N)
			break;

		printf("Case %d: %llu\n", caseId, countNumCall(n, k, memoTable));

		caseId++;
	}

	return 0;
}

unsigned long long int countNumCall(int n, int k, unsigned long long int memoTable[][MAX_SIZE])
{
	int i;

	if(n <= 1)
		return 1;

	if(memoTable[n][k] > 0)
		return memoTable[n][k];

	unsigned long long int numCall = 1;	/* Count the current call as well */
	for(i = 1; i <= k; i++)
		numCall += countNumCall(n - i, k, memoTable);

	memoTable[n][k] = numCall;

	return numCall;
}
