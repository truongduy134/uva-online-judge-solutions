/************************************************************
 *  Author: Nguyen Truong Duy
 ***********************************************************/
#include <cstdio>
#include <vector>
#include <map>
#include <string>
#include <utility>

using namespace std;

#define MAX_NAME_LEN 20

class UnionFind
{
private:
    vector<int> _parent, _rank, _setSize;

    int getLeader(int ele);

public:
    UnionFind() { reset(0); }
    UnionFind(int mSize) { reset(mSize); }
    UnionFind(const UnionFind & another) : _parent(another._parent), _rank(another._rank),
            _setSize(another._setSize)
    {
    }
    ~UnionFind() {}

    void reset(int newSize);
    int getSetSize(int ele);
    bool areInSameSet(int eleOne, int eleTwo);
    void unionSet(int eleOne, int eleTwo);
};

void UnionFind::reset(int newSize)
{
    _parent.assign(newSize, 0);
    _rank.assign(newSize, 0);
    _setSize.assign(newSize, 1);

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

int UnionFind::getSetSize(int ele)
{
    return _setSize[getLeader(ele)];
}

void UnionFind::unionSet(int eleOne, int eleTwo)
{
    int leaderOne = getLeader(eleOne), leaderTwo = getLeader(eleTwo);

    if(leaderOne == leaderTwo)
        return;

    if(_rank[leaderOne] < _rank[leaderTwo])
    {
        _parent[leaderOne] = leaderTwo;
        _setSize[leaderTwo] += _setSize[leaderOne];
    }
    else
    {
        _parent[leaderTwo] = leaderOne;
        _setSize[leaderOne] += _setSize[leaderTwo];

        if(_rank[leaderOne] == _rank[leaderTwo])
            _rank[leaderOne]++;
    }
}

int getNameId(char name[], map<string, int> & mapNameToId, int * nextIdToAssign);

int main(void)
{
    char nameOne[MAX_NAME_LEN + 1], nameTwo[MAX_NAME_LEN + 1];
    vector<pair<int, int> > friendshipVect;
    UnionFind friendSet;
    map<string, int> mapNameToId;
    int T, numFriendship, idOne, idTwo, nextIdToAssign, numPeople;

    scanf("%d", &T);

    while(T)
    {
        scanf("%d", &numFriendship);

        friendshipVect.assign(numFriendship, pair<int, int> (0, 0));
        mapNameToId.clear();

        nextIdToAssign = 0;
        for(int i = 0; i < numFriendship; i++)
        {
            scanf("%s %s", nameOne, nameTwo);
            idOne = getNameId(nameOne, mapNameToId, &nextIdToAssign);
            idTwo = getNameId(nameTwo, mapNameToId, &nextIdToAssign);

            friendshipVect[i].first = idOne;
            friendshipVect[i].second = idTwo;
        }
        numPeople = nextIdToAssign;

        friendSet.reset(numPeople);
        for(int i = 0; i < numFriendship; i++)
        {
            // Form friendship
            friendSet.unionSet(friendshipVect[i].first, friendshipVect[i].second);
            printf("%d\n", friendSet.getSetSize(friendshipVect[i].first));
        }
        T--;
    }
    return 0;
}

int getNameId(char name[], map<string, int> & mapNameToId, int * nextIdToAssign)
{
    map<string, int>::iterator it = mapNameToId.find(name);
    int returnId;

    if(it == mapNameToId.end())
    {
        returnId = *nextIdToAssign;
        mapNameToId[name] = returnId;
        (*nextIdToAssign)++;
    }
    else
        returnId = it->second;

    return returnId;
}
