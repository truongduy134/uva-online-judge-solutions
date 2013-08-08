/*******************************************************************************
 * Author: Nguyen Truong Duy
 ********************************************************************************/

/* Methodology:
 *	+ This can be modelled as a graph problem.
 * 	  We build an undirected graph G as follows:
 *		- Creatures are vertices in the graph.
 *		- Two vertices are adjacent if one creature is a predator of the other.
 *
 *	+ The problem asks us to find the size of the largest connected compononent
 *	  (This problem is quite misleading, because it appears to ask for the length
 *	   of the longest path in a directed graph)
 *
 *	+ There are 2 solutions:
 *		+ Use Union Find
 *		+ Use DFS / BFS
 */

#include <map>
#include <vector>
#include <cstdio>
#include <string>

using namespace std;

const int MAX_LEN_NAME = 30;

int getMaxSizeConnectedComponent(const vector<vector<int> > & adjList);
int DFS(int v, const vector<vector<int> > & adjList, vector<bool> & visited);

int main(void)
{
	vector<vector<int> > adjList;
	map<string, int> mapNameToId;
	vector<int> emptyList;
	int numV, numE;
	char name[MAX_LEN_NAME + 1];

	while(1)
	{
		scanf("%d %d", &numV, &numE);
		if(!(numV || numE))
			break;
		
		mapNameToId.clear();
		adjList.assign(numV, emptyList);

		for(int id = 0; id < numV; id++)
		{
			scanf("%s", name);
			mapNameToId[name] = id;
		}

		for(int e = 0; e < numE; e++)
		{
			scanf("%s", name);
			int idOne = mapNameToId[name];
			scanf("%s", name);
			int idTwo = mapNameToId[name];
			
			adjList[idTwo].push_back(idOne);
			adjList[idOne].push_back(idTwo);
		}

		printf("%d\n", getMaxSizeConnectedComponent(adjList));
	}
	return 0;
}

int getMaxSizeConnectedComponent(const vector<vector<int> > & adjList)
{
	int numV = (int) adjList.size();
	int maxSize = 0, size;
	vector<bool> visited(numV, false);

	for(int v = 0; v < numV; v++)
		if(visited[v] == false)
		{
			size = DFS(v, adjList, visited);
			if(size > maxSize)
				maxSize = size;
		}

	return maxSize;
}

int DFS(int v, const vector<vector<int> > & adjList, vector<bool> & visited)
{
	visited[v] = true;

	int size = 1;

	for(int ind = 0; ind < (int) adjList[v].size(); ind++)
	{
		int neighbor = adjList[v][ind];
		if(visited[neighbor] == false)
		{
			size += DFS(neighbor, adjList, visited);
		}
	}

	return size;
}
