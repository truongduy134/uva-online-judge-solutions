/*******************************************************
 * Author: Nguyen Truong Duy
 *******************************************************/

#include <cstdio>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

class UnionFind
{
private:
	vector<int> _rank, _parent;
	int getLeader(int ele);

public:
	UnionFind(int numEle);
	~UnionFind() {}
	bool areInSameSet(int eleOne, int eleTwo);
	void unionSet(int eleOne, int eleTwo);	
};

UnionFind::UnionFind(int numEle)
{
	_rank.assign(numEle, 0);
	_parent.assign(numEle, 0);

	for(int i = 0; i < numEle; i++)
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

struct Edge
{
	double weight;
	int u, v;

	Edge(int inU, int inV, double inWeight);
	Edge();
	bool operator< (const Edge & another) const;
};

Edge::Edge(int inU, int inV, double inWeight)
{
	u = inU;
	v = inV;
	weight = inWeight;
}

Edge::Edge()
{
	u = v = 0;
	weight = 0.0;
}

bool Edge::operator< (const Edge & another) const 
{
	return weight < another.weight;
}

struct Coord
{
	int x, y;

	Coord() { x = y = 0; }
	Coord(int inX, int inY) { x = inX; y = inY; }
};

double getDistance(const Coord & one, const Coord & two)
{
	return sqrt((one.x - two.x) * (one.x - two.x) + (one.y - two.y) * (one.y - two.y));
}

double getTotalWeightOfMST(vector<Edge> & edgeList, int numV);

int main(void)
{
	vector<Edge> edgeList;
	vector<Coord> coordList;
	int numV, numExistE, u, v;

	while(scanf("%d", &numV) > 0)
	{
		coordList.assign(numV, Coord() );
		edgeList.clear();

		for(int i = 0; i < numV; i++)
		{
			scanf("%d %d", &coordList[i].x, &coordList[i].y);
		}

		scanf("%d", &numExistE);

		for(int i = 0; i < numExistE; i++)
		{
			scanf("%d %d", &u, &v);
			u--;
			v--;
			edgeList.push_back(Edge(u, v, 0.0));
		}

		for(u = 0; u < numV; u++)
			for(v = u + 1; v < numV; v++)
				edgeList.push_back(Edge(u, v, getDistance(coordList[u], coordList[v])));

		printf("%.2lf\n", getTotalWeightOfMST(edgeList, numV));
	}
	return 0; 
}

double getTotalWeightOfMST(vector<Edge> & edgeList, int numV)
{
	sort(edgeList.begin(), edgeList.end());

	UnionFind disjointForest(numV);

	int u, v;
	double weight, total = 0;
	for(int i = 0; i < (int) edgeList.size(); i++)
	{
		u = edgeList[i].u;
		v = edgeList[i].v;
		weight = edgeList[i].weight;

		if(disjointForest.areInSameSet(u, v) == false)
		{
			disjointForest.unionSet(u, v);
			total += weight;
		}
	}

	return total;
}
