#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 2000
#define END_CHAR '*'

int isTautogram(char poem[]);

int main(void)
{
    char poem[MAX_LEN + 1];

    while(1)
    {
        if(gets(poem) == NULL)
            break;
        if(poem[0] == END_CHAR)
            break;

        if(isTautogram(poem))
            printf("Y\n");
        else
            printf("N\n");

    }

    return 0;
}

int isTautogram(char poem[])
{
    char *word, delim[] = " ", firstWordChar;

    word = strtok(poem, delim);
    if(word == NULL)
        return 1;

    firstWordChar = tolower(word[0]);

    while(1)
    {
        word = strtok(NULL, delim);
        if(word == NULL)
            break;

        if(tolower(word[0]) != firstWordChar)
            return 0;
    }

    return 1;
}
