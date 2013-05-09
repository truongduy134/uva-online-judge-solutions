#include <stdio.h>

int main(void)
{
	int T, numPlayer, startPlayer, numRound, caseId, finalPlayer;

	scanf("%d", &T);
	caseId = 1;
	while(caseId <= T)
	{
		scanf("%d %d %d", &numPlayer, &startPlayer, &numRound);

		finalPlayer = (startPlayer + numRound) % numPlayer;
		if(finalPlayer == 0)
			finalPlayer = numPlayer;

		printf("Case %d: %d\n", caseId, finalPlayer);
		caseId++;
	}
	return 0;
}
