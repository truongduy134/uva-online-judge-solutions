#include <stdio.h>
#include <stdlib.h>

/*
 * Find two non-negative integers x and y such that
 *      x + y = S >= 0
 *      x - y = D >= 0
 *
 */
int main()
{
    /* larger = x, smaller = y */
    long long int sum, absDiff, larger, smaller, numCase;
    int flagPossible;

    scanf("%lld", &numCase);

    while(numCase)
    {
        /* Reset */
        flagPossible = 1;

        scanf("%lld %lld", &sum, &absDiff);

        if(sum < absDiff)
            flagPossible = 0;
        else
        {
            larger = sum + absDiff;  /* 2 * x */
            if(larger & 1 == 1)           /* sum + absDiff is odd */
            {
                flagPossible = 0;
            }
            else
            {
                larger >>= 1;
                smaller = larger - absDiff;
            }
        }

        if(flagPossible)
            printf("%lld %lld\n", larger, smaller);
        else
            printf("impossible\n");

        numCase--;
    }
    return 0;
}
