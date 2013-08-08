#include <cstdio>
#include <vector>
#include <utility>

using namespace std;

class UnionFind 
{
private:
	vector<int> _parent, _rank;

	int getLeader(int ele);

public:
	UnionFind();
	UnionFind(int mSize);
	UnionFind(const UnionFind & another);
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

	if(_rank[leaderOne] < _rank[leaderTwo])
	{
		_parent[leaderOne] = leaderTwo;
	}
	else
	{
		_parent[leaderTwo] = leaderOne;

		if(_rank[leaderOne] == _rank[leaderTwo])
			_rank[leaderOne]++;
	}
}

const int MAX_SIZE = 100050;
const int MAX_LEN_LINE = 1000;

int simulateAcceptingBindingPairs(const vector<pair<int, int> > & bindingPairList);

int main(void)
{
	vector<pair<int, int> > bindingPairList;
	char line[MAX_LEN_LINE + 1];
	int eleOne, eleTwo;

	while(scanf("%d", &eleOne) > 0)
	{
		bindingPairList.clear();

		while(1)
		{
			if(eleOne < 0)
				break;

			scanf("%d", &eleTwo);

			bindingPairList.push_back(pair<int, int> (eleOne, eleTwo));
			
			scanf("%d", &eleOne);
		}

		printf("%d\n", simulateAcceptingBindingPairs(bindingPairList));
	}

	return 0;
}

/* The functions Return the number of refusals.
 *
 * Methodology:
 * 	+ A binding pair is refused if it mixes N different binding pairs containing N simple compounds creates a powerful explosive
 *	+ Here we build a graph with compounds as vertices. A binding pair is an edge between two compounds.
 *	+ Therefore, a binding pair is refused if it forms a cycle in our graph.
 */
int simulateAcceptingBindingPairs(const vector<pair<int, int> > & bindingPairList)
{
	UnionFind mSet(MAX_SIZE);
	int numRefusal = 0, eleOne, eleTwo;

	for(int pair = 0; pair < (int) bindingPairList.size(); pair++)
	{
		eleOne = bindingPairList[pair].first;
		eleTwo = bindingPairList[pair].second;

		if(mSet.areInSameSet(eleOne, eleTwo))
			numRefusal++;
		else
		{
			// Accept this binding pair
			mSet.unionSet(eleOne, eleTwo);
		}
	}

	return numRefusal;
}
