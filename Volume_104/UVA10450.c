#include <stdio.h>

#define MAX_SIZE 51

int main(void)
{
	unsigned long long int numWay[MAX_SIZE];
	int i, T, n, caseId;

	numWay[0] = 0;
	numWay[1] = 2;
	numWay[2] = 3;

	for(i = 3; i < MAX_SIZE; i++)
		numWay[i] = numWay[i - 1] + numWay[i - 2];

	scanf("%d", &T);
	caseId = 1;
	while(caseId <= T)
	{
		scanf("%d", &n);

		printf("Scenario #%d:\n%llu\n\n", caseId, numWay[n]);
		caseId++;
	}

	return 0;
}
