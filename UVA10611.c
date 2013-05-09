#include <stdio.h>

#define MAX_SIZE 50000

int findSupremumInd(int sortedArr[], int mSize, int key);
int findInfimumInd(int sortedArr[], int mSize, int key);

int main(void)
{
    int sortedHeight[MAX_SIZE], mSize, numQuery, query, height, i, supremumInd, infimumInd;

    while(scanf("%d", &mSize) > 0)
    {
        for(i = 0; i < mSize; i++)
            scanf("%d", &sortedHeight[i]);

        scanf("%d", &numQuery);
        for(query = 0; query < numQuery; query++)
        {
            scanf("%d", &height);
            supremumInd = findSupremumInd(sortedHeight, mSize, height);
            infimumInd = findInfimumInd(sortedHeight, mSize, height);

             if(infimumInd < 0)
                printf("X ");
            else
                printf("%d ", sortedHeight[infimumInd]);
            if(supremumInd < 0)
                printf("X\n");
            else
                printf("%d\n", sortedHeight[supremumInd]);
        }
    }

    return 0;
}

/* Find an index i such that A[i - 1] <= key < A[i] */
int findSupremumInd(int sortedArr[], int mSize, int key)
{
    int left, right, mid;

    /* Corner case */
    if(sortedArr[0] > key)
        return 0;
    if(sortedArr[mSize - 1] <= key)
        return -1;

    left = 1;
    right = mSize - 1;
    while(left <= right)
    {
        mid = left + ((right - left) >> 1);
        if(sortedArr[mid - 1] <= key && key < sortedArr[mid])
            return mid;

        if(sortedArr[mid] <= key)
            left = mid + 1;
        else
        {
            right = mid - 1;
        }
    }

    return -1;
}

/* Find an index i such that A[i] < key <= A[i + 1] */
int findInfimumInd(int sortedArr[], int mSize, int key)
{
    int left, right, mid;

    /* Corner case */
    if(sortedArr[0] >= key)
        return -1;
    if(sortedArr[mSize - 1] < key)
        return mSize - 1;

    left = 0;
    right = mSize - 2;
    while(left <= right)
    {
        mid = left + ((right - left) >> 1);

        if(sortedArr[mid] < key && key <= sortedArr[mid + 1])
            return mid;

        if(sortedArr[mid] >= key)
            right = mid - 1;
        else
            left = mid + 1;
    }

    return -1;
}
