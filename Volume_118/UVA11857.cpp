#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

class UnionFind
{
private:
	vector<int> _rank, _parent;
	int _numSet;

	int getLeader(int ele);
public:
	UnionFind();
	UnionFind(int mSize);
	UnionFind(const UnionFind & another);
	~UnionFind() {}

	void reset(int newSize);
	bool areInSameSet(int eleOne, int eleTwo);
	void unionSet(int eleOne, int eleTwo);
	int getNumDisjointSet() const {return _numSet;}
};

void UnionFind::reset(int newSize)
{
	_rank.assign(newSize, 0);
	_parent.assign(newSize, 0);
	_numSet = newSize;

	for(int i = 0; i < newSize; i++)
		_parent[i] = i;
}

UnionFind::UnionFind()
{
	reset(0);
}

UnionFind::UnionFind(int mSize)
{
	reset(mSize);
}

UnionFind::UnionFind(const UnionFind & another)
{
	_parent = another._parent;
	_rank = another._rank;
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

	_numSet--;
	if(_rank[leaderOne] < _rank[leaderTwo])
		_parent[leaderOne] = leaderTwo;
	else
	{
		_parent[leaderTwo] = leaderOne;

		if(_rank[leaderOne] == _rank[leaderTwo])
			_rank[leaderOne]++;
	}
}

int getMaximumWeightInMST(vector<pair<int, pair<int, int> > > & edgeList, int numV);

int main(void)
{
	vector<pair<int, pair<int, int> > > edgeList;
	int numV, numE, u, v, weight, minRange;

	while(1)
	{
		scanf("%d %d", &numV, &numE);
		if(!(numV || numE))
			break;

		edgeList.clear();

		for(int e = 0; e < numE; e++)
		{
			scanf("%d %d %d", &u, &v, &weight);
			edgeList.push_back(pair<int, pair<int, int> > (weight, pair<int, int> (u, v)));
		}

		minRange = getMaximumWeightInMST(edgeList, numV);
		if(minRange < 0)
			// The graph is not connected
			printf("IMPOSSIBLE\n");
		else
			printf("%d\n", minRange);		
	}
	return 0;
}

int getMaximumWeightInMST(vector<pair<int, pair<int, int> > > & edgeList, int numV)
{
	// Sort the edge list
	sort(edgeList.begin(), edgeList.end());

	UnionFind spanningForest(numV);

	pair<int, pair<int, int> > edge;
	int weight, u, v, maxWeight = -1;

	for(int e = 0; e < (int) edgeList.size(); e++)
	{
		edge = edgeList[e];
		weight = edge.first;
		u = edge.second.first;
		v = edge.second.second;

		if(!spanningForest.areInSameSet(u, v))
		{
			if(weight > maxWeight)
				maxWeight = weight;
			spanningForest.unionSet(u, v);
		}
	}

	if(spanningForest.getNumDisjointSet() != 1)
		// The graph is not connected
		return -1;
	return maxWeight;
}
