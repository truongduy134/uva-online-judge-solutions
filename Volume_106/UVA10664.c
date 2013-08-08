#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SIZE 30
#define MAX_LEN 2000
#define MAX_TOTAL_WEIGHT 300

int existEqualTwoPartition(int arr[], int mSize);
int existSubsetWithSum(int ind, int sum, int arr[], int memoTable[][MAX_TOTAL_WEIGHT]);

int main(void)
{
    int T, weightArr[MAX_SIZE], numLuggage;
    char line[MAX_LEN + 1], trash[MAX_LEN + 1], delim[] = " ", *ptrNumStr;

    scanf("%d", &T);
    gets(trash);

    while(T)
    {
        numLuggage = 0;

        gets(line);
        ptrNumStr = strtok(line, delim);
        do
        {
            if(ptrNumStr != NULL)
            {
                weightArr[numLuggage] = atoi(ptrNumStr);
                numLuggage++;
            }

            ptrNumStr = strtok(NULL, delim);
        } while(ptrNumStr != NULL);

        if(existEqualTwoPartition(weightArr, numLuggage))
            printf("YES\n");
        else
            printf("NO\n");

        T--;
    }

    return 0;
}

int existEqualTwoPartition(int arr[], int mSize)
{
    int i, sum = 0, memoTable[MAX_SIZE][MAX_TOTAL_WEIGHT];

    for(i = 0; i < mSize; i++)
        sum += arr[i];

    if(sum & 1)
        return 0;

    memset(memoTable, -1, MAX_SIZE * MAX_TOTAL_WEIGHT * sizeof(int));

    return existSubsetWithSum(mSize - 1, sum >> 1, arr, memoTable);
}

int existSubsetWithSum(int ind, int sum, int arr[], int memoTable[][MAX_TOTAL_WEIGHT])
{
    if(sum < 0)
        return 0;
    if(sum == 0)
        return 1;
    if(ind < 0)
        return 0;

    if(memoTable[ind][sum] >= 0)
        return memoTable[ind][sum];

    int result = existSubsetWithSum(ind - 1, sum, arr, memoTable) |
                 existSubsetWithSum(ind - 1, sum - arr[ind], arr, memoTable);

    memoTable[ind][sum] = result;

    return result;
}
