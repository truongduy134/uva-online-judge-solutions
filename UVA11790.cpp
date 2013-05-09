#include <cstdio>
#include <vector>

using namespace std;

vector<int> memoTable;

int LISTopDown(int n, vector<int> &heightArr, vector<int> &widthArr)
{
        if(memoTable[n] >= 0)
            return memoTable[n];

        int longestLen = widthArr[n], newLen;
        for(int i = 0; i < n; i++)
            if(heightArr[i] < heightArr[n])
            {
                newLen = widthArr[n] + LISTopDown(i, heightArr, widthArr);
                if(newLen > longestLen)
                    longestLen = newLen;
            }

        memoTable[n] = longestLen;
        return longestLen;
}

int computeLIS(vector<int> &heightArr, vector<int> &widthArr)
{
    int N = (int) heightArr.size();
    memoTable.assign(N, -1);

    int longestLen = 0, newLen;
    for(int i = N - 1; i >= 0; i--)
    {
        newLen = LISTopDown(i, heightArr, widthArr);
        if(newLen > longestLen)
            longestLen = newLen;
    }

    return longestLen;
}

int main(void)
{
    int T, caseId, N, valLIS, valLDS;
    vector<int> heightArr, widthArr;

 //   freopen("in.txt", "r", stdin);

    caseId = 1;
    scanf("%d", &T);
    while(caseId <= T)
    {
        scanf("%d", &N);
        heightArr.assign(N, 0);
        widthArr.assign(N, 0);

        for(int i = 0; i < N; i++)
            scanf("%d", &heightArr[i]);
        for(int i = 0; i < N; i++)
            scanf("%d", &widthArr[i]);

        valLIS = computeLIS(heightArr, widthArr);
        for(int i = 0; i < N; i++)
            heightArr[i] = -heightArr[i];
        valLDS = computeLIS(heightArr, widthArr);

        if(valLIS >= valLDS)
            printf("Case %d. Increasing (%d). Decreasing (%d).\n", caseId, valLIS, valLDS);
        else
            printf("Case %d. Decreasing (%d). Increasing (%d).\n", caseId, valLDS, valLIS);

        caseId++;
    }
    return 0;
}
