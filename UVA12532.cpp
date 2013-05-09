#include <cstdio>
#include <vector>

using namespace std;

class FenwickTree
{
private:
    vector<int> fenTree;
public:
    FenwickTree(int n);
    FenwickTree();
    void update(int index, int val);
    void reset(int newN);
    int rangeSumQuery(int b);
    int rangeSumQuery(int a, int b);
};

FenwickTree::FenwickTree()
{
    fenTree.assign(1, 0);
}
FenwickTree::FenwickTree(int n)
{
    fenTree.assign(n + 1, 0);
}

void FenwickTree::reset(int newN)
{
    fenTree.assign(newN + 1, 0);
}

void FenwickTree::update(int index, int val)
{
    while(index < (int) fenTree.size())
    {
        fenTree[index] += val;
        index += (index & (-index));
    }
}

int FenwickTree::rangeSumQuery(int b)
{
    int sum = 0;
    while(b)
    {
        sum += fenTree[b];
        b -= (b & (-b));
    }

    return sum;
}

int FenwickTree::rangeSumQuery(int a, int b)
{
    if(a == 1)
        return rangeSumQuery(b);
    else
        return rangeSumQuery(b) - rangeSumQuery(a - 1);
}

int main(void)
{
    char cmd[2];
    int N, K, param1, param2, temp, numZero, numNeg;
    vector<int> arr;
    FenwickTree numZeroTree, numNegTree;

   // freopen("in.txt", "r", stdin);
   // freopen("out.txt", "w", stdout);

    while(scanf("%d %d", &N, &K) > 0)
    {
        arr.assign(N, 0);
        numZeroTree.reset(N);
        numNegTree.reset(N);

        for(int i = 0; i < N; i++)
        {
            scanf("%d", &arr[i]);
            if(arr[i] == 0)
                numZeroTree.update(i + 1, 1);
            else
                if(arr[i] < 0)
                    numNegTree.update(i + 1, 1);
        }

        for(int i = 0; i < K; i++)
        {
            scanf("%s %d %d", cmd, &param1, &param2);

            if(cmd[0] == 'C')
            {
                if(param2 == 0)
                {
                    if(arr[param1 - 1])
                    {
                        numZeroTree.update(param1, 1);
                        if(arr[param1 - 1] < 0)
                            numNegTree.update(param1, -1);
                    }

                }
                else
                {
                    if(param2 < 0)
                    {
                        if(arr[param1 - 1] >= 0)
                        {
                            numNegTree.update(param1, 1);
                            if(arr[param1 - 1] == 0)
                                numZeroTree.update(param1, -1);
                        }
                    }
                    else
                    {
                        if(arr[param1 - 1] < 0)
                            numNegTree.update(param1, -1);
                        else
                            if(arr[param1 - 1] == 0)
                                numZeroTree.update(param1, -1);
                    }
                }

                arr[param1 - 1] = param2;
            }
            else
            {
                if(param1 > param2)
                {
                    temp = param1;
                    param1 = param2;
                    param2 = temp;
                }
                numZero = numZeroTree.rangeSumQuery(param1, param2);
                numNeg = numNegTree.rangeSumQuery(param1, param2);
                if(numZero)
                    printf("0");
                else
                    if(numNeg & 1)
                        // Odd number of negative numbers
                        printf("-");
                    else
                        printf("+");
            }
        }
        printf("\n");
    }
    return 0;
}
