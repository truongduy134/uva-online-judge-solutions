#include <stdio.h>

#define MAX_LEN 500000

int findFirstCharInd(char str[], int startInd, char letter);
int isSubsequence(char strOne[], char strTwo[]);

int main(void)
{
    char strOne[MAX_LEN + 1], strTwo[MAX_LEN + 1];

    while(scanf("%s %s", strOne, strTwo) > 0)
    {
        if(isSubsequence(strOne, strTwo))
            printf("Yes\n");
        else
            printf("No\n");
    }

    return 0;
}

int isSubsequence(char strOne[], char strTwo[])
{
    int indOne, indTwo;

    for(indOne = 0, indTwo = -1; strOne[indOne] != '\0'; indOne++)
    {
        indTwo = findFirstCharInd(strTwo, indTwo + 1, strOne[indOne]);

        if(indTwo < 0)
            return 0;
    }

    return 1;
}

/* Return the index of the first occurence of the input
 *      character in the input string from the startInd
 *      onwards.
 *
 * Return -1 if such a character does not exist
 */
int findFirstCharInd(char str[], int startInd, char letter)
{
    int ind = startInd;

    while(str[ind] != '\0')
    {
        if(str[ind] == letter)
            return ind;

        ind++;
    }

    return -1;
}
