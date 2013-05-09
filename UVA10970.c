#include <stdio.h>

#define min(A, B) ((A < B) ? A : B)

int main(void)
{
    int m, n, numA, numB;

    while(scanf("%d %d", &m, &n) > 0)
    {
        numA = m - 1 + m * (n - 1);
        numB = n - 1 + n * (m - 1);
        printf("%d\n", min(numA, numB));
    }
    return 0;
}