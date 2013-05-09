#include <cstdio>
#include <vector>
#include <algorithm>
#include <utility>
#include <queue>

using namespace std;

class UnionFind {
private:
    vector<int> _parent, _rank;

public:
    UnionFind();
    UnionFind(int mSize);
    UnionFind(const UnionFind & another);
    ~UnionFind() {}

    void reset(int newSize);
    bool areInSameSet(int eleOne, int eleTwo);
    int findLeader(int ele);
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

UnionFind::UnionFind(int newSize)
{
    reset(newSize);
}

UnionFind::UnionFind(const UnionFind & another)
{
    _parent = another._parent;
    _rank = another._rank;
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
    int leaderOne = findLeader(eleOne);
    int leaderTwo = findLeader(eleTwo);

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

void runKruskalMaxSpanningTree(vector<pair<int, pair<int, int> > > & edgeList, int numV,
                               vector<vector<pair<int, int> > > & adjListTree);
void breathFirstSearch(const vector<vector<pair<int, int> > > &adjList, int source, int dest,
                       vector<pair<int, int> > & parentArr);
int getMinOnPath(const vector<pair<int, int> > & parentArr, int source, int dest);

int main(void)
{
    vector<pair<int, pair<int, int> > > edgeList;
    vector<vector<pair<int, int> > > adjListTree;
    vector<pair<int, int> > parentArr;
    int numV, numE, numPassenger, startCity, endCity, cityOne, cityTwo, weight, bottleneck,
        numTrip, caseId;

    //freopen("in.txt", "r", stdin);

    caseId = 1;
    while(1)
    {
        scanf("%d %d", &numV, &numE);
        if(numV == 0 && numE == 0)
            break;

        edgeList.clear();

        for(int i = 0; i < numE; i++)
        {
            scanf("%d %d %d", &cityOne, &cityTwo, &weight);
            cityOne--;
            cityTwo--;
            edgeList.push_back(make_pair(weight, make_pair(cityOne, cityTwo)));
        }

        scanf("%d %d %d", &startCity, &endCity, &numPassenger);
        startCity--;
        endCity--;

        runKruskalMaxSpanningTree(edgeList, numV, adjListTree);
        breathFirstSearch(adjListTree, startCity, endCity, parentArr);

        bottleneck = getMinOnPath(parentArr, startCity, endCity);
        // Must preserve 1 palce for the tour guide on each trip!
        bottleneck--;

        numTrip = numPassenger / bottleneck;

        if(numPassenger % bottleneck)
            numTrip++;

        printf("Scenario #%d\nMinimum Number of Trips = %d\n\n", caseId, numTrip);

        caseId++;
    }

    return 0;
}

void runKruskalMaxSpanningTree(vector<pair<int, pair<int, int> > > & edgeList, int numV,
                               vector<vector<pair<int, int> > > & adjListTree)
{
    vector<pair<int, int> > emptyNeighborList;
    adjListTree.assign(numV, emptyNeighborList);

    sort(edgeList.begin(), edgeList.end());

    UnionFind disjointSet(numV);

    pair<int, pair<int, int> > edge;
    int weight, vOne, vTwo;
    // Find maximum spanning tree
    for(int ind = (int) edgeList.size() - 1; ind >= 0; ind--)
    {
        edge = edgeList[ind];
        weight = edge.first;
        vOne = edge.second.first;
        vTwo = edge.second.second;

        if(!disjointSet.areInSameSet(vOne, vTwo))
        {
            disjointSet.unionSet(vOne, vTwo);

            adjListTree[vOne].push_back(make_pair(vTwo, weight));
            adjListTree[vTwo].push_back(make_pair(vOne, weight));
        }
    }
}

void breathFirstSearch(const vector<vector<pair<int, int> > > &adjList, int source, int dest,
                       vector<pair<int, int> > & parentArr)
{
    int numV = (int) adjList.size();

    pair<int, int> emptyPair;
    parentArr.assign(numV, emptyPair);

    vector<bool> visited(numV, false);
    queue<int> vQueue;
    vQueue.push(source);
    visited[source] = true;

    int curV, nextV, weight;
    while(!vQueue.empty())
    {
        curV = vQueue.front();
        vQueue.pop();

        if(curV == dest)
            break;

        for(int i = 0; i < (int) adjList[curV].size(); i++)
        {
            nextV = adjList[curV][i].first;
            weight = adjList[curV][i].second;

            if(!visited[nextV])
            {
                visited[nextV] = true;
                parentArr[nextV] = make_pair(curV, weight);
                vQueue.push(nextV);
            }
        }
    }
}

int getMinOnPath(const vector<pair<int, int> > & parentArr, int source, int dest)
{
    if(source == dest)
        return 0;

    int minWeight = parentArr[dest].second, parent = parentArr[dest].first;

    while(parent != source)
    {
        if(minWeight > parentArr[parent].second)
            minWeight = parentArr[parent].second;

        parent = parentArr[parent].first;
    }

    return minWeight;
}
