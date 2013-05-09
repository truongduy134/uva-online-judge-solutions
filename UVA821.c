#include <stdio.h>
#include <string.h>

#define MAX_SIZE 100

double computeAverageAPSP(int adjMatrix[][MAX_SIZE], int numV)
{
	int i, j, k, newPath, numPath, sumLength;

	for(k = 0; k < numV; k++)
		for(i = 0; i < numV; i++)
			for(j = 0; j < numV; j++)
			{
				if(adjMatrix[i][k] && adjMatrix[k][j])
				{
					newPath = adjMatrix[i][k] + adjMatrix[k][j];
					if(newPath < adjMatrix[i][j] || adjMatrix[i][j] == 0)
						adjMatrix[i][j] = newPath;
				}
			}

	numPath = 0;
	sumLength = 0;
	
	for(i = 0; i < numV; i++)
		for(j = 0; j < numV; j++)
			if(i != j && adjMatrix[i][j])
			{
				numPath++;
				sumLength += adjMatrix[i][j];
			}

	return sumLength * 1.0 / numPath;
}

int main(void)
{
	int caseId, u, v, adjMatrix[MAX_SIZE][MAX_SIZE], numV, i, j;

	caseId = 1;
	while(1)
	{
		scanf("%d %d", &u, &v);
		if(u == 0 && v == 0)
			break;

		numV = 0;
		
		memset((int *) adjMatrix, 0, MAX_SIZE * MAX_SIZE * sizeof(int));

		if(u > numV)
			numV = u;
		if(v > numV)
			numV = v;
		adjMatrix[u - 1][v - 1] = 1;

		while(1)
		{
			scanf("%d %d", &u, &v);
			if(u == 0 && v == 0)
				break;
			adjMatrix[u - 1][v - 1] = 1;
			if(u > numV)
				numV = u;
			if(v > numV)
				numV = v;
		}
		
		printf("Case %d: average length between pages = %.3lf clicks\n",
				caseId, computeAverageAPSP(adjMatrix, numV));
		caseId++;
	}

	return 0;
}


