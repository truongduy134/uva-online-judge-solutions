#include <stdio.h>
#include <string.h>

#define NUM_KIND_DIGIT 10
#define MAX_SIZE 5001

int haveDistinctDigit(int n)
{
    int digitFlag[NUM_KIND_DIGIT] = {0}, digit;

    if(n < 10)
        return 1;

    while(n)
    {
        digit = n % 10;
        if(digitFlag[digit])
            return 0;

        digitFlag[digit] = 1;
        n /= 10;
    }

    return 1;
}

void preprocess(int accumulateNumDistinctInt[])
{
    int n;

    memset(accumulateNumDistinctInt, 0, MAX_SIZE * sizeof(int));

    for(n = 0; n < MAX_SIZE; n++)
        if(haveDistinctDigit(n))
            accumulateNumDistinctInt[n] = 1;

    for(n = 1; n < MAX_SIZE; n++)
        accumulateNumDistinctInt[n] += accumulateNumDistinctInt[n - 1];
}

int main(void)
{
    int N, M, accumulateNumDistinctInt[MAX_SIZE];

    preprocess(accumulateNumDistinctInt);

    while(scanf("%d %d", &N, &M) > 0)
    {
        printf("%d\n", accumulateNumDistinctInt[M] - accumulateNumDistinctInt[N - 1]);
    }

    return 0;
}
