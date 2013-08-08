#include <stdio.h>

#define MAX_NUM_EGG 30

int main(void)
{
	int T, caseId, numEgg, upperBoundNumEgg, maxWeight, eggWeight[MAX_NUM_EGG], i,
	    numEggGreedy, greedyWeight;

	scanf("%d", &T);
	caseId = 1;
	while(caseId <= T)
	{
		scanf("%d %d %d", &numEgg, &upperBoundNumEgg, &maxWeight);
		for(i = 0; i < numEgg; i++)
			scanf("%d", &eggWeight[i]);

		/* Assumption: Egg weights are in non-descending order 
		 *
		 * Approach: greedily choose the eggs in non-descending order of weights until
		 *		we reach the maximum weight allowed
                 */
		numEggGreedy = 0;
		greedyWeight = 0;
		for(i = 0; i < numEgg && greedyWeight + eggWeight[i] <= maxWeight
				      && numEggGreedy < upperBoundNumEgg; i++)
		{
			greedyWeight += eggWeight[i];
			numEggGreedy++;
		}

		printf("Case %d: %d\n", caseId, numEggGreedy);
		caseId++;
	}

	return 0;
}
