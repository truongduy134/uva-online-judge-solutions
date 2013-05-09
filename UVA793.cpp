#include <cstdio>
#include <vector>
#include <cstdlib>
using namespace std;

class UnionSet {
private:
    vector<int> _parent, _rank;

public:
    UnionSet();
    UnionSet(int mSize);

    void clearAndReset(int newSize);
    int findSetLeader(int ele);
    bool areSameSet(int one, int two);
    void unionSet(int one, int two);
};

UnionSet::UnionSet()
{
    _parent.assign(0, 0);
    _rank.assign(0, 0);
}

UnionSet::UnionSet(int mSize)
{
    _rank.assign(mSize, 0);
    _parent.assign(mSize, 0);
    for(int i = 0; i < mSize; i++)
        _parent[i] = i;
}

void UnionSet::clearAndReset(int newSize)
{
    _rank.assign(newSize, 0);
    _parent.assign(newSize, 0);
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

bool UnionSet::areSameSet(int one, int two)
{
    return findSetLeader(one) == findSetLeader(two);
}

void UnionSet::unionSet(int one, int two)
{
    int leaderOne = findSetLeader(one);
    int leaderTwo = findSetLeader(two);

    if(leaderOne == leaderTwo)
        return;

    if(_rank[leaderOne] > _rank[leaderTwo])
        _parent[leaderTwo] = leaderOne;
    else
    {
        _parent[leaderOne] = leaderTwo;
        if(_rank[leaderOne] == _rank[leaderTwo])
            _rank[leaderTwo]++;
    }
}

int main(void)
{
    int T, one, two, totalQuery, rightQuery, numComputer;
    char op[3], trash[3], line[100];
    UnionSet mSet;

 //   freopen("in.txt", "r", stdin);
 //   freopen("out.txt", "w", stdout);

    scanf("%d", &T);
    gets(trash);
    gets(trash);

    while(T)
    {
        totalQuery = 0;
        rightQuery = 0;

        scanf("%d", &numComputer);
        gets(trash);
        mSet.clearAndReset(numComputer);
        while(gets(line) != NULL && line[0] != '\0')
        {
            sscanf(line, "%s %d %d", op, &one, &two);
            if(op[0] == 'c')
                mSet.unionSet(one - 1, two - 1);
            else
            {
                totalQuery++;
                if(mSet.areSameSet(one - 1, two - 1))
                    rightQuery++;
            }
        }

        printf("%d,%d\n", rightQuery, totalQuery - rightQuery);
        if(T != 1)
            printf("\n");
        T--;
    }
    return 0;
}
