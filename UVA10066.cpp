#include <cstdio>
using namespace std;

#define MAX_SIZE 102

int memoTable[MAX_SIZE][MAX_SIZE];

int findLenLCS(int arr1[], int arr2[], int i1, int i2)
{
    if(i1 < 0 || i2 < 0)
        return 0;

    if(memoTable[i1][i2] >= 0)
        return memoTable[i1][i2];

    int maxLen = 0, len;
    if(arr1[i1] == arr2[i2])
        len = 1 + findLenLCS(arr1, arr2, i1 - 1, i2 - 1);
    else
        len = findLenLCS(arr1, arr2, i1 - 1, i2 - 1);
    if(len > maxLen)
        maxLen = len;

    len = findLenLCS(arr1, arr2, i1, i2 - 1);
    if(len > maxLen)
        maxLen = len;
    len = findLenLCS(arr1, arr2, i1 - 1, i2);
    if(len > maxLen)
        maxLen = len;

    memoTable[i1][i2] = maxLen;
    return maxLen;
}

int main(void)
{
    int N1, N2, arr1[MAX_SIZE], arr2[MAX_SIZE], caseId = 1;

  //  freopen("in.txt", "r", stdin);
  //  freopen("out.txt", "w", stdout);

    while(1)
    {
        scanf("%d %d", &N1, &N2);
        if(N1 == 0 && N2 == 0)
            break;

        for(int i = 0; i < N1; i++)
            scanf("%d", &arr1[i]);
        for(int i = 0; i < N2; i++)
            scanf("%d", &arr2[i]);

        for(int i = 0; i < N1; i++)
            for(int j = 0; j < N2; j++)
                memoTable[i][j] = -1;

        printf("Twin Towers #%d\n", caseId);
        printf("Number of Tiles : %d\n\n", findLenLCS(arr1, arr2, N1 - 1, N2 - 1));
        caseId++;
    }
    return 0;
}
