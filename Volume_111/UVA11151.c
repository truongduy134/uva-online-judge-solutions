#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 1001
#define NOT_PROCESSED -1
#define LEN_TRASH 2

int computeLongestPalindromeSubseq(char str[], int len);
int computeLongestCommonSubseq(char strOne[], char strTwo[], int posOne, int posTwo, int memoTable[][MAX_LENGTH]);
void reverseStr(char origin[], int len, char result[]);

int main(void)
{
    int T, len;
    char str[MAX_LENGTH + 1], trash[LEN_TRASH + 1];

    /*freopen("in.txt", "r", stdin);*/
    scanf("%d", &T);
    gets(trash);

    while(T)
    {
        gets(str);
        len = (int) strlen(str);

        printf("%d\n", computeLongestPalindromeSubseq(str, len));

        T--;
    }
    return 0;
}

int computeLongestPalindromeSubseq(char str[], int len)
{
    char rev[MAX_LENGTH + 1];
    int memoTable[MAX_LENGTH][MAX_LENGTH], row, col;

    reverseStr(str, len, rev);

    for(row = 0; row < len; row++)
        for(col = 0; col < len; col++)
            memoTable[row][col] = NOT_PROCESSED;

    return computeLongestCommonSubseq(str, rev, len - 1, len - 1, memoTable);
}

int computeLongestCommonSubseq(char strOne[], char strTwo[], int posOne, int posTwo, int memoTable[][MAX_LENGTH])
{
    if(posTwo < 0 || posOne < 0)
        return 0;

    if(memoTable[posOne][posTwo] != NOT_PROCESSED)
        return memoTable[posOne][posTwo];

    int maxLen = 0, len = 0;

    if(strOne[posOne] == strTwo[posTwo])
        len = 1;
    len += computeLongestCommonSubseq(strOne, strTwo, posOne - 1, posTwo - 1, memoTable);
    if(len > maxLen)
        maxLen = len;

    len = computeLongestCommonSubseq(strOne, strTwo, posOne, posTwo - 1, memoTable);
    if(len > maxLen)
        maxLen = len;

    len = computeLongestCommonSubseq(strOne, strTwo, posOne - 1, posTwo, memoTable);
    if(len > maxLen)
        maxLen = len;

    memoTable[posOne][posTwo] = maxLen;
    return maxLen;
}

void reverseStr(char origin[], int len, char result[])
{
    int left, right;

    result[len] = '\0';

    for(left = 0, right = len - 1; left < len; left++, right--)
        result[left] = origin[right];
}
