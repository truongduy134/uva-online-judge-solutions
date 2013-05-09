#include <stdio.h>

#define MAX_LEN 500

void removeDigitFromStr(char str[], char digit, char result[]);

int main(void)
{
    char digit[MAX_LEN + 1], str[MAX_LEN + 1], result[MAX_LEN + 1];

    while(1)
    {
        scanf("%s %s", digit, str);
        if(digit[0] == '0' && str[0] == '0' && str[1] == '\0')
            break;

        removeDigitFromStr(str, digit[0], result);

        printf("%s\n", result);
    }

    return 0;
}

void removeDigitFromStr(char str[], char digit, char result[])
{
    int indStr, indResult;

    for(indStr = 0, indResult = 0; str[indStr] != '\0'; indStr++)
    {
        if(str[indStr] == digit)
            continue;
        if(str[indStr] == '0' && indResult == 0)
        {
            /* Do not want leading zeroes */
            continue;
        }

        result[indResult] = str[indStr];
        indResult++;
    }

    if(indResult == 0)
    {
        result[indResult] = '0';
        indResult++;
    }

    result[indResult] = '\0';
}
