#include <stdio.h>
#include <limits.h>

#define MAX_V 100
const int NOT_REACHED = INT_MAX;

int max(int a, int b)
{
	if(a < b)
		return b;
	return a;
}

int min(int a, int b)
{
	if(a > b)
		return b;
	return a;
}

void computeMinSoundIntensity(int adjMat[][MAX_V], int numV);

int main(void)
{
	int numV, numE, numQuery, adjMat[MAX_V][MAX_V], i, j, q, e,
		u, v, weight, isFirst, caseId;

	caseId = 1;
	isFirst = 1;
	while(1)
	{
		scanf("%d %d %d", &numV, &numE, &numQuery);
		if(numV == 0 && numE == 0 && numQuery == 0)
			break;

		for(i = 0; i < numV; i++)
			for(j = 0; j < numV; j++)
				adjMat[i][j] = NOT_REACHED;

		for(e = 0; e < numE; e++)
		{
			scanf("%d %d %d", &u, &v, &weight);
			adjMat[u - 1][v - 1] = weight;
			adjMat[v - 1][u - 1] = weight;
		}

		computeMinSoundIntensity(adjMat, numV);

		if(isFirst)
			isFirst = 0;
		else
			printf("\n");
		printf("Case #%d\n", caseId);

		for(q = 0; q < numQuery; q++)
		{
			scanf("%d %d", &u, &v);
			if(adjMat[u - 1][v - 1] != NOT_REACHED)
				printf("%d\n", adjMat[u - 1][v - 1]);
			else
				printf("no path\n");
		}

		caseId++;
	}

	return 0;
}

/* Run Floy-Warshall to compute:
 *	min { max { w(e) | e in P, P is a path from u to v } } for every u, v
 */
void computeMinSoundIntensity(int adjMat[][MAX_V], int numV)
{
	int i, j, k;

	for(k = 0; k < numV; k++)
		for(i = 0; i < numV; i++)
			for(j = 0; j < numV; j++)
			{
				adjMat[i][j] = min(adjMat[i][j], max(adjMat[i][k], adjMat[j][k]));
			}
}
