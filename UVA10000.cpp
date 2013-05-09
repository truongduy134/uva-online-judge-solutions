#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

void DFS(const vector<vector<int> > & adjList, int v, vector<bool> &visited, vector<int> & topoOrder)
{
	visited[v] = true;

	int nextV;
	for(int i = 0; i < (int) adjList[v].size(); i++)
	{
		nextV = adjList[v][i];
		if(!visited[nextV])
			DFS(adjList, nextV, visited, topoOrder);
	}

	topoOrder.push_back(v);
}

void findTopoOrder(const vector<vector<int> > & adjList, int v, vector<int> & topoOrder)
{
	vector<bool> visited((int) adjList.size(), false);
	
	DFS(adjList, v, visited, topoOrder);

	reverse(topoOrder.begin(), topoOrder.end());
}

pair<int, int> findLongestPath(const vector<vector<int> > & adjList, int startV)
{
	vector<int> topoOrder;
	int numV = (int) adjList.size();

	findTopoOrder(adjList, startV, topoOrder);

	vector<int> longestDist(numV, 0);
	
	int u, v;
	for(int startIndex = 0; startIndex < (int) topoOrder.size(); startIndex++)
	{
		u = topoOrder[startIndex];
		for(int i = 0; i < (int) adjList[u].size(); i++)
		{
			v = adjList[u][i];
			if(longestDist[u] + 1  > longestDist[v])
				longestDist[v] = longestDist[u] + 1;
		}
	}

	int maxInd = 0;
	for(int i = 1; i < numV; i++)
		if(longestDist[i] > longestDist[maxInd])
			maxInd = i;
	if(longestDist[maxInd] == 0)
		maxInd = startV;

	return make_pair(longestDist[maxInd], maxInd);	
}

int main(void)
{
	int numV, startV, v1, v2, caseId;
	vector<vector<int> > adjList;
	vector<int> empty;
	pair<int, int> ans;

	caseId = 1;
	while(1)
	{
		scanf("%d", &numV);
		if(numV == 0)
			break;
		adjList.assign(numV, empty);

		scanf("%d", &startV);
		startV--;

		while(1)
		{
			scanf("%d %d", &v1, &v2);
			if(v1 == 0 && v2 == 0)
				break;
			adjList[v1 - 1].push_back( v2 - 1);
		}

		ans = findLongestPath(adjList, startV);

		printf("Case %d: The longest path from %d has length %d, finishing at %d.\n\n",
			caseId, startV + 1, ans.first, ans.second + 1);
		caseId++;			
	}
	return 0;
}
