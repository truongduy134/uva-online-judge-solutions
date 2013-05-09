#include <stdio.h>

#define MAX_LEN 1000000
#define SHIFT_VAL 7
int main(void)
{
    char line[MAX_LEN + 1];
    int ind;

   /* freopen("in.txt", "r", stdin); */

    while(gets(line) != NULL)
    {
        for(ind = 0; line[ind] != '\0'; ind++)
            line[ind] -= SHIFT_VAL;

        printf("%s\n", line);
    }

    return 0;
}
