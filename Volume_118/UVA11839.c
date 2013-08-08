#include <stdio.h>

#define MAX_BLACK_LEVEL 127
#define NUM_CHOICE 5

int determineChoice(int colorValArr[]);

int main(void)
{
    int colorValArr[NUM_CHOICE], numQuestion, i, choiceId, q;

    while(1)
    {
        scanf("%d", &numQuestion);
        if(!numQuestion)
            break;

        for(q = 0; q < numQuestion; q++)
        {
            for(i = 0; i < NUM_CHOICE; i++)
                scanf("%d", &colorValArr[i]);

            choiceId = determineChoice(colorValArr);
            if(choiceId < 0)
                printf("*\n");
            else
                printf("%c\n", choiceId + 'A');
        }
    }
    return 0;
}

int determineChoice(int colorValArr[])
{
    int i, numChosen = 0, choiceId;

    for(i = 0; i < NUM_CHOICE; i++)
        if(colorValArr[i] <= MAX_BLACK_LEVEL)
        {
            numChosen++;
            if(numChosen > 1)
                return -1;

            choiceId = i;
        }

    if(numChosen == 0)
        return -1;

    return choiceId;
}
