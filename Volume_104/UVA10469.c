#include <stdio.h>
#include <stdlib.h>

int main()
{
    unsigned long int a, b;

    while(scanf("%lu %lu", &a, &b) > 0)
    {
        printf("%lu\n", a ^ b);
    }
    return 0;
}
