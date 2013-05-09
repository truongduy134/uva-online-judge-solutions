#include <stdio.h>

#define MAX_YEAR 53

/* Methodology:
 *      + Let M(n) be the number of male bees at year n.
 *      + Let F(n) be the number of female bees at year n.
 *      + Let T(n) = M(n) + F(n) be the total number of bees at year n.
 *
 *      + Recurrence relation:
 *          M(n + 1) = M(n) + F(n)
 *          F(n + 1) = M(n) + 1     (since the queen bee is immortal)
 *
 *      + Base case: M(0) = 0, F(0) = 1
 */
int main(void)
{
    unsigned int numMale[MAX_YEAR + 1], numFemale[MAX_YEAR + 1];
    int year;

    numMale[0] = 0;
    numFemale[0] = 1;

    for(year = 1; year <= MAX_YEAR; year++)
    {
        numMale[year] = numMale[year - 1] + numFemale[year - 1];
        numFemale[year] = numMale[year - 1] + 1;
    }

    while(1)
    {
        scanf("%d", &year);
        if(year < 0)
            break;

        printf("%u %u\n", numMale[year], numMale[year] + numFemale[year]);
    }

    return 0;
}
