#include <cstdio>
#include <vector>
#include <map>
#include <utility>
#include <queue>

using namespace std;

#define NUM_DIRECTION 4
#define LEFT 0
#define RIGHT 1
#define UP 2
#define DOWN 3

void readAndBuildResidualGraph(vector<vector<pair<int, int> > > & residualGraph, vector<map<int, int> > & findIndInAdjList, int *numLocation);
int findMaxFlowEdmondsKarp(vector<vector<pair<int, int> > > & residualGraph, 
			   vector<map<int, int> > & findIndInAdjList, int source, int sink);
bool breathFirstSearch(vector<vector<pair<int, int> > > & residualGraph, int source, int sink,
		      vector<int> & parent);
int getAugmentFlow(vector<vector<pair<int, int> > > & residualGraph, vector<map<int, int> > & findIndInAdjList, int source, int sink, vector<int> & parent);
void augmentResidualGraph(vector<vector<pair<int, int> > > & residualGraph, vector<map<int, int> > & findIndInAdjList, int source, int sink, int augmentFlow, vector<int> & parent);
void getNextPosition(int street, int avenue, int *nextS, int *nextA, int direction);

int main(void)
{
	int T, numLocation, source, sink;
	vector<vector<pair<int, int> > > residualGraph;
	vector<map<int, int> > findIndInAdjList;
	scanf("%d", &T);
	while(T)
	{
		readAndBuildResidualGraph(residualGraph, findIndInAdjList, &numLocation);

		source = 0;
		sink = (int) residualGraph.size() - 1;
		if(findMaxFlowEdmondsKarp(residualGraph, findIndInAdjList, source, sink) == numLocation)
			printf("possible\n");
		else
			printf("not possible\n");

		T--;
	}	
}

void readAndBuildResidualGraph(vector<vector<pair<int, int> > > & residualGraph, vector<map<int, int> > & findIndInAdjList, int *numLocation)
{
	int numStreet, numAvenue, numV, street, avenue, id, lastV, numCell;
	vector<pair<int, int> > emptyList;
	map<int, int> emptyMap;

	scanf("%d %d %d", &numStreet, &numAvenue, numLocation);
	numCell = numStreet * numAvenue;

	// 2 pseudo-vertices and each original vertex is split into 2
	numV = 2 * numStreet * numAvenue + 2;
	
	residualGraph.assign(numV, emptyList);
	findIndInAdjList.assign(numV, emptyMap);

	// Add bank locations to pseudo-vertex 0
	for(int i = 0; i < *numLocation; i++)
	{
		scanf("%d %d", &street, &avenue);

		id = street + (avenue - 1) * numAvenue;
		findIndInAdjList[0][id] = (int) residualGraph[0].size();
		findIndInAdjList[id][0] = (int) residualGraph[id].size();
		residualGraph[0].push_back(make_pair(id, 1));
		residualGraph[id].push_back(make_pair(0, 0));
	}

	// Add rear locations to pseudo-vertex 2 * numStreet * numAvenue + 1
	lastV = numV - 1;
	for(street = 1; street <= numStreet; street += numStreet - 1)
		for(avenue = 1; avenue <= numAvenue; avenue++)
		{
			id = street + (avenue - 1) * numAvenue + numCell;
			findIndInAdjList[lastV][id] = (int) residualGraph[lastV].size();
			findIndInAdjList[id][lastV] = (int) residualGraph[id].size();
			residualGraph[lastV].push_back(make_pair(id, 0));
			residualGraph[id].push_back(make_pair(lastV, 1));
		}
	for(street = 2; street < numStreet; street++)
		for(avenue = 1; avenue <= numAvenue; avenue += numAvenue - 1)
		{
			id = street + (avenue - 1) * numAvenue + numCell;
			findIndInAdjList[lastV][id] = (int) residualGraph[lastV].size();
			findIndInAdjList[id][lastV] = (int) residualGraph[id].size();
			residualGraph[lastV].push_back(make_pair(id, 0));
			residualGraph[id].push_back(make_pair(lastV, 1));
		}

	// Add adjacent cells
	int nextS, nextA, nextId;
	for(street = 1; street <= numStreet; street++)
		for(avenue = 1; avenue <= numAvenue; avenue++)
		{
			id = street + (avenue - 1) * numAvenue;
			// Every vertex is split into 2
			findIndInAdjList[id + numCell][id] = (int) residualGraph[id + numCell].size();
			findIndInAdjList[id][id + numCell] = (int) residualGraph[id].size();
			residualGraph[id + numCell].push_back(make_pair(id, 0));
			residualGraph[id].push_back(make_pair(id + numCell, 1));
			
			for(int direction = 0; direction < NUM_DIRECTION; direction++)
			{
				getNextPosition(street, avenue, &nextS, &nextA, direction);
				if(nextS <= 0 || nextA <= 0 || nextS > numStreet || nextA > numAvenue)
					continue;

				nextId = nextS + (nextA - 1) * numAvenue;
				findIndInAdjList[nextId][id + numCell] = (int) residualGraph[nextId].size();
				findIndInAdjList[id + numCell][nextId] = (int) residualGraph[id + numCell].size();
				residualGraph[nextId].push_back(make_pair(id + numCell, 0));
				residualGraph[id + numCell].push_back(make_pair(nextId, 1));
			}
	}		
	
}

