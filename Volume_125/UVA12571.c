#include <stdio.h>

#define MAX_SIZE_SET 100000
#define MAX_VAL 230

int getMaxAndBitwise(int arr[], int N, int a);

int main(void)
{
    int T, N, Q, arr[MAX_SIZE_SET], memoArr[MAX_VAL], i, q, queryInput;

    scanf("%d", &T);
    while(T)
    {
        scanf("%d %d", &N, &Q);

        for(i = 0; i < N; i++)
            scanf("%d", &arr[i]);
        for(i = 0; i < MAX_VAL; i++)
            memoArr[i] = -1;

        for(q = 0; q < Q; q++)
        {
            scanf("%d", &queryInput);
            if(memoArr[queryInput] < 0)
            {
                memoArr[queryInput] = getMaxAndBitwise(arr, N, queryInput);
            }

            printf("%d\n", memoArr[queryInput]);
        }
        T--;
    }

    return 0;
}

int getMaxAndBitwise(int arr[], int N, int a)
{
    int maxVal = arr[0] & a, i;

    for(i = 1; i < N; i++)
        if((arr[i] & a) > maxVal)
            maxVal = arr[i] & a;

    return maxVal;
}
