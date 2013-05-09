#include <cstdio>
#include <vector>

using namespace std;

class FenwickTree
{
private:
    vector<int> fenTree;
public:
    FenwickTree(int mSize);
    FenwickTree();
    void add(int index, int val);
    void reset(int mSize);
    int rangeSumQuery(int index);
    int rangeSumQuery(int left, int right);
};

FenwickTree::FenwickTree()
{
    fenTree.assign(1, 0);
}

FenwickTree::FenwickTree(int mSize)
{
    fenTree.assign(mSize + 1, 0);
}

void FenwickTree::reset(int mSize)
{
    fenTree.assign(mSize + 1, 0);
}

void FenwickTree::add(int index, int val)
{
    for(; index < (int) fenTree.size(); index += (index & (-index)))
        fenTree[index] += val;
}

int FenwickTree::rangeSumQuery(int index)
{
    int sum = 0;
    for(; index; index -= (index & (-index)))
        sum += fenTree[index];

    return sum;
}

int FenwickTree::rangeSumQuery(int left, int right)
{
    if(left == 1)
        return rangeSumQuery(right);
    else
        return rangeSumQuery(right) - rangeSumQuery(left - 1);
}

#define MAX_LEN 10

int main(void)
{
    int N, left, right, pos, newVal, caseId;
    vector<int> ohmVal;
    char cmd[MAX_LEN];
    FenwickTree fenTreeObj;

//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);

    caseId = 1;
    while(1)
    {
        scanf("%d", &N);
        if(N == 0)
            break;

        ohmVal.assign(N, 0);
        fenTreeObj.reset(N);

        for(int i = 0; i < N; i++)
        {
            scanf("%d", &ohmVal[i]);
            fenTreeObj.add(i + 1, ohmVal[i]);
        }

        if(caseId != 1)
            printf("\n");
        printf("Case %d:\n", caseId);

        while(1)
        {
            scanf("%s", cmd);
            if(cmd[0] == 'E')
                break;

            if(cmd[0] == 'M')
            {
                scanf("%d %d", &left, &right);
                printf("%d\n", fenTreeObj.rangeSumQuery(left, right));
            }
            else
            {
                scanf("%d %d", &pos, &newVal);
                fenTreeObj.add(pos, newVal - ohmVal[pos - 1]);
                ohmVal[pos - 1] = newVal;
            }
        }

        caseId++;
    }
    return 0;
}
