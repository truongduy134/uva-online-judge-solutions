#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

class UnionSet {
private:
    vector<int> _rank, _parent;
    int _numSet;
public:
    UnionSet();
    UnionSet(int numSet);
    void reset(int newSize);

    int getLeader(int u);
    bool areInSameSet(int u, int v);
    void unionSet(int u, int v);
    int getNumSet();
};

UnionSet::UnionSet()
{
    reset(0);
}

void UnionSet::reset(int newSize)
{
    _rank.assign(newSize, 0);
    _parent.assign(newSize, 0);
    _numSet = newSize;

    for(int i = 0; i < newSize; i++)
        _parent[i] = i;
}

UnionSet::UnionSet(int numSet)
{
    reset(numSet);
}

int UnionSet::getLeader(int u)
{
    if(_parent[u] == u)
        return u;

    int leader = getLeader(_parent[u]);
    _parent[u] = leader;
    return leader;
}

int UnionSet::getNumSet()
{
    return _numSet;
}

bool UnionSet::areInSameSet(int u, int v)
{
    return getLeader(u) == getLeader(v);
}

void UnionSet::unionSet(int u, int v)
{
    int leaderU = getLeader(u), leaderV = getLeader(v);

    if(leaderU == leaderV)
        return;

    _numSet--;
    if(_rank[leaderU] > _rank[leaderV])
    {
        _parent[leaderV] = leaderU;
    }
    else
    {
        _parent[leaderU] = leaderV;
        if(_rank[leaderU] == _rank[leaderV])
            _rank[leaderV]++;
    }
}

int getWeightMinSpanTree(vector<pair<int, pair<int, int> > > & edgeList, int numV)
{
    sort(edgeList.begin(), edgeList.end());

    int minW = 0, numE = (int) edgeList.size(), wE;
    UnionSet spanForest(numV);
    pair<int, int> pairV;
    for(int i = 0; i < numE; i++)
    {
        if(spanForest.getNumSet() == 1)
            break;

        wE = edgeList[i].first;
        pairV = edgeList[i].second;
        if(!spanForest.areInSameSet(pairV.first, pairV.second))
        {
            minW += wE;
            spanForest.unionSet(pairV.first, pairV.second);
        }
    }

    return minW;
}

int main(void)
{
    vector<pair<int, pair<int, int> > > edgeList;
    int numV, numE, sumE, u, v, weightE, minSpanTree;

    //freopen("in.txt", "r", stdin);

    while(1)
    {
        scanf("%d %d", &numV, &numE);
        if(numV == 0 && numE == 0)
            break;

        edgeList.clear();
        sumE = 0;

        for(int i = 0; i < numE; i++)
        {
            scanf("%d %d %d", &u, &v, &weightE);
            sumE += weightE;
            edgeList.push_back(make_pair(weightE, make_pair(u, v)));
        }

        minSpanTree = getWeightMinSpanTree(edgeList, numV);
        printf("%d\n", sumE - minSpanTree);
    }

    return 0;
}