void getNextPosition(int street, int avenue, int *nextS, int *nextA, int direction)
{
	switch(direction)
	{
		case LEFT:
			*nextS = street;
			*nextA = avenue - 1;
			return;
		case RIGHT:
			*nextS = street;
			*nextA = avenue + 1;
			return;
		case UP:
			*nextS = street - 1;
			*nextA = avenue;
			return;
		default:
			*nextS = street + 1;
			*nextA = avenue;
	}	
}
int findMaxFlowEdmondsKarp(vector<vector<pair<int, int> > > & residualGraph, 
			   vector<map<int, int> > & findIndInAdjList, int source, int sink)
{
	int maxFlow = 0, numV = (int) residualGraph.size(), augmentFlow;
	vector<int> parent;
	bool hasAugmentPath;

	while(1)
	{
		hasAugmentPath = breathFirstSearch(residualGraph, source, sink, parent);
		if(!hasAugmentPath)
			break;

		augmentFlow = getAugmentFlow(residualGraph, findIndInAdjList, source, sink, parent);
		
		if(augmentFlow == 0)
			break;
		
		maxFlow += augmentFlow;
		augmentResidualGraph(residualGraph, findIndInAdjList, source, sink, augmentFlow, parent);	
		
	}

	return maxFlow;
}

bool breathFirstSearch(vector<vector<pair<int, int> > > & residualGraph, int source, int sink,
		      vector<int> & parent)
{
	int numV = (int) residualGraph.size();
	queue<int> mQueue;

	parent.assign(numV, -1);
	parent[source] = source;
	mQueue.push(source);
	
	int curV, nextV, capacity;
	while(!mQueue.empty())
	{
		curV = mQueue.front();
		mQueue.pop();
	
		if(curV == sink)
			return true;

		for(int ind = 0; ind < (int) residualGraph[curV].size(); ind++)
		{
			nextV = residualGraph[curV][ind].first;
			capacity = residualGraph[curV][ind].second;

			if(capacity > 0 && parent[nextV] < 0)
			{
				parent[nextV] = curV;
				mQueue.push(nextV);
			}
		}
	}

	return false;	
}

int getAugmentFlow(vector<vector<pair<int, int> > > & residualGraph, vector<map<int, int> > & findIndInAdjList, int source, int sink, vector<int> & parent)
{
	int curV = sink, parentV, minCapacity = 0, indInParent;

	while(curV != source)
	{
		parentV = parent[curV];
		indInParent = findIndInAdjList[parentV][curV];
		if(minCapacity == 0 || residualGraph[parentV][indInParent].second < minCapacity)
			minCapacity = residualGraph[parentV][indInParent].second;

		curV = parentV;
	}

	return minCapacity;
}

void augmentResidualGraph(vector<vector<pair<int, int> > > & residualGraph, vector<map<int, int> > & findIndInAdjList, int source, int sink, int augmentFlow, vector<int> & parent)
{
	int curV = sink, parentV, indInParent, indInChild;

	while(curV != source)
	{
		parentV = parent[curV];
		indInParent = findIndInAdjList[parentV][curV];
		indInChild = findIndInAdjList[curV][parentV];
		residualGraph[parentV][indInParent].second -= augmentFlow;
		residualGraph[curV][indInChild].second += augmentFlow;

		curV = parentV;
	}
}
