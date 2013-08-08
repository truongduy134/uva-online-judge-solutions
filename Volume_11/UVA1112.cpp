#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

void DFS(const vector<vector<pair<int, int> > > &adjList, int v, vector<bool> & visited, vector<int> & topoOrder)
{
	visited[v] = true;

	pair<int, int> nextEdge;

	for(int i = 0; i < (int) adjList[v].size(); i++)
	{
		nextEdge = adjList[v][i];
		if(!visited[nextEdge.first])
			DFS(adjList, nextEdge.first, visited, topoOrder);
	}

	topoOrder.push_back(v);
}

void getTopoOrder(const vector<vector<pair<int, int> > > &adjList, int startV, vector<int> & topoOrder)
{
	int numV = (int) adjList.size();
	vector<bool> visited(numV, false);

	DFS(adjList, startV, visited, topoOrder);

	reverse(topoOrder.begin(), topoOrder.end());
}

int countNumFinish(const vector<vector<pair<int, int> > > &adjList, int startV, int maxTime)
{
	int numV = (int) adjList.size();
	vector<int> topoOrder;

	vector<int> shortestDist(numV, -1);
	shortestDist[startV] = 0;

	getTopoOrder(adjList, startV, topoOrder);

	int curV, nextV, weight;
	pair<int, int> nextEdge;
	for(int i = 0; i < (int) topoOrder.size(); i++)
	{
		curV = topoOrder[i];
		for(int j = 0; j < (int) adjList[curV].size(); j++)
		{
			nextEdge = adjList[curV][j];
			nextV = nextEdge.first;
			weight = nextEdge.second;
			if(shortestDist[nextV] < 0 || shortestDist[curV] + weight <
							shortestDist[nextV])
				shortestDist[nextV] = shortestDist[curV] + weight;
		}
	}

	int count = 0;
	for(int i = 0; i < numV; i++)
		if(shortestDist[i] >= 0 && shortestDist[i] <= maxTime)
			count++;

	return count;
}

int main(void)
{
	int T, exitV, numV, numE, headV, tailV, maxTime, time;
	vector<vector<pair<int, int> > > adjList;
	vector<pair<int, int> > empty;

	scanf("%d", &T);
	while(T)
	{
		scanf("%d %d %d %d", &numV, &exitV, &maxTime, &numE);
		
		adjList.assign(numV, empty);
		
		exitV--;
		for(int i = 0; i < numE; i++)
		{
			scanf("%d %d %d", &headV, &tailV, &time);

			// Construct the transpose graph
			adjList[tailV - 1].push_back(make_pair(headV - 1, time));
		}

		printf("%d\n", countNumFinish(adjList, exitV, maxTime));
		if(T != 1)
			printf("\n");
		T--;
	}
	return 0;
}
