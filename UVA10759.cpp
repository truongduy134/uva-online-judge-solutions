#include <cstdio>

using namespace std;

#define MAX_FACE_VALUE 6
#define MAX_NUM_DICE 24
#define MAX_SUM 150

unsigned long long memoTable[MAX_NUM_DICE][MAX_SUM], totalNumEvent[MAX_NUM_DICE + 1];

unsigned long long findGcd(unsigned long long a, unsigned long long b)
{
    unsigned long long r;

    while(b)
    {
        r = a % b;
        a = b;
        b = r;
    }

    return a;
}

unsigned long long computeNumSatisfyEvent(int n, int index, int x)
{
    unsigned long long result;
    if(index >= n && x > 0)
        return 0;

    if(index >= n && x <= 0)
        return 1;
    if(x <= 0)
    {
        return totalNumEvent[n - index];
    }

    if(memoTable[index][x] != (unsigned long long) (-1))
        return memoTable[index][x];

    result = 0;
    for(int faceValue = 1; faceValue <= MAX_FACE_VALUE; faceValue++)
        result += computeNumSatisfyEvent(n, index + 1, x - faceValue);

    memoTable[index][x]= result;
    return result;
}

int main(void)
{
    int n, x;
    unsigned long long numEvent, gcd, mTotalNumEvent;

    totalNumEvent[0] = 1;
    for(int i = 1; i <= MAX_NUM_DICE; i++)
        totalNumEvent[i] = totalNumEvent[i - 1] * MAX_FACE_VALUE;

 //   freopen("in.txt", "r", stdin);
 //   freopen("out.txt", "w", stdout);

    while(1)
    {
        scanf("%d %d", &n, &x);

        if(n == 0 && x == 0)
            break;

        for(int i = 0; i < n; i++)
            for(int j = 0; j <= x; j++)
                    memoTable[i][j] = (unsigned long long) (-1);

        numEvent = computeNumSatisfyEvent(n, 0, x);

        mTotalNumEvent = totalNumEvent[n];
        if(numEvent == 0)
            printf("0\n");
        else
        {
            gcd = findGcd(mTotalNumEvent, numEvent);

            mTotalNumEvent /= gcd;
            numEvent /= gcd;

            if(mTotalNumEvent == 1)
                printf("%llu\n", numEvent);
            else
                printf("%llu/%llu\n", numEvent,mTotalNumEvent);
        }
    }
}
