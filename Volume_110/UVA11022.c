#include <stdio.h>
#include <string.h>

#define MAX_LEN 100

/* Methodology:
 *    + Define f(i, j) = the minimum weight of the maximal factoring starting at index i
 *                       of the input string S (S[i ... j])
 *
 *    + f(i, j) = min( f(i, k) + f(g, j) ) for all k = i, ... , j
 *          where L = S[i... k] and S[i ... j] = (L)^n S[g ... j]
 *
 *    + Base case: f(end, end) = 0 and f(end - 1, end) = 1
 */

int getStartOfNewFactorInd(char str[], int s, int e, int k);
int getWeightMaximalFactoring(char str[], int start, int end, int memoTable[][MAX_LEN]);

int main(void)
{
    char inputStr[MAX_LEN + 1];
    int memoTable[MAX_LEN][MAX_LEN];

    while(1)
    {
        scanf("%s", inputStr);

        if(inputStr[0] == '*')
            break;

        memset(memoTable, -1, MAX_LEN * MAX_LEN * sizeof(int));

        printf("%d\n", getWeightMaximalFactoring(inputStr, 0, (int) strlen(inputStr) - 1,
                                                 memoTable));
    }

    return 0;
}

int getWeightMaximalFactoring(char str[], int start, int mEnd, int memoTable[][MAX_LEN])
{
    int endFactorInd, minWeight, nextInd, weight;

    if(start > mEnd)
        return 0;
    if(start == mEnd)
        return 1;

    if(memoTable[start][mEnd] >= 0)
        return memoTable[start][mEnd];

    /* Intially, the whole string is a factor */
    minWeight = mEnd - start + 1;
    for(endFactorInd = start; endFactorInd < mEnd; endFactorInd++)
    {
        nextInd = getStartOfNewFactorInd(str, start, mEnd, endFactorInd);

        weight = getWeightMaximalFactoring(str, start, endFactorInd, memoTable) +
                 getWeightMaximalFactoring(str, nextInd, mEnd, memoTable);

        if(minWeight > weight)
            minWeight = weight;
    }

    memoTable[start][mEnd] = minWeight;
    return minWeight;
}

/* str[s ... e] will be factored as ( str[s ... k] )^m str[nextK ... e] (for some m)
 * This function will return the value of nextK after trying to find as many consecutive
 *      copies of str[s ... k] as possbile.
 *
 */
int getStartOfNewFactorInd(char str[], int s, int e, int k)
{
    int len = k - s + 1, nextK = k + 1;

    while(nextK + len - 1 <= e && strncmp(&str[s], &str[nextK], len) == 0)
    {
        nextK += len;
    }

    return nextK;
}
