#include <stdio.h>

#define NUM_MONTH 12

int main(void)
{
    int numProblemRequired[NUM_MONTH], numProblemProduced[NUM_MONTH], numProblemAvail[NUM_MONTH],
        caseId, i;

    caseId = 1;
    while(1)
    {
        scanf("%d", &numProblemAvail[0]);
        if(numProblemAvail[0] < 0)
            break;

        for(i = 0; i < NUM_MONTH; i++)
            scanf("%d", &numProblemProduced[i]);

        for(i = 0; i < NUM_MONTH; i++)
            scanf("%d", &numProblemRequired[i]);

        printf("Case %d:\n", caseId);
        for(i = 0; i < NUM_MONTH; i++)
        {
            if(i)
                numProblemAvail[i] = numProblemAvail[i - 1] + numProblemProduced[i - 1];
            if(numProblemAvail[i] < numProblemRequired[i])
                printf("No problem. :(\n");
            else
            {
                printf("No problem! :D\n");
                numProblemAvail[i] -= numProblemRequired[i];
            }
        }
        caseId++;
    }
    return 0;
}
