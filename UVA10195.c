#include <stdio.h>
#include <math.h>
/* Radius of the incircle of a triangle is given by the formula:
 *      r = sqrt( (s - a)(s - b)(s - c) / s ) where s = 1/2 (a + b + c)
 *        = sqrt( (1/8)(b + c - a)(a + c - b)(a + b - c) / (1/2)(a + b + c) )
 *        = sqrt( (1/4)(b + c - a)(a + c - b)(a + b - c) / (a + b + c) )
 *        = 1/2 * sqrt( (b + c - a)(a + c - b)(a + b - c) / (a + b + c) )
 */

#define EPS 0.0000000001
int main(void)
{
    double a, b, c, r;

    while(scanf("%lf %lf %lf", &a, &b, &c) > 0)
    {
        if(a < EPS || b < EPS || c < EPS)
            r = 0;
        else
            r = 0.5 * sqrt((b + c - a) * (a + c - b) * ((a + b - c) / (a + b + c)));

        printf("The radius of the round table is: %.3lf\n", r);
    }

    return 0;
}
