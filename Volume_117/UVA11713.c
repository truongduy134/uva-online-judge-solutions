#include <stdio.h>
#include <string.h>

#define MAX_LEN 100

int isCompatible(char nameOne[], char nameTwo[]);
int isVowel(char c);

int main(void)
{
    char nameOne[MAX_LEN + 1], nameTwo[MAX_LEN + 1];
    int T;

    scanf("%d", &T);
    while(T)
    {
        scanf("%s %s", nameOne, nameTwo);

        if(isCompatible(nameOne, nameTwo))
            printf("Yes\n");
        else
            printf("No\n");

        T--;
    }
    return 0;
}

int isCompatible(char nameOne[], char nameTwo[])
{
    int lenOne = strlen(nameOne), lenTwo = strlen(nameTwo), i;

    if(lenOne != lenTwo)
        return 0;

    for(i = 0; i < lenOne; i++)
    {
        if(!isVowel(nameOne[i]) && !isVowel(nameTwo[i]))
        {
            if(nameOne[i] != nameTwo[i])
                return 0;
        }
        else
        {
            if(!(isVowel(nameOne[i]) && isVowel(nameTwo[i])))
                return 0;
        }
    }

    return 1;
}

int isVowel(char c)
{
    if(c == 'a' || c == 'e' || c == 'i' || c == 'u' || c == 'o')
        return 1;
    return 0;
}
