/*******************************************************************************
 * Author: Nguyen Truong Duy
 ********************************************************************************/

/* Methodology
 *	+ Note that the input graph is a tree, because there is no cyle in the graph.
 *	  Therefore, between any 2 vertices in the graph, there exists a unique
 *		path.
 *	+ Hence, we can use either BFS or DFS to traverse the graph to find the path
 *		between any vertices u and v.
 *
 *	+ Time complexity: O(Q(V + E)) where Q is the number of query, V is
 *		the number vertices and E is the number of edges	
 */

#include <cstdio>
#include <map>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>

using namespace std;

const int MAX_LEN = 500;
const int INF = 1000000000;

int getCityId(char name[], map<string, int> & mapNameToId, vector<string> & mapIdToName, int & nextIdToAssign);
void insertEdgeToAdjList(vector<vector<int> > & adjList, int vOne, int vTwo);
void findShortestPath(const vector<vector<int> > & adjList, int u, int v, vector<int> & path);

int main(void)
{
	int T;
	int numE, numQuery, idOne, idTwo, nextIdToAssign;
	char name1[MAX_LEN + 1], name2[MAX_LEN + 1];
	vector<vector<int> > adjList;
	map<string, int> mapNameToId;
	vector<string> mapIdToName;
	vector<int> path;

	scanf("%d", &T);
	while(T)
	{
		scanf("%d %d", &numE, &numQuery);

		adjList.clear();
		mapNameToId.clear();
		mapIdToName.clear();
		nextIdToAssign = 0;

		for(int i = 0; i < numE; i++)
		{
			scanf("%s %s", name1, name2);
			idOne = getCityId(name1, mapNameToId, mapIdToName, nextIdToAssign);
			idTwo = getCityId(name2, mapNameToId, mapIdToName, nextIdToAssign);
			// Assumption: idOne != idTwo (There is no loop in the graph)
			insertEdgeToAdjList(adjList, idOne, idTwo);
		}

		for(int i = 0; i < numQuery; i++)
		{
			scanf("%s %s", name1, name2);
			idOne = getCityId(name1, mapNameToId, mapIdToName, nextIdToAssign);
			idTwo = getCityId(name2, mapNameToId, mapIdToName, nextIdToAssign);
			findShortestPath(adjList, idOne, idTwo, path);

			for(int i = 0; i < (int) path.size(); i++)
				printf("%c", mapIdToName[path[i]][0]);
			printf("\n");			
		}
		if(T > 1)
			printf("\n");
		T--;
	}
	return 0;
}

int getCityId(char name[], map<string, int> & mapNameToId, vector<string> & mapIdToName, int & nextIdToAssign)
{
	map<string, int>::iterator it = mapNameToId.find(name);
	if(it != mapNameToId.end())
		return it->second;
	int ret = nextIdToAssign;
	nextIdToAssign++;
	mapNameToId[name] = ret;
	mapIdToName.push_back(name);
	return ret;
}

// Assumption: vOne != vTwo
void insertEdgeToAdjList(vector<vector<int> > & adjList, int vOne, int vTwo)
{
	int numV = (int) adjList.size();
	vector<int> emptyList;

	if(vOne >= numV)
		adjList.push_back(emptyList);
	if(vTwo >= numV)
		adjList.push_back(emptyList);
	adjList[vOne].push_back(vTwo);
	adjList[vTwo].push_back(vOne);
} 

void findShortestPath(const vector<vector<int> > & adjList, int u, int v, vector<int> & path)
{
	path.clear();
	int numV = (int) adjList.size();

	vector<int> minDist(numV, INF);
	minDist[u] = 0;
	vector<int> predecessor(numV);
	for(int i = 0; i < numV; i++)
		predecessor[i] = i;
	queue<int> bfsQ;
	bfsQ.push(u);

	bool existPath = false;
	while(!bfsQ.empty())
	{
		int curV = bfsQ.front();
		bfsQ.pop();

		if(curV == v)
		{
			existPath = true;
			break;
		}

		for(int i = 0; i < (int) adjList[curV].size(); i++)
		{
			int nextV = (int) adjList[curV][i];
			if(minDist[nextV] == INF)
			{
				minDist[nextV] = minDist[curV] + 1;
				predecessor[nextV] = curV;
				bfsQ.push(nextV);
			}
		}
	}

	if(!existPath)
		return;

	int curV = v;
	while(predecessor[curV] != curV)
	{
		path.push_back(curV);
		curV = predecessor[curV];
	}
	path.push_back(u);

	reverse(path.begin(), path.end());
}
