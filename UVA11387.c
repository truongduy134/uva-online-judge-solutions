#include <stdio.h>

/* Methodology:
 *     + If n is odd or n = 2, there is no way to construct a 3-regular graph (by Handshaking Theorem)
 *     + If n is even and n >= 4, we can construct the following simple 3-regular graph:
 *          + Partition a graph into two sets {1, 3, 5, ... } and {2, 4, 6, ... }
 *          + For each u = 1, 3, 5, ..., it has at most 3 edges
 *                   - (u, u + 1),
 *                   - (u, u - 1) if u > 1
 *                   - (u, u + 3).if u != n - 1
 *          + The last two edges are (1, n - 1) and (2, n)
 *          + The total number of edges in the graph is 3 * n / 2
 */
int main(void)
{
    int numV, u;

    while(1)
    {
        scanf("%d", &numV);
        if(numV == 0)
            break;

        if(numV == 2 || (numV & 1))
            printf("Impossible\n");
        else
        {
            printf("%d\n", (3 * numV) >> 1);
            for(u = 1; u <= numV; u += 2)
            {
                /* 1st edge: (u, u + 1) */
                printf("%d %d\n", u, u + 1);

                /* 2nd edge: */
                if(u > 1)
                    printf("%d %d\n", u, u - 1);

                /* 3rd edge: */
                if(u < numV - 1)
                    printf("%d %d\n", u, u + 3);
            }
            printf("%d %d\n", 1, numV - 1);
            printf("%d %d\n", 2, numV);
        }
    }
    return 0;
}


