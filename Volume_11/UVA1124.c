/*******************************************************
 * Author: Nguyen Truong Duy
 *******************************************************/

/* Methodology:
 *  + This is a trivial problem.
 *  + The simplest equation is the equation itself of the form <symbol> = <value>
 *  + Thus, we just need to print out what we have read.
 */

#include <stdio.h>

const int MAX_LEN_LINE = 100000;

int main(void)
{
    char line[MAX_LEN_LINE + 1];

    while(gets(line) != NULL)
    {
        printf("%s\n", line);
    }
    return 0;
}
