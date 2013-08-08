/*******************************************************
 * Author: Nguyen Truong Duy
 *******************************************************/

/* Methodology:
 *  + The area the cow can eat grass is an ellipse with the following properties:
 *      - The two foci are the two pillars. Call them F1, F2
 *        So F1F2 = 2f = D (the distance between the two pillars)
 *        So f = D / 2
 *
 *      - Let P be a point on the boundary of the ellipse
 *        The PF1 + PF2 = 2a = L (the length of the rope)
 *        So a = L / 2
 *
 *      - We have f = sqrt(a^2 - b^2). So b = sqrt(a^2 - f^2)
 *      - The area of the ellipse if PI * a * b
 *
 *      - Time complexity: O(1)
 */

#include <stdio.h>
#include <math.h>

const double PI = 2 * acos(0);

double computeEllipseArea(double a, double f);

int main(void)
{
    double D, L;
    int T;

    scanf("%d", &T);
    while(T)
    {
        scanf("%lf %lf", &D, &L);

        printf("%.3lf\n", computeEllipseArea(L / 2.0, D / 2.0));
        T--;
    }
    return 0;
}

double computeEllipseArea(double a, double f)
{
    double b = sqrt(a * a - f * f);
    return PI * a * b;
}
