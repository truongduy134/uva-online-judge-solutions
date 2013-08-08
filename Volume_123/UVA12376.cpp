#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

pair<int, int> computeGreedyLongestPath(const vector<vector<int> > & adjList, int startV, const vector<int> & weightOfVertex);

int main(void)
{
	int T, numV, numE, u, v, caseId;
	vector<vector<int> > adjList;
	vector<int> emptyList, weightOfVertex;

	scanf("%d", &T);

	pair<int, int> maxLearnAndDest;

	caseId = 1;
	while(caseId <= T)
	{
		scanf("%d %d", &numV, &numE);
		
		adjList.assign(numV, emptyList);
		weightOfVertex.assign(numV, 0);

		for(v = 0; v < numV; v++)
			scanf("%d", &weightOfVertex[v]);

		for(int e = 0; e < numE; e++)
		{
			scanf("%d %d", &u, &v);
			adjList[u].push_back(v);
		}

		maxLearnAndDest = computeGreedyLongestPath(adjList, 0, weightOfVertex);

		printf("Case %d: %d %d\n", caseId, maxLearnAndDest.first, maxLearnAndDest.second);
		
		caseId++;
	} 
	return 0;
}

pair<int, int> computeGreedyLongestPath(const vector<vector<int> > & adjList, int startV, const vector<int> & weightOfVertex)
{
	int v = startV, totalWeight, maxNeighborInd;

	totalWeight = weightOfVertex[startV];
	while(adjList[v].size() > 0)
	{
		maxNeighborInd = 0;

		for(int ind = 1; ind < (int) adjList[v].size(); ind++)
			if(weightOfVertex[adjList[v][ind]] > weightOfVertex[adjList[v][maxNeighborInd]])
				maxNeighborInd = ind;

		totalWeight += weightOfVertex[adjList[v][maxNeighborInd]];
		v = adjList[v][maxNeighborInd];
	}

	return make_pair(totalWeight, v);
}
