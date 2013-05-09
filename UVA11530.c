#include <stdio.h>

#define NUM_ALPHA 26
#define MAX_LEN 1000

const int numTimeKeyType[NUM_ALPHA] = {1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3,
                                       1, 2, 3, 4, 1, 2, 3, 1, 2, 3, 4};

int countTotalNumTimeType(char str[])
{
    int numTimeType = 0, ind;

    for(ind = 0; str[ind] != '\0'; ind++)
        if(str[ind] == ' ')
            numTimeType++;
        else
            numTimeType += numTimeKeyType[(int) (str[ind] - 'a')];

    return numTimeType;
}
int main(void)
{
    int T, caseId, numTimeType;
    char trash[MAX_LEN + 1], line[MAX_LEN + 1];

  /*  freopen("in.txt", "r", stdin); */

    scanf("%d", &T);
    gets(trash);
    caseId = 1;

    while(caseId <= T)
    {
        gets(line);

        printf("Case #%d: %d\n", caseId, countTotalNumTimeType(line));

        caseId++;
    }
    return 0;
}
