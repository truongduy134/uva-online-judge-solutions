#include <stdio.h>
#include <stdlib.h>

int main()
{
    int numTest, first, second;

    scanf("%d", &numTest);

    while(numTest)
    {
        scanf("%d %d", &first, &second);

        if(first < second)
            printf("<\n");
        else
        {
            if(first > second)
                printf(">\n");
            else
                printf("=\n");
        }
        numTest--;
    }

    return 0;
}
