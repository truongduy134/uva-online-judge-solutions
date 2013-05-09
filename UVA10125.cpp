#include <cstdio>
#include <map>
#include <vector>
#include <utility>

using namespace std;

#define MINUS_INF -(1 << 30)
int main(void)
{
    int n, sum, maxD, a, b;
    vector<int> S;
    map<int, vector<pair<int, int> > > mapTable;
    map<int, vector<pair<int, int> > >::iterator itMap;
    vector<pair<int, int> > vectAB;

   // freopen("in.txt", "r", stdin);
   // freopen("out.txt", "w", stdout);

    while(1)
    {
        scanf("%d", &n);
        if(n == 0)
            break;

        S.assign(n, 0);
        for(int i = 0; i < n; i++)
            scanf("%d", &S[i]);

        mapTable.clear();

        for(int iA = 0; iA < n; iA++)
            for(int iB = iA + 1; iB < n; iB++)
            {
                sum = S[iA] + S[iB];

                itMap = mapTable.find(sum);
                if(itMap == mapTable.end())
                {
                    vector<pair<int, int> > newVect;
                    mapTable[sum] = newVect;
                }

                mapTable[sum].push_back(make_pair(S[iA], S[iB]));
            }

        maxD = MINUS_INF;
        for(int iC = 0; iC < n; iC++)
            for(int iD = 0; iD < n; iD++)
                if(iC != iD && S[iD] > maxD)
                {
                    sum = S[iD] - S[iC];

                    itMap = mapTable.find(sum);
                    if(itMap != mapTable.end())
                    {
                        vectAB = itMap->second;
                        for(int i = 0; i < (int) vectAB.size(); i++)
                        {
                            a = vectAB[i].first;
                            b = vectAB[i].second;
                            if(a != S[iC] && a != S[iD] && b != S[iC] && b != S[iD])
                            {
                                maxD = S[iD];
                                break;
                            }
                        }
                    }
                }

        if(maxD == MINUS_INF)
            printf("no solution\n");
        else
            printf("%d\n", maxD);
    }
}
