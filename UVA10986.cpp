#include <cstdio>
#include <queue>
#include <vector>
#include <utility>

using namespace std;

int computeShortestTime(const vector<vector<pair<int, int> > > &adjList, int startV, int endV)
{
	int numV = (int) adjList.size();
	
	vector<int> shortestDist(numV, 1 << 31 - 1);

	priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pQueue;

	shortestDist[startV] = 0;
	pQueue.push(make_pair(0, startV));

	pair<int, int> curPath, nextEdge;
	int dist, curV, w, nextV;
	while(!pQueue.empty())
	{
		curPath = pQueue.top();
		pQueue.pop();
		dist = curPath.first;
		curV = curPath.second;

		if(dist == shortestDist[curV])
		{
			if(curV == endV)
				return dist;

			for(int i = 0; i < (int) adjList[curV].size(); i++)
			{
				nextEdge = adjList[curV][i];
				w = nextEdge.second;
				nextV = nextEdge.first;

				if(dist + w < shortestDist[nextV])
				{
					// Relax
					shortestDist[nextV] = dist + w;
					pQueue.push(make_pair(shortestDist[nextV], nextV));
				} 
			}
		}
	}

	return -1;	
}

int main(void)
{
	int T, startV, endV, numV, numE, caseId, u, v, weight;
	vector<vector<pair<int, int> > > adjList;
	vector<pair<int, int> > empty;
	int shortestTime;

	scanf("%d", &T);

	caseId = 1;
	while(caseId <= T)
	{
		scanf("%d %d %d %d", &numV, &numE, &startV, &endV);

		adjList.assign(numV, empty);

		for(int i = 0; i < numE; i++)
		{
			scanf("%d %d %d", &u, &v, &weight);
			adjList[u].push_back(make_pair(v, weight));
			adjList[v].push_back(make_pair(u, weight));
		}

		shortestTime = computeShortestTime(adjList, startV, endV);

		printf("Case #%d: ", caseId);
		if(shortestTime < 0)
			printf("unreachable\n");
		else
			printf("%d\n", shortestTime);

		caseId++;
	}
	return 0;
}
