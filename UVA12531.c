#include <stdio.h>
#include <stdlib.h>

int main()
{
    int angle;

    while(scanf("%d", &angle) > 0)
    {
        if(angle % 6 == 0)
            printf("Y\n");
        else
            printf("N\n");
    }
    return 0;
}
