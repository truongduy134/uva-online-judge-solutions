#include <stdio.h>

unsigned int findMinNumTransform(unsigned int target);

#define MAX_SIZE_MEMO 800000
unsigned int memoTable[MAX_SIZE_MEMO] = {0};

int main(void)
{
    unsigned int target;

    while(scanf("%u", &target) > 0)
    {
        printf("%u\n", findMinNumTransform(target));
    }

    return 0;
}

/* Let findMinNumTransform(N) = f(N) = the minimum steps to transform
 *              0 to N where allowed operations in each step are:
 *                  + Decrement
 *                  + Increment
 *                  + Double
 * f(0) = 0
 * f(1) = 1
 * f(N) = 1 + f(N / 2) if N is even
 * f(N) = 1 + min { f(N  + 1), f(N - 1) } if N is odd
 */
unsigned int findMinNumTransform(unsigned int target)
{
    if(target == 0)
        return 0;
    if(target == 1)
        return 1;

    if(target < MAX_SIZE_MEMO && memoTable[target] > 0)
        return memoTable[target];

    unsigned int decVal, incVal, result;

    if(target & 1)
    {
        /* target is odd */
        decVal = findMinNumTransform(target - 1);
        incVal = findMinNumTransform(target + 1);

        if(decVal < incVal)
            result = 1 + decVal;
        else
            result = 1 + incVal;
    }
    else
        /* target is even */
        result = 1 + findMinNumTransform(target >> 1);

    if(target < MAX_SIZE_MEMO)
        memoTable[target] = result;

    return result;
}
