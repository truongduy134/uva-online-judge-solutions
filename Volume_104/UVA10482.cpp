#include <cstdio>

using namespace std;

#define MAX_NUM 32
#define MAX_SUM 640


int memoTable[MAX_NUM][MAX_SUM + 1][MAX_SUM + 1];
int totalWeight;

int findMinDiff(int w[], int curObjInd, int sizeOne, int sizeTwo)
{
    if(curObjInd < 0)
    {
        int sizeThree = totalWeight - sizeOne - sizeTwo;
        int maxSize = sizeOne, minSize = sizeOne;
        if(sizeTwo > maxSize)
            maxSize = sizeTwo;
        if(sizeThree > maxSize)
            maxSize = sizeThree;
        if(sizeTwo < minSize)
            minSize = sizeTwo;
        if(sizeThree < minSize)
            minSize = sizeThree;
        return maxSize - minSize;
    }

    if(memoTable[curObjInd][sizeOne][sizeTwo] >= 0)
        return memoTable[curObjInd][sizeOne][sizeTwo];

    int minDiff = totalWeight;
    int diff;
    // This item belong to the first set
    diff = findMinDiff(w, curObjInd - 1, sizeOne + w[curObjInd], sizeTwo);
    if(minDiff > diff)
        minDiff = diff;
     // This item belong to the second set
     diff = findMinDiff(w, curObjInd - 1, sizeOne, sizeTwo + w[curObjInd]);
     if(minDiff > diff)
        minDiff = diff;
     // This item belong to the third set
     diff = findMinDiff(w, curObjInd - 1, sizeOne, sizeTwo);
     if(minDiff > diff)
        minDiff = diff;

     memoTable[curObjInd][sizeOne][sizeTwo] = minDiff;

     return minDiff;
}

int main(void)
{
    int T, n, w[MAX_NUM], caseId;

   //freopen("in.txt", "r", stdin);
   // freopen("out.txt", "r", stdout);


    scanf("%d", &T);
    caseId = 1;
    while(caseId <= T)
    {
        scanf("%d", &n);

        for(int i = 0; i < n; i++)
            for(int j = 0; j <= MAX_SUM; j++)
                for(int k = 0; k <= MAX_SUM; k++)
                    memoTable[i][j][k] = -1;

        totalWeight = 0;
        for(int i = 0; i < n; i++)
        {
            scanf("%d", &w[i]);
            totalWeight += w[i];
        }

        printf("Case %d: %d\n", caseId, findMinDiff(w, n - 1, 0, 0));
        caseId++;
    }
    return 0;
}
