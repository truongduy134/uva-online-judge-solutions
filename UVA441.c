#include <stdio.h>

#define MAX_SIZE 15

int main(void)
{
    int mSet[MAX_SIZE], numEle, isFirst, i, i1, i2, i3, i4, i5, i6;

    isFirst = 1;
    while(1)
    {
        scanf("%d", &numEle);
        if(!numEle)
            break;

        for(i = 0; i < numEle; i++)
            scanf("%d", &mSet[i]);

        if(isFirst)
            isFirst = 0;
        else
            printf("\n");

        /* Print all the 6-element subsets */
        for(i1 = 0; i1 < numEle; i1++)
            for(i2 = i1 + 1; i2 < numEle; i2++)
                for(i3 = i2 + 1; i3 < numEle; i3++)
                    for(i4 = i3 + 1; i4 < numEle; i4++)
                        for(i5 = i4 + 1; i5 < numEle; i5++)
                            for(i6 = i5 + 1; i6 < numEle; i6++)
                            {
                                printf("%d %d %d %d %d %d\n", mSet[i1], mSet[i2], mSet[i3],
                                       mSet[i4], mSet[i5], mSet[i6]);
                            }
    }
    return 0;
}
