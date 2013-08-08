#include <cstdio>
#include <cstring>

#define MAX_LEN 1000

int memoTable[MAX_LEN][MAX_LEN];

int computeLCS(char strA[], char strB[], int indA, int indB)
{
    if(indA < 0 || indB < 0)
        return 0;
    if(memoTable[indA][indB] >= 0)
        return memoTable[indA][indB];

    int maxLen = computeLCS(strA, strB, indA - 1, indB - 1);
    if(strA[indA] == strB[indB])
        maxLen++;

    int len = computeLCS(strA, strB, indA, indB - 1);
    if(len > maxLen)
        maxLen = len;

    len = computeLCS(strA, strB, indA - 1, indB);
    if(len > maxLen)
        maxLen = len;

    memoTable[indA][indB] = maxLen;
    return maxLen;
}

int main(void)
{
    char strA[MAX_LEN + 1], strB[MAX_LEN + 1];
    int lenA, lenB;

  //  freopen("in.txt", "r", stdin);

    while(gets(strA) != NULL)
    {
        gets(strB);

        lenA = (int) strlen(strA);
        lenB = (int) strlen(strB);

        for(int i = 0; i < lenA; i++)
            for(int j = 0; j < lenB; j++)
                memoTable[i][j] = -1;

        printf("%d\n", computeLCS(strA, strB, lenA - 1, lenB - 1));
    }
    return 0;
}
