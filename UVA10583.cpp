#include <cstdio>
#include <vector>

using namespace std;

class UnionFind
{
private:
    vector<int> _rank, _parent;
    int _numDisjointSet;

    int getLeader(int ele);

public:
    UnionFind() { reset(0); }
    UnionFind(int mSize) { reset(mSize); }
    UnionFind(const UnionFind & another) :
        _rank(another._rank), _parent(another._parent), _numDisjointSet(another._numDisjointSet)
    {
    }
    ~UnionFind() {}

    void reset(int newSize);
    int getNumDisjointSet() const {return _numDisjointSet;}
    bool areInSameSet(int eleOne, int eleTwo);
    void unionSet(int eleOne, int eleTwo);
};

void UnionFind::reset(int newSize)
{
    _rank.assign(newSize, 0);
    _parent.assign(newSize, 0);
    _numDisjointSet = newSize;

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

    _numDisjointSet--;

    if(_rank[leaderOne] < _rank[leaderTwo])
        _parent[leaderOne] = leaderTwo;
    else
    {
        _parent[leaderTwo] = leaderOne;
        if(_rank[leaderOne] == _rank[leaderTwo])
            _rank[leaderOne]++;
    }
}

int main(void)
{
    int numPeople, numPair, pOne, pTwo, caseId;
    UnionFind religionSets;

    //freopen("in.txt", "r", stdin);
    caseId = 1;
    while(1)
    {
        scanf("%d %d", &numPeople, &numPair);
        if(numPeople == 0 && numPair == 0)
            break;

        religionSets.reset(numPeople);

        for(int i = 0; i < numPair; i++)
        {
            scanf("%d %d", &pOne, &pTwo);
            religionSets.unionSet(pOne - 1, pTwo - 1);
        }

        printf("Case %d: %d\n", caseId, religionSets.getNumDisjointSet());

        caseId++;
    }

    return 0;
}
