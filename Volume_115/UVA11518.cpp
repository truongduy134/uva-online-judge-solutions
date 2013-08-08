/*******************************************************************************
 * Author: Nguyen Truong Duy
 *******************************************************************************/

/* Methodology:
 *	+ Build a graph G = (V, E) such that
 *		- Each domino is a vertex
 *		- There is a directed edge from u to v if the fact that domino u falling
 *			makes domino v fall as well.
 *
 *	+ Keep track of an array S such that S[i] = true if domino i has fallen, S[i] = false
 *		otherwise
 *	+ For each knocked domino u, perform a DFS (or BFS) traversal from u in G if
 *		S[u] = false. For each domino v visited in the traversal, mark S[v] = true.
 *	+ Count and output the number of dominoes fallen.
 *
 *	+ Time complexity: O(V + E)
 */

#include <cstdio>
#include <vector>

using namespace std;

int findNumFall(const vector<vector<int> > & adjList, const vector<int> & knockId);
void DFS(const vector<vector<int> > & adjList, int v, vector<bool> & visited);

int main(void)
{
	vector<vector<int> > adjList;
	vector<int> emptyList;
	int u, v, numV, numE, numKnock, T;
	vector<int> knockId;

	scanf("%d", &T);
	while(T)
	{
		scanf("%d %d %d", &numV, &numE, &numKnock);

		adjList.assign(numV, emptyList);
		knockId.assign(numKnock, 0);

		for(int e = 0; e < numE; e++)
		{
			scanf("%d %d", &u, &v);
			u--;
			v--;
			adjList[u].push_back(v);
		}

		for(int i = 0; i < numKnock; i++)
		{
			scanf("%d", &knockId[i]);
			knockId[i]--;
		}

		printf("%d\n", findNumFall(adjList, knockId));
		T--;
	}
	return 0;
}

int findNumFall(const vector<vector<int> > & adjList, const vector<int> & knockId)
{
	int numV = (int) adjList.size();
	vector<bool> hasFall(numV, false);

	for(int i = 0; i < (int) knockId.size(); i++)
		if(hasFall[knockId[i]] == false)
		{
			DFS(adjList, knockId[i], hasFall); 
		}

	int count = 0;
	for(int v = 0; v < numV; v++)
		if(hasFall[v])
			count++;

	return count;
}

void DFS(const vector<vector<int> > & adjList, int v, vector<bool> & visited)
{
	visited[v] = true;

	for(int i = 0; i < (int) adjList[v].size(); i++)
	{
		int nextV = adjList[v][i];
		if(visited[nextV] == false)
			DFS(adjList, nextV, visited);
	}
}
