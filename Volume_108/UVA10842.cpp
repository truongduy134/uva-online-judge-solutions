#include <cstdio>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

class UnionFind
{
private:
	vector<int> _parent, _rank;

	int getLeader(int ele);
public:
	UnionFind() { reset(0); }
	UnionFind(int mSize) { reset(mSize); }
	UnionFind(const UnionFind & another) : _parent(another._parent), _rank(another._rank) {}
	~UnionFind() {}

	void reset(int newSize);
	bool areInSameSet(int eleOne, int eleTwo);
	void unionSet(int eleOne, int eleTwo);
};

void UnionFind::reset(int newSize)
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

int getMinEdgeWeightInMaximumSpanningTree(vector<pair<int, pair<int, int> > > & edgeList, int numV);

int main(void)
{
	int T, numV, numE, u, v, weight, caseId;
	vector<pair<int, pair<int, int> > > edgeList;

	scanf("%d", &T);
	caseId = 1;
	while(caseId <= T)
	{
		scanf("%d %d", &numV, &numE);

		edgeList.clear();

		for(int e = 0; e < numE; e++)
		{
			scanf("%d %d %d", &u, &v, &weight);
			edgeList.push_back(pair<int, pair<int, int> > (weight, pair<int, int> (u, v)));
		}

		printf("Case #%d: %d\n", caseId, getMinEdgeWeightInMaximumSpanningTree(edgeList, numV));

		caseId++;
	}

	return 0;
}

int getMinEdgeWeightInMaximumSpanningTree(vector<pair<int, pair<int, int> > > & edgeList, int numV)
{
	sort(edgeList.begin(), edgeList.end());

	UnionFind disjointForest(numV);

	int u, v, weight, minWeight = -1;
	for(int id = (int) edgeList.size() - 1; id >= 0; id--)
	{
		weight = edgeList[id].first;
		u = edgeList[id].second.first;
		v = edgeList[id].second.second;

		if(!disjointForest.areInSameSet(u, v))
		{
			disjointForest.unionSet(u, v);
			if(minWeight < 0 || weight < minWeight)
				minWeight = weight;
		}
	}

	return minWeight;
	
}
