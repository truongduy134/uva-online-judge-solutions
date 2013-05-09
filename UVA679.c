#include <stdio.h>
#include <string.h>

#define MAX_DEPTH 20
#define MAX_BALL 524288

/* Methodology:
 *      - Assumption: k <= 2^d - 1
 *      - Let f(d, k) = the destination leaf when dropping the k-th ball at the fully binary tree of depth d.
 *      - Then we have the recurrence relation:
 *          + When d = 1: f(1, k) = 1
 *          + If k is odd:  f(d, k) = 2^(d - 2) + f(d - 1, floor(k / 2) + 1)
 *          + If k is even: f(d, k) = f(d - 1, k / 2) + 2 ^ (d - 1)
 *
 * How to come up with the recurrence relation?
 *      Observation: Let T(d) be the fully binary tree of depth d.
 *                   Then the left subtree at the root of T(d) is T(d - 1)
 *                   For odd k, the ball will go to the left subtree. Moreover, the final position of dropping
 * the k-th ball on T(d) is the same as the final position of dropping the (k / 2 + 1)-th ball on T(d - 1).
 *                   Similar to the case k is even (where the final position is in the right subtree)
 *
 *  And to arrive that the final solution, we need to convert the final position at T(d - 1) to the corresponding
 *      position at T(d) depending on the ball falls in the left or right subtree.
 */
int findDestination(int depth, int ballId);

int memoTable[MAX_DEPTH + 1][MAX_BALL + 1];

int main(void)
{
    int depth, T, ballId, numBall;

    memset(memoTable, -1, (MAX_DEPTH + 1) * (MAX_BALL + 1) * sizeof(int));

    scanf("%d", &T);
    while(T)
    {
        scanf("%d %d", &depth, &ballId);

        numBall = (1 << depth) - 1;
        if(ballId > numBall)
            ballId = ballId % numBall;
        if(ballId == 0)
            ballId = numBall;

        if(memoTable[depth][ballId] >= 0)
            printf("%d\n", memoTable[depth][ballId]);
        else
            printf("%d\n", findDestination(depth, ballId));

        T--;
    }
    return 0;
}

int findDestination(int depth, int ballId)
{
    int result;

    if(depth == 1)
        return 1;

    if(memoTable[depth][ballId] >= 0)
        return memoTable[depth][ballId];

    if(ballId & 1)
        result = findDestination(depth - 1, (ballId >> 1) + 1) + (1 << (depth - 2));
    else
        result = findDestination(depth - 1, ballId >> 1) + (1 << (depth - 1));

    memoTable[depth][ballId] = result;

    return result;
}
