#include <cstdio>
#include <queue>
#include <map>
#include <vector>
#include <utility>

using namespace std;

int getId(int val, map<int, int> & mapNodeValToId, int *nextAssignId);
int findNumReachableByBFS(const vector<vector<int> > & adjList, int startV, int TTL);

int main(void)
{
	int numE, numV, caseId, valOne, valTwo, idOne, idTwo, TTL, nextAssignId, numReach;
	map<int, int> mapNodeValToId;
	vector<vector<int> > adjList;
	vector<int> emptyList;
	map<int, int>::const_iterator it;

	caseId = 1;
	while(1)
	{
		scanf("%d", &numE);
		if(numE == 0)
			break;

		nextAssignId = 0;
		mapNodeValToId.clear();
		adjList.clear();

		// Read input and build graph
		for(int e = 0; e < numE; e++)
		{
			scanf("%d %d", &valOne, &valTwo);
			idOne = getId(valOne, mapNodeValToId, &nextAssignId);
			idTwo = getId(valTwo, mapNodeValToId, &nextAssignId);

			if(idOne >= (int) adjList.size())
				adjList.push_back(emptyList);
			if(idTwo >= (int) adjList.size())
				adjList.push_back(emptyList);
			
			adjList[idOne].push_back(idTwo);
			adjList[idTwo].push_back(idOne);
		}
		numV = (int) adjList.size();

		// Query
		while(1)
		{
			scanf("%d %d", &valOne, &TTL);
			if(valOne == 0 && TTL == 0)
				break;

			it = mapNodeValToId.find(valOne);
			if(it == mapNodeValToId.end())
				numReach = 0;
			else
				numReach = findNumReachableByBFS(adjList, it->second, TTL);

			printf("Case %d: %d nodes not reachable from node %d with TTL = %d.\n",
					caseId, numV - numReach, valOne, TTL);

			caseId++;
		}
	}
	return 0;
}

int getId(int val, map<int, int> & mapNodeValToId, int *nextAssignId)
{
	map<int, int>::iterator it = mapNodeValToId.find(val);
	int returnId;

	if(it == mapNodeValToId.end())
	{
		returnId = *nextAssignId;
		mapNodeValToId[val] = returnId;
		(*nextAssignId)++;
	}
	else
		returnId = it->second;

	return returnId;
}

int findNumReachableByBFS(const vector<vector<int> > & adjList, int startV, int TTL)
{
	int numV = (int) adjList.size();

	vector<bool> visited(numV, false);

	queue<pair<int, int> > vQueue;
	vQueue.push(pair<int, int> (startV, 0) );
	visited[startV] = true;

	int numReach = 0, timeSoFar, curV, nextV;
	while(!vQueue.empty())
	{
		curV = vQueue.front().first;
		timeSoFar = vQueue.front().second;
		vQueue.pop();

		if(timeSoFar > TTL)
			break;

		numReach++;

		for(int ind = 0; ind < (int) adjList[curV].size(); ind++)
		{
			nextV = adjList[curV][ind];
			if(visited[nextV] == false)
			{
				visited[nextV] = true;
				vQueue.push(pair<int, int>(nextV, timeSoFar + 1));
			}
		}		
	}
	return numReach;
}
