#include <stdio.h>

int main(void)
{
    int nKindHat, nKindShirt, nKindPant, nKindSock, nKindShoe;

    while(1)
    {
        scanf("%d %d %d %d %d", &nKindHat, &nKindShirt, &nKindPant, &nKindSock,
                                &nKindShoe);

        if(!(nKindHat || nKindShirt || nKindPant || nKindSock || nKindShoe))
            break;

        printf("%d\n", nKindHat * nKindShirt * nKindPant * nKindSock *
                       nKindSock * nKindShoe * nKindShoe);
    }

    return 0;
}
