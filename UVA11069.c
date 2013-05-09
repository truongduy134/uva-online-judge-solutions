#include <stdio.h>

#define MAX_SIZE 76

/* Methodology:
 *      + f(n) = the number of subsets of [1 ... n] satisfying the requirements.
 *      + Then f(n) = f(n - 2) + f(n - 3)
 *      + Base case:
 *              f(0) = 1    // Empty set is counted here
 *              f(1) = 1
 *              f(2) = 2
 */
int main(void)
{
    int n, numSubset[MAX_SIZE + 1];

    numSubset[0] = 1;
    numSubset[1] = 1;
    numSubset[2] = 2;

    for(n = 3; n <= MAX_SIZE; n++)
        numSubset[n] = numSubset[n - 2] + numSubset[n - 3];

    while(scanf("%d", &n) > 0)
    {
        printf("%d\n", numSubset[n]);
    }

    return 0;
}
