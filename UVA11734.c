#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 100

int removeSpace(char str[], char result[]);

int main(void)
{
    int T, caseId, hasSpace, len;
    char judgeStr[MAX_LEN + 2], userAns[MAX_LEN + 2],
         userNoSpaceAns[MAX_LEN + 2], trash[MAX_LEN + 2];

    scanf("%d", &T);
    fgets(trash, MAX_LEN + 2, stdin);
    caseId = 1;
    while(caseId <= T)
    {
        fgets(userAns, MAX_LEN + 2, stdin);
        len = strlen(userAns);
        if(userAns[len - 1] == '\n')
        {
            userAns[len - 1] = '\0';
            len--;
        }

        fgets(judgeStr, MAX_LEN + 2, stdin);
        len = strlen(judgeStr);
        if(judgeStr[len - 1] == '\n')
        {
            judgeStr[len - 1] = '\0';
            len--;
        }

        hasSpace = removeSpace(userAns, userNoSpaceAns);

        printf("Case %d: ", caseId);
        if(strcmp(judgeStr, userNoSpaceAns) == 0)
        {
            if(hasSpace)
                printf("Output Format Error\n");
            else
                printf("Yes\n");
        }
        else
            printf("Wrong Answer\n");
        caseId++;
    }
    return 0;
}

int removeSpace(char str[], char result[])
{
    int strInd, resultInd, hasSpace;

    hasSpace = 0;
    for(resultInd = 0, strInd = 0; str[strInd] != '\0'; strInd++)
        if(!isspace(str[strInd]))
        {
            result[resultInd] = str[strInd];
            resultInd++;
        }
        else
            hasSpace = 1;

    result[resultInd] = '\0';

    return hasSpace;
}
