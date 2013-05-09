#include <stdio.h>

#define MAX_AGE 21

int main(void)
{
	int T, N, ageSieve[MAX_AGE], i, caseId, age, numSmaller, leaderAge;

	scanf("%d", &T);
	caseId = 1;
	while(caseId <= T)
	{
		scanf("%d", &N);
		for(i = 0; i < MAX_AGE; i++)
		{
			ageSieve[i] = 0;
		}

		for(i = 0; i < N; i++)
		{
			scanf("%d", &age);
			ageSieve[age]++;
		}

		numSmaller = N >> 1;
		for(i = 0; i < MAX_AGE; i++)
		{
			numSmaller -= ageSieve[i];
			if(numSmaller < 0)
			{
				leaderAge = i;
				break;
			}
		}

		printf("Case %d: %d\n", caseId, leaderAge);
		caseId++;
	}

	return 0;
}
