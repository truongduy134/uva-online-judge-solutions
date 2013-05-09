#include <stdio.h>
#include <stdlib.h>

int main()
{
    int listPrime[] = {2, 3, 5, 7, 11, 13, 17, 19};
    int numPrime = 8, numCase, n, index;

    scanf("%d", &numCase);

    while(numCase)
    {
        scanf("%d", &n);

        for(index = numPrime - 1; index >= 0; index--)
            if(listPrime[index] < n)
            {
                printf("%d\n", listPrime[index]);
                break;
            }

        numCase--;
    }
    return 0;
}
