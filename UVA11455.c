#include <stdio.h>

#define NUM_EDGE 4

int isSquare(unsigned int edges[]);
int isRectangle(unsigned int edges[]);
int isQuadrangle(unsigned int edges[]);

int main(void)
{
    unsigned int edges[NUM_EDGE];
    int T, i;

    scanf("%d", &T);
    while(T)
    {
        for(i = 0; i < NUM_EDGE; i++)
            scanf("%d", &edges[i]);

        if(isSquare(edges))
            printf("square\n");
        else
        {
            if(isRectangle(edges))
                printf("rectangle\n");
            else
            {
                if(isQuadrangle(edges))
                    printf("quadrangle\n");
                else
                    printf("banana\n");
            }
        }
        T--;
    }
    return 0;
}

int isSquare(unsigned int edges[])
{
    int i;

    for(i = 1; i < NUM_EDGE; i++)
        if(edges[i] != edges[0])
            return 0;
    return 1;
}

int isRectangle(unsigned int edges[])
{
    if(edges[0] == edges[1] && edges[2] == edges[3])
        return 1;
    if(edges[0] == edges[2] && edges[1] == edges[3])
        return 1;
    if(edges[0] == edges[3] && edges[1] == edges[2])
        return 1;
    return 0;
}

int isQuadrangle(unsigned int edges[])
{
    if(edges[0] + edges[1] + edges[2] <= edges[3])
        return 0;
    if(edges[0] + edges[1] + edges[3] <= edges[2])
        return 0;
    if(edges[0] + edges[2] + edges[3] <= edges[1])
        return 0;
    if(edges[1] + edges[2] + edges[3] <= edges[0])
        return 0;
    return 1;
}
