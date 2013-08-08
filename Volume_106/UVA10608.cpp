#include <cstdio>
#include <vector>

using namespace std;

class UnionSet
{
private:
    vector<int> _parent, _rank, _sizeSetVect;
    int _maxSizeSet;

public:
    UnionSet();
    UnionSet(int mSize);

    void clearAndReset(int newSize);
    int findSetLeader(int ele);
    bool areInSameSet(int one, int two);
    void unionSet(int one, int two);
    int getMaxSizeSet();
};

UnionSet::UnionSet()
{
    _parent.assign(0, 0);
    _rank.assign(0, 0);
    _sizeSetVect.assign(0, 0);
    _maxSizeSet = 0;
}

UnionSet::UnionSet(int mSize)
{
    clearAndReset(mSize);
}

void UnionSet::clearAndReset(int newSize)
{
    _parent.assign(newSize, 0);
    _rank.assign(newSize, 0);
    _sizeSetVect.assign(newSize, 1);
    _maxSizeSet = 1;

    for(int i = 0; i < newSize; i++)
        _parent[i] = i;
}

int UnionSet::findSetLeader(int ele)
{
    if(_parent[ele] == ele)
        return ele;
    _parent[ele] = findSetLeader(_parent[ele]);
    return _parent[ele];
}

bool UnionSet::areInSameSet(int one, int two)
{
    return findSetLeader(one) == findSetLeader(two);
}

void UnionSet::unionSet(int one, int two)
{
    int leaderOne = findSetLeader(one);
    int leaderTwo = findSetLeader(two);

    if(leaderOne == leaderTwo)
        return;

    int newSizeSet = _sizeSetVect[leaderOne] + _sizeSetVect[leaderTwo];
    if(newSizeSet > _maxSizeSet)
        _maxSizeSet = newSizeSet;

    if(_rank[leaderOne] > _rank[leaderTwo])
    {
        _parent[leaderTwo] = leaderOne;
        _sizeSetVect[leaderOne] = newSizeSet;
    }
    else
    {
        _parent[leaderOne] = leaderTwo;
        _sizeSetVect[leaderTwo] = newSizeSet;

        if(_rank[leaderOne] == _rank[leaderTwo])
            _rank[leaderTwo]++;
    }
}

int UnionSet::getMaxSizeSet()
{
    return _maxSizeSet;
}

int main(void)
{
    int T, numPeople, numPair, pOne, pTwo;
    UnionSet groupSet;

 //   freopen("in.txt", "r", stdin);
 //   freopen("out.txt", "w", stdout);

    scanf("%d", &T);
    while(T)
    {
        scanf("%d %d", &numPeople, &numPair);

        groupSet.clearAndReset(numPeople);

        for(int i = 0; i < numPair; i++)
        {
            scanf("%d %d", &pOne, &pTwo);

            groupSet.unionSet(pOne - 1, pTwo - 1);
        }

        printf("%d\n", groupSet.getMaxSizeSet());

        T--;
    }

    return 0;
}
