/*******************************************************
 * Author: Nguyen Truong Duy
 *******************************************************/

/* Methodology:
 *  + This is a variant of 0-1 Knapsack problem. We can use Dynamic Programming to solve
 *    this problem.
 *  + Define f(i, L) = the maximum number of boxes that can be stacked up using
 *          boxes from i to N - 1 (N is the total number of boxes) and the maximum
 *          load of the base is L.
 *  + Recurrence relation:
 *      * If w[i] (weight of box i) > L, f(i, L) = f(i + 1, L)
 *      * Otherwise, f(i, L) = max (f(i, L), 1 + f(i + 1, min(L - w[i], M[i])) (M[i] is
 *          the maximum load of box i)
 *  + Base case:
 *      * f(N, L) = 0
 *      * f(i, L) = 0 if L < 0
 *  + At the beginning, we call the function f(0, INFINITY)
 *
 * IMPORTANT NOTE: You should use 2-byte integer (type short) for the result (since
 *  there are at most 1000 items). Attempt to use int may result in Runtime Error
 *  or Memory Limit Exceeded on UVA online judge.
 */

#include <stdio.h>
#include <string.h>

const int MAX_WEIGHT = 3000;
const int MAX_NUM_BOX = 1000;

int findMin(int a, int b);
short findMaxNumBoxStackUp(int itemInd, int maxLoad, int isFirst, int weightArr[], int maxLoadArr[], int numBox,
                         short memoTable[][MAX_WEIGHT + 1]);

int main(void)
{
    int weight[MAX_NUM_BOX], maxLoad[MAX_NUM_BOX], numBox;
    short memoTable[MAX_NUM_BOX][MAX_WEIGHT + 1], i;

    while(1)
    {
        scanf("%d", &numBox);
        if(!numBox)
            break;

        memset(memoTable, -1, MAX_NUM_BOX * (MAX_WEIGHT + 1) * sizeof(short));

        for(i = 0; i < numBox; i++)
            scanf("%d %d", &weight[i], &maxLoad[i]);

        printf("%d\n", findMaxNumBoxStackUp(0, MAX_WEIGHT, 1, weight, maxLoad, numBox, memoTable));
    }

    return 0;
}

short findMaxNumBoxStackUp(int itemInd, int maxLoad, int isFirst, int weightArr[], int maxLoadArr[], int numBox,
                         short memoTable[][MAX_WEIGHT + 1])
{
    if(itemInd == numBox)
        return 0;
    if(maxLoad < 0)
        return 0;
    if(memoTable[itemInd][maxLoad] >= 0)
        return memoTable[itemInd][maxLoad];

    /* Not choose this item for stacking up */
    short maxStackUp = findMaxNumBoxStackUp(itemInd + 1, maxLoad, isFirst, weightArr, maxLoadArr, numBox, memoTable);

    /* Choose */
    if(maxLoad >= weightArr[itemInd])
    {
        int newMaxLoad = maxLoadArr[itemInd];
        if(!isFirst)
            newMaxLoad = findMin(maxLoad - weightArr[itemInd], maxLoadArr[itemInd]);
        else
            isFirst = 0;

        short numStackUp = 1 + findMaxNumBoxStackUp(itemInd + 1, newMaxLoad, isFirst, weightArr, maxLoadArr, numBox, memoTable);
        if(numStackUp > maxStackUp)
            maxStackUp = numStackUp;
    }

    memoTable[itemInd][maxLoad] = maxStackUp;
    return maxStackUp;
}

int findMin(int a, int b)
{
    if(a < b)
        return a;
    return b;
}
