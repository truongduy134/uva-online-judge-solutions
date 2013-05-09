#include <cstdio>
#include <map>
#include <vector>
#include <utility>
#include <algorithm>
#include <string>

using namespace std;

#define MAX_LEN 100

class UnionFind {
private:
    vector<int> _parent, _rank;
    int _numDisjointSet;
public:
    UnionFind();
    UnionFind(int numSet);
    UnionFind(const UnionFind & another);
    ~UnionFind() {}

    void reset(int newNumSet);
    int findLeader(int ele);
    bool areInSameSet(int eleOne, int eleTwo);
    void unionSet(int eleOne, int eleTwo);
    int getNumDisjointSet() {return _numDisjointSet;}
};

UnionFind::UnionFind()
{
    reset(0);
}

UnionFind::UnionFind(int newNumSet)
{
    reset(newNumSet);
}

UnionFind::UnionFind(const UnionFind & another)
{
    _parent = another._parent;
    _rank = another._rank;
    _numDisjointSet = another._numDisjointSet;
}

void UnionFind::reset(int numSet)
{
    _parent.assign(numSet, 0);
    _rank.assign(numSet, 0);
    _numDisjointSet = numSet;

    for(int i = 0; i < numSet; i++)
        _parent[i] = i;
}

int UnionFind::findLeader(int ele)
{
    if(_parent[ele] == ele)
        return ele;
    _parent[ele] = findLeader(_parent[ele]);
    return _parent[ele];
}

bool UnionFind::areInSameSet(int eleOne, int eleTwo)
{
    return findLeader(eleOne) == findLeader(eleTwo);
}

void UnionFind::unionSet(int eleOne, int eleTwo)
{
    int leaderOne = findLeader(eleOne), leaderTwo = findLeader(eleTwo);

    if(leaderOne == leaderTwo)
        return;

    _numDisjointSet--;
    if(_rank[leaderOne] < _rank[leaderTwo])
    {
        _parent[leaderOne] = leaderTwo;
    }
    else
    {
        _parent[leaderTwo] = leaderOne;
        if(_rank[leaderTwo] == _rank[leaderOne])
            _rank[leaderOne]++;
    }
}

int getCostOfMinSpanningTree(vector<pair<int, pair<int, int> > > & edgeList, int numV);

int main(void)
{
    int numE, numV, cost, minCost;
    map<string, int> mapNameToId;
    vector<pair<int, pair<int, int> > > edgeList;
    char cityOne[MAX_LEN + 1], cityTwo[MAX_LEN + 1];

    while(1)
    {
        scanf("%d %d", &numV, &numE);
        if(numV == 0 && numE == 0)
            break;

        mapNameToId.clear();
        edgeList.clear();

        for(int id = 0; id < numV; id++)
        {
            scanf("%s", cityOne);
            mapNameToId[cityOne] = id;
        }

        for(int e = 0; e < numE; e++)
        {
            scanf("%s %s %d", cityOne, cityTwo, &cost);
            edgeList.push_back(make_pair(cost,
                                         make_pair(mapNameToId[cityOne], mapNameToId[cityTwo])));
        }
        scanf("%s", cityOne);

        minCost = getCostOfMinSpanningTree(edgeList, numV);
        if(minCost < 0)
            printf("Impossible\n");
        else
            printf("%d\n", minCost);
    }
    return 0;
}

int getCostOfMinSpanningTree(vector<pair<int, pair<int, int> > > & edgeList, int numV)
{
    sort(edgeList.begin(), edgeList.end());

    UnionFind disjointSet(numV);
    int sumCost = 0;

    pair<int, pair<int, int> > curEdge;
    int cost, u, v;
    for(int e = 0; e < (int) edgeList.size(); e++)
    {
        curEdge = edgeList[e];
        cost = curEdge.first;
        u = curEdge.second.first;
        v = curEdge.second.second;

        if(!disjointSet.areInSameSet(u, v))
        {
            sumCost += cost;
            disjointSet.unionSet(u, v);
        }
    }

    if(disjointSet.getNumDisjointSet() != 1)
        return -1;

    return sumCost;
}
