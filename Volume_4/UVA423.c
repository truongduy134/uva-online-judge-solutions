/*******************************************************************************
 * Author: Nguyen Truong Duy
 *******************************************************************************/

/* Methodology:
 *	+ Let d(1, v) is the shortest time to send a message from the first
 *			to the v-th processor.
 *	+ Then the problem asks us to find
 *			max ( d(1, v) ) for all 1 < v <= n
 *
 *	+ Since the number of vertices is V <= 100, we can use a simple O(V^3)
 *		Floy-Warshall's algorithm.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int MAX_NUM_V = 100;
const int MAX_LEN_STR = 100;
const char UNDEFINED = 'x';

void runFloyWarshall(int adjMat[][MAX_NUM_V], int numV);

int main(void)
{
	int numV, adjMat[MAX_NUM_V][MAX_NUM_V], u, v, cost, minCompleteTime;
	char str[MAX_LEN_STR];

	scanf("%d", &numV);
	/* Read the graph */
	for(u = 1; u < numV; u++)
		for(v = 0; v < u; v++)
		{
			scanf("%s", str);
			if(str[0] == UNDEFINED)
				cost = -1;
			else
				cost = atoi(str);

			adjMat[u][v] = cost;
			adjMat[v][u] = cost;
		} 

	for(u = 0; u < numV; u++)
		adjMat[u][u] = 0;

	runFloyWarshall(adjMat, numV);

	minCompleteTime = adjMat[0][0];
	for(u = 1; u < numV; u++)
		if(minCompleteTime < adjMat[0][u])
			minCompleteTime = adjMat[0][u];

	printf("%d\n", minCompleteTime);

	return 0;
}

void runFloyWarshall(int adjMat[][MAX_NUM_V], int numV)
{
	int u, v, k, cost;

	for(k = 0; k < numV; k++)
		for(u = 0; u < numV; u++)
			for(v = 0; v < numV; v++)
			{
				if(adjMat[u][k] < 0 || adjMat[k][v] < 0)
				{
					/* Not connected yet */
					continue;
				}

				cost = adjMat[u][k] + adjMat[k][v];
				if(adjMat[u][v] < 0 || cost < adjMat[u][v])
					adjMat[u][v] = cost;
			}
}

