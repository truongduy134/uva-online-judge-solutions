#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;

#define MAX_NUM 500
class UnionSet {
private:
    vector<int> _parent, _rank;
    int _numSet;

    int getLeader(int u);

public:
    UnionSet(int initSize);

    bool areInSameSet(int u, int v);
    void unionSet(int u, int v);
    int getNumSet();
};

UnionSet::UnionSet(int initSize)
{
    _parent.assign(initSize, 0);
    _rank.assign(initSize, 0);
    _numSet = 0;

    for(int i = 0; i < initSize; i++)
        _parent[i] = i;
}

int UnionSet::getLeader(int u)
{
    if(_parent[u] == u)
        return u;

    _parent[u] = getLeader(_parent[u]);
    return _parent[u];
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
        _parent[leaderV] = leaderU;
    else
    {
        _parent[leaderU] = leaderV;
        if(_rank[leaderU] == _rank[leaderV])
            _rank[leaderV]++;
    }
}

double getWeightMinSpanTree(vector<pair<double, pair<int ,int> > > & edgeList, int numV)
{
    sort(edgeList.begin(), edgeList.end());

    int numE = (int) edgeList.size();
    UnionSet spanForest(numV);
    double minCost = 0, cost;
    pair<int, int> pairV;

    for(int i = 0; i < numE; i++)
    {
        cost = edgeList[i].first;
        pairV = edgeList[i].second;

        if(!spanForest.areInSameSet(pairV.first, pairV.second))
        {
            minCost += cost;
            spanForest.unionSet(pairV.first, pairV.second);
        }
    }

    return minCost;
}
int main(void)
{
    int numV, T;
    double xCoord[MAX_NUM], yCoord[MAX_NUM], dist;
    vector<pair<double, pair<int, int> > > edgeList;

   // freopen("in.txt", "r", stdin);

    scanf("%d", &T);
    while(T)
    {
        scanf("%d", &numV);

        edgeList.clear();

        for(int i = 0; i < numV; i++)
            scanf("%lf %lf", &xCoord[i], &yCoord[i]);

        for(int u = 0; u < numV; u++)
            for(int v = u + 1; v < numV; v++)
            {
                dist = sqrt((xCoord[u] - xCoord[v]) * (xCoord[u] - xCoord[v]) +
                            (yCoord[u] - yCoord[v]) * (yCoord[u] - yCoord[v]));
                edgeList.push_back(make_pair(dist, make_pair(u, v)));
            }

        printf("%.2lf\n", getWeightMinSpanTree(edgeList, numV));
        if(T != 1)
            printf("\n");
        T--;
    }
    return 0;
}
