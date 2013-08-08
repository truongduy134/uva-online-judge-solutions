/*
 * UVA Prolem ID: 12459 (Bees' Ancestors)
 *
 * Input:
 *    + The problem consists of multiple test cases.
 *    + For each test case, there is a line containing a single integer N (indicating the generation).
 *      Note that N <= 80
 *    + The input terminates when N = 0.
 *
 * Output:
 *    + For each input case, print the corresponding number of ancestors that Willy has in
 *      such generation.
 *
 * Let f(n) = the number of female ancestors at generation n
 *     m(n) = the number of male ancestors at generation n
 *     t(n) = the number of ancestors at generation n.
 *
 * Clearly, t(n) = f(n) + m(n)
 *
 * Recurrence relation:
 *      f(n) = f(n - 1) + m(n - 1) = t(n - 1)
 *      m(n) = f(n - 1) = t(n - 2)
 *
 * Hence, t(n) = t(n - 1) + t(n - 2) = Fibo(n)
 *
 * Base case: t(1) = 1
 * We let t(0) = 1
 *
 */
#include <stdio.h>

#define MAX_LEVEL 80

void findNumAncestor();

long long int numAncestor[MAX_LEVEL + 1];

int main()
{
    int level;

    findNumAncestor();

    while(1)
    {
        scanf("%d", &level);

        if(level == 0)
            break;

        printf("%lld\n", numAncestor[level]);
    }

    return 0;
}

/* Find the number of ancestors at level n for all 1 <= n <= 80 */
void findNumAncestor()
{
    int level;

    numAncestor[0] = 1;
    numAncestor[1] = 1;

    for(level = 2; level <= MAX_LEVEL; level++)
    {
        numAncestor[level] = numAncestor[level - 1] + numAncestor[level - 2];
    }
}
