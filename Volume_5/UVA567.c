#include <stdio.h>
#include <string.h>

#define MAX_NUM_CITY 20

void computeAllPairShortestPath(int adjMat[][MAX_NUM_CITY], int numV);

int main(void)
{
	int caseId, adjMat[MAX_NUM_CITY][MAX_NUM_CITY], numNeighbor,
	    neighbor, stopFlg, city, time, numQuery, cityOne, cityTwo,
	    query;

	caseId = 1;
	stopFlg = 0;
	while(1)
	{
		memset(adjMat, 0, MAX_NUM_CITY * MAX_NUM_CITY * sizeof(int));

		for(city = 0; city < MAX_NUM_CITY - 1; city++)
			if(scanf("%d", &numNeighbor) > 0)
			{
				for(time = 0; time < numNeighbor; time++)
				{
					scanf("%d", &neighbor);
					neighbor--;
					adjMat[neighbor][city] = 1;
					adjMat[city][neighbor] = 1;
				}
			}
			else
			{
				stopFlg = 1;
				break;
			}

		if(stopFlg)
			break;

		computeAllPairShortestPath(adjMat, MAX_NUM_CITY);

		printf("Test Set #%d\n", caseId);
		scanf("%d", &numQuery);

		for(query = 0; query < numQuery; query++)
		{
			scanf("%d %d", &cityOne, &cityTwo);
			printf("%2d to %2d: %d\n", cityOne, cityTwo, adjMat[cityOne - 1][cityTwo - 1]);
		}
		printf("\n");

		caseId++;
	}

	return 0;
}

void computeAllPairShortestPath(int adjMat[][MAX_NUM_CITY], int numV)
{
	int i, j, k, dist;

	for(k = 0; k < numV; k++)
		for(i = 0; i < numV; i++)
			for(j = 0; j < numV; j++)
			{
				if(adjMat[i][k] && adjMat[k][j])
				{
					dist = adjMat[i][k] + adjMat[k][j];
					if(adjMat[i][j] == 0 || dist < adjMat[i][j])
						adjMat[i][j] = dist;
				}
			}
}
