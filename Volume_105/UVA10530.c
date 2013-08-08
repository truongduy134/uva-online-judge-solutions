#include <stdio.h>
#include <string.h>

#define HIGH "high"
#define RIGHT "right"

#define MAX_LEN 500
#define LOWER 1
#define UPPER 10

int main(void)
{
    int left, right, guess, ans;
    char hint[MAX_LEN + 1], trash[MAX_LEN + 1];

    while(1)
    {
        scanf("%d", &guess);
        gets(trash);
        if(guess == 0)
            break;

        left = LOWER;
        right = UPPER;

        while(1)
        {
            gets(hint);
            if(strstr(hint, RIGHT) != NULL)
            {
                ans = guess;
                break;
            }

            if(strstr(hint, HIGH) != NULL)
            {
                if(guess <= right)
                    right = guess - 1;
            }
            else
            {
                if(guess >= left)
                    left = guess + 1;
            }
            scanf("%d", &guess);
            gets(trash);
        }

        if(left < LOWER || right > UPPER || ans < left || ans > right)
            printf("Stan is dishonest\n");
        else
            printf("Stan may be honest\n");
    }
    return 0;
}
