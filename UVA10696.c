#include <stdio.h>

#define MAX_VAL 1000001

/* Note that f91(n) > 0 for all n > 0 */
/* Recursive implementation */
int computeF91(int n, int memoF91[])
{
    if(memoF91[n])
        return memoF91[n];

    if(n > 100)
    {
        memoF91[n] = n - 10;
    }
    else
        memoF91[n] = computeF91(computeF91(n + 11, memoF91), memoF91);

    return memoF91[n];
}

/* We can prove that:
 *      f91(n) = n - 10     for n >= 101
 *      f91(n) = 91         otherwise
 */
int main(void)
{
    int n, result;
    while(1)
    {
        scanf("%d", &n);
        if(n == 0)
            break;

        result = 91;
        if(n > 100)
            result = n - 10;
        printf("f91(%d) = %d\n", n, result);
    }

    return 0;
}
