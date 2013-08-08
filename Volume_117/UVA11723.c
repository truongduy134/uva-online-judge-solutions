#include <stdio.h>

#define NUM_ALPHA 26

int main(void)
{
	int numRoad, numInt, caseId, numAddAlpha, numName;

	caseId = 1;
	while(1)
	{
		scanf("%d %d", &numRoad, &numInt);
		if(numRoad == 0 && numInt == 0)
			break;
	
		numName = numInt;
		for(numAddAlpha = 0; numAddAlpha <= NUM_ALPHA; numAddAlpha++)
		{
			if(numName >= numRoad)
				break;
			numName += numInt; 
		}

		printf("Case %d: ", caseId);
		if(numAddAlpha > NUM_ALPHA)
			printf("impossible\n");
		else
			printf("%d\n", numAddAlpha);

		caseId++;		
	}
	return 0;
}
