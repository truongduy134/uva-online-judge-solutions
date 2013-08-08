#include <cstdio>
#include <map>
#include <vector>
#include <utility>
#include <string>
#include <algorithm>

using namespace std;

#define MAX_LENGTH 8

class UnionFind
{
private:
	vector<int> _parent, _rank;
	
	int getLeader(int ele);

public:
	UnionFind(int newSize);
	~UnionFind() {}

	bool areInSameSet(int eleOne, int eleTwo);
	void unionSet(int eleOne, int eleTwo);	
};

UnionFind::UnionFind(int newSize)
{
	_parent.assign(newSize, 0);
	_rank.assign(newSize, 0);

	for(int i = 0; i < newSize; i++)
		_parent[i] = i;
}

int UnionFind::getLeader(int ele)
{
	if(_parent[ele] == ele)
		return ele;
	_parent[ele] = getLeader(_parent[ele]);
	return _parent[ele];
}

bool UnionFind::areInSameSet(int eleOne, int eleTwo)
{
	return getLeader(eleOne) == getLeader(eleTwo);
}

void UnionFind::unionSet(int eleOne, int eleTwo)
{
	int leaderOne = getLeader(eleOne), leaderTwo = getLeader(eleTwo);

	if(leaderOne == leaderTwo)
		return;

	if(_rank[leaderOne] < _rank[leaderTwo])
		_parent[leaderOne] = leaderTwo;
	else
	{
		_parent[leaderTwo] = leaderOne;
		if(_rank[leaderOne] == _rank[leaderTwo])
			_rank[leaderOne]++;
	}
}

int getTotalCostOfMinimumSpanningTree(vector<pair<int, pair<int, int> > > & edgeList, int numV);
int getId(char name[], map<string, int> & mapNameToId, int * nextIdToAssign);

int main(void)
{
	int T, numE, numV, idToAssign, u, v, cost;
	map<string, int> mapCityToId;
	char cityName[MAX_LENGTH + 1];
	vector<pair<int, pair<int, int> > > edgeList;

	scanf("%d", &T);
	while(T)
	{
		scanf("%d %d", &numV, &numE);

		edgeList.clear();
		mapCityToId.clear();
		idToAssign = 0;

		for(int e = 0; e < numE; e++)
		{
			scanf("%s", cityName);
			u = getId(cityName, mapCityToId, &idToAssign);
			scanf("%s", cityName);
			v = getId(cityName, mapCityToId, &idToAssign);
			scanf("%d", &cost);
			
			edgeList.push_back(pair<int, pair<int, int> > (cost, pair<int, int> (u, v)));
		}

		printf("%d\n", getTotalCostOfMinimumSpanningTree(edgeList, numV));

		if(T != 1)
			printf("\n");
		T--;	
	}

	return 0;
}

int getTotalCostOfMinimumSpanningTree(vector<pair<int, pair<int, int> > > & edgeList, int numV)
{
	int totalCost = 0, u, v, cost;
	UnionFind spanningForest(numV);

	sort(edgeList.begin(), edgeList.end());

	for(int i = 0; i < (int) edgeList.size(); i++)
	{
		cost = edgeList[i].first;
		u = edgeList[i].second.first;
		v = edgeList[i].second.second;

		if(!spanningForest.areInSameSet(u, v))
		{
			spanningForest.unionSet(u, v);
			totalCost += cost;
		}
	}

	return totalCost;
}

int getId(char name[], map<string, int> & mapNameToId, int * nextIdToAssign)
{
	map<string, int>::iterator it = mapNameToId.find(name);
	int returnId;

	if(it == mapNameToId.end())
	{
		returnId = *nextIdToAssign;
		mapNameToId[name] = returnId;
		(*nextIdToAssign)++;
	}
	else
		returnId = it->second;

	return returnId;
}
