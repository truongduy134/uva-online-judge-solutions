#include <stdio.h>

#define MAX_SIZE 20

void printRoute(int parentMat[][MAX_SIZE], int startV, int endV)
{
	if(startV != endV)
		printRoute(parentMat, startV, parentMat[startV][endV]);
	printf(" %d", endV + 1);
}

int main(void)
{
	int caseId, numV, adjMat[MAX_SIZE][MAX_SIZE], numE, nextV, w, startV, endV,
		parentMat[MAX_SIZE][MAX_SIZE], newW, i, j, k, v;

	caseId = 1;
	while(1)
	{
		scanf("%d", &numV);
		if(numV == 0)
			break;

		for(i = 0; i < numV; i++)
			for(j = 0; j < numV; j++)
				adjMat[i][j] = 0;

		for(v = 0; v < numV; v++)
		{
			scanf("%d", &numE);
			for(i = 0; i < numE; i++)
			{
				scanf("%d %d", &nextV, &w);
				adjMat[v][nextV - 1] = w;
			}
		}

		scanf("%d %d", &startV, &endV);
		startV--;
		endV--;

		for(i = 0; i < numV; i++)
			for(j = 0; j < numV; j++)
				parentMat[i][j] = i;


		for(k = 0; k < numV; k++)
			for(i = 0; i < numV; i++)
				for(j = 0; j < numV; j++)
					if(adjMat[i][k] && adjMat[k][j])
					{
						newW = adjMat[i][k] + adjMat[k][j];
						if(newW < adjMat[i][j] || adjMat[i][j] == 0)
						{
							adjMat[i][j] = newW;
							parentMat[i][j] = parentMat[k][j]; 
						}
					}

		printf("Case %d: Path =", caseId);
		printRoute(parentMat, startV, endV);
		printf("; %d second delay\n", adjMat[startV][endV]);

		caseId++;
	}

	return 0;	
}
