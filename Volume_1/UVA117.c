/*******************************************************************************
 * Author: Nguyen Truong Duy
 ********************************************************************************/

/* Methodology:
 *	+ The given graph G is connected and has no parallel edges.
 *	+ G has at most 2 vertices of odd degree.
 *	+ Because the number of odd-degree vertices in a graph is even. There are two cases:
 *		- Case 1: G has no vertex of odd degree
 *			* Then G is Eulerian. 
 *			* The cost of the minimal tour visiting all edges at least once is
 *				the sum of weight of edges in G.
 *		- Case 2: G has 2 vertices u, v of odd degree
 *			* The cost of the minimial tour visiting all edges at least once is
 *				the sum of weight of edges in G 
 *			      + weight of the shortest path from u to v
 *
 *	+ Since the input graph is small, we can use the simple Floy Warshall algorithm
 *		to find the shortest path from u to v
 *
 *	+ Time complexity: O(E + V^3) = O(V^3)
 */

#include <stdio.h>
#include <string.h>

const int MAX_NUM_VERTEX = 26;
const char END_INPUT[] = "deadend";
const int MAX_LEN_STR = 100000;

int findCostMinimialEdgeTour(int weightMat[][MAX_NUM_VERTEX]);
int findShortestPath(int adjMat[][MAX_NUM_VERTEX], int vOne, int vTwo);

int main(void)
{
	char name[MAX_LEN_STR + 1];
	int weightMat[MAX_NUM_VERTEX][MAX_NUM_VERTEX], u, v, weight;

	while(scanf("%s", name) > 0)
	{
		memset(weightMat, 0, MAX_NUM_VERTEX * MAX_NUM_VERTEX * sizeof(int));

		while(1)
		{
			if(strcmp(name, END_INPUT) == 0)
				break;

			weight = (int) strlen(name);
			u = name[0] - 'a';
			v=  name[weight - 1] - 'a';
			weightMat[u][v] = weight;
			weightMat[v][u] = weight;

			scanf("%s", name);
		}

		printf("%d\n", findCostMinimialEdgeTour(weightMat));
	}

	return 0;
}

int findCostMinimialEdgeTour(int weightMat[][MAX_NUM_VERTEX])
{
	int vDegree[MAX_NUM_VERTEX], u, v, totalEdgeWeight = 0, i;

	for(i = 0; i < MAX_NUM_VERTEX; i++)
		vDegree[i] = 0;

	for(u = 0; u < MAX_NUM_VERTEX; u++)
		for(v = u; v < MAX_NUM_VERTEX; v++)
		{
			if(weightMat[u][v] > 0)
			{
				totalEdgeWeight += weightMat[u][v];
				vDegree[u]++;
				vDegree[v]++;
			}
		}

	/* Find if there are 2 vertices with odd degree */
	u = v = -1;
	for(i = 0; i < MAX_NUM_VERTEX; i++)
		if(vDegree[i] & 1)
		{
			if(u < 0)
				u = i;
			else
			{
				v = i;
				break;
			}
		}

	if(u < 0)
		/* The graph is Eulerian */
		return totalEdgeWeight;
	
	return totalEdgeWeight + findShortestPath(weightMat, u, v);		
}

int findShortestPath(int adjMat[][MAX_NUM_VERTEX], int vOne, int vTwo)
{
	int k, u, v, cost;

	for(k = 0; k < MAX_NUM_VERTEX; k++)
		for(u = 0; u < MAX_NUM_VERTEX; u++)
			for(v = 0; v < MAX_NUM_VERTEX; v++)
			{
				if(adjMat[u][k] == 0 || adjMat[k][v] == 0)
					continue;

				cost = adjMat[u][k] + adjMat[k][v];
				if(cost < adjMat[u][v] || adjMat[u][v] == 0)
					adjMat[u][v] = cost;
			}

	return adjMat[vOne][vTwo];
}
