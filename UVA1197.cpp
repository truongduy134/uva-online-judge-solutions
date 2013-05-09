#include <cstdio>
#include <vector>

using namespace std;

class UnionFind {
private:
    vector<int> parentVector, rankVector, sizeVector;

public:
    UnionFind(int numSet);
    int findSet(int element);
    int getSetSize(int element);
    bool isSameSet(int eleOne, int eleTwo);
    void unionSet(int eleOne, int eleTwo);

};

UnionFind::UnionFind(int numSet)
{
    rankVector.assign(numSet, 0);
    sizeVector.assign(numSet, 1);
    parentVector.assign(numSet, 0);
    for(int i = 0; i < numSet; i++)
        parentVector[i] = i;
}

int UnionFind::findSet(int element)
{
    if(parentVector[element] == element)
        return element;
    else
    {
        parentVector[element] = findSet(parentVector[element]);
        return parentVector[element];
    }
}

int UnionFind::getSetSize(int element)
{
    if(parentVector[element] == element)
        return sizeVector[element];
    else
    {
        sizeVector[element] = getSetSize(parentVector[element]);
        return sizeVector[element];
    }
}

bool UnionFind::isSameSet(int eleOne, int eleTwo)
{
    return findSet(eleOne) == findSet(eleTwo);
}

void UnionFind::unionSet(int eleOne, int eleTwo)
{
    if(isSameSet(eleOne, eleTwo))
        return;


    int setOne = findSet(eleOne), setTwo = findSet(eleTwo);
    int sizeOne = getSetSize(eleOne), sizeTwo = getSetSize(eleTwo);

    if(rankVector[setOne] > rankVector[setTwo])
    {
        parentVector[setTwo] = setOne;
        sizeVector[setOne] = sizeOne + sizeTwo;
    }
    else
    {
        parentVector[setOne] = setTwo;
        sizeVector[setTwo] = sizeOne + sizeTwo;
        if(rankVector[setOne] == rankVector[setTwo])
            rankVector[setTwo]++;
    }
}

int main(void)
{
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);

    int numStudent, numGroup, numMember, hostMem, nextMem;

    while(1)
    {
        scanf("%d %d", &numStudent, &numGroup);

        if(numStudent == 0 && numGroup == 0)
            break;

        UnionFind mySet(numStudent);

        for(int group = 0; group < numGroup; group++)
        {
            scanf("%d %d", &numMember, &hostMem);
            for(int i = 1; i < numMember; i++)
            {
                scanf("%d", &nextMem);
                mySet.unionSet(hostMem, nextMem);
            }
        }

        printf("%d\n", mySet.getSetSize(0));

    }
    return 0;
}
