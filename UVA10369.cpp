#include <cstdio>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define MAX_SIZE 600

class UnionSet {
private:
    vector<int> _rank, _parent;
    int _numSet;
public:
    UnionSet(int initSize);

    int getLeader(int u);
    bool areInSameSet(int u, int v);
    void unionSet(int u, int v);
    int getNumSet();
};

int UnionSet::getNumSet()
{
    return _numSet;
}

UnionSet::UnionSet(int initSize)
{
    _rank.assign(initSize, 0);
    _parent.assign(initSize, 0);
    _numSet = initSize;

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
    if(_rank[leaderU] < _rank[leaderV])
        _parent[leaderU] = leaderV;
    else
    {
        _parent[leaderV] = leaderU;

        if(_rank[leaderU] == _rank[leaderV])
            _rank[leaderU]++;
    }
}

double getMinEdgeForest(vector<pair<double, pair<int, int> > > & edgeList, int numV, int numForest)
{
    sort(edgeList.begin(), edgeList.end());

    UnionSet allForest(numV);
    double maxE = 0, wE;
    int numE = (int) edgeList.size();
    pair<int, int> pairV;

    for(int i = 0; i < numE && allForest.getNumSet() != numForest; i++)
    {
        wE = edgeList[i].first;
        pairV = edgeList[i].second;

        if(!allForest.areInSameSet(pairV.first, pairV.second))
        {
            if(maxE < wE)
                maxE = wE;

            allForest.unionSet(pairV.first, pairV.second);
        }
    }

    return maxE;
}

int main(void)
{
    int T, numSatellite, numPost, xCoord[MAX_SIZE], yCoord[MAX_SIZE];
    double dist;
    vector<pair<double, pair<int, int> > > edgeList;

   // freopen("in.txt", "r", stdin);

    scanf("%d", &T);

    while(T)
    {
        edgeList.clear();

        scanf("%d %d", &numSatellite, &numPost);

        for(int i = 0; i < numPost; i++)
            scanf("%d %d", &xCoord[i], &yCoord[i]);

        for(int u = 0; u < numPost; u++)
            for(int v = u + 1; v < numPost; v++)
            {
                dist = sqrt((xCoord[u] - xCoord[v]) * (xCoord[u] - xCoord[v]) +
                            (yCoord[u] - yCoord[v]) * (yCoord[u] - yCoord[v]));
                edgeList.push_back(make_pair(dist, make_pair(u, v)));
            }

        printf("%.2lf\n", getMinEdgeForest(edgeList, numPost, numSatellite));

        T--;
    }
    return 0;
}
