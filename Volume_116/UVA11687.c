#include <stdio.h>
#include <string.h>

#define MAX_LEN 1000000

/* Methodology:
 *      x(i + 1) = the number of digits in the decimal representation of x(i)
 *
 * Note that: x(0) has at most 10^6 digits
 *
 * Case 1:
 *      x(0) = 1. Then x(1) = 1 = x(0). So the smallest i such that x(i) = x(i - 1) is 1
 *
 * Case 2:
 *      0 <= x(0) < 10 and x(0) != 1. Then x(1) = 1, x(2) = 1.
 *      So the smallest i such that x(i) = x(i - 1) is 2
 *
 * Case 3:
 *      x(0) has < 10 digits and > 1 digits. Then x(1) = a where 2 <= a < 10.
 *      x(2) = 1, x(3) = 1. So the smallest i such that x(i) = x(i - 1) is 3.
 *
 * Case 4:
 *      x(0) has >= 10 digits. Then x(1) = a where a >= 10 and a <= 10^6
 *      x(2) = b where 2 <= b <= 7.
 *      x(3) = 1 and x(4) = 1. So the smallest i such that x(i) = x(i - 1) is 4
 */

int main(void)
{
    char number[MAX_LEN + 1];
    int len, result;

  //  freopen("in.txt", "r", stdin);

    while(1)
    {
        gets(number);
        if(number[0] == 'E')
            break;

        len = (int) strlen(number);
        if(len == 1)
        {
            if(number[0] == '1')
                result = 1;
            else
                result = 2;
        }
        else
        {
            if(len < 10)
                result = 3;
            else
                result = 4;
        }

        printf("%d\n", result);
    }

    return 0;
}
