#include <stdio.h>

#define MAX_LEN 30

int getDecimalVal(char binary[])
{
    int decimal = 0, i;

    for(i = 0; binary[i] != '\0'; i++)
        decimal = (decimal << 1) + (binary[i] - '0');

    return decimal;
}

int findGcd(int a, int b)
{
    int r;

    while(b)
    {
        r = a % b;
        a = b;
        b = r;
    }

    return a;
}

int main(void)
{
    int T, caseId, valA, valB;
    char binary[MAX_LEN + 1], trash[MAX_LEN + 1];

    scanf("%d", &T);
    gets(trash);

    caseId = 1;
    while(caseId <= T)
    {
        scanf("%s", binary);
        valA = getDecimalVal(binary);
        scanf("%s", binary);
        valB = getDecimalVal(binary);

        if(findGcd(valA, valB) > 1)
            printf("Pair #%d: All you need is love!\n", caseId);
        else
            printf("Pair #%d: Love is not all you need!\n", caseId);

        caseId++;
    }

    return 0;
}
