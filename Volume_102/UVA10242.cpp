/*******************************************************
 * Author: Nguyen Truong Duy
 *******************************************************/

/* Methodology:
 *  + Let the parallelogram be ABCD
 *  + We are given end points of the edges AB and BC. We are asked to find the coordinates of D.
 *
 *  + First, we must determine point B (We cannot assume the points are given in the order A, B, B, C)
 *  + Let the center of the parallelogram be O.
 *    Then O is the midpoint of AC and BD.
 *  + From A and C, we compute O.
 *  + Then, from O and B, we compute D.
 */

#include <cstdio>
#include <cmath>

struct Point {
    double x, y;
};

const double EPS = 0.000000001;

Point getMidPoint(const Point & A, const Point & B)
{
    Point mid;
    mid.x = (A.x + B.x) / 2.0;
    mid.y = (A.y + B.y) / 2.0;

    return mid;
}

Point getPointFromMid(const Point & A, const Point & mid)
{
    Point B;
    B.x = 2 * mid.x - A.x;
    B.y = 2 * mid.y - A.y;

    return B;
}

bool areTheSame(const Point & A, const Point & B)
{
    if(fabs(A.x - B.x) < EPS && fabs(B.y - A.y) < EPS)
        return true;
    return false;
}
int main(void)
{
    Point S1, S2, S3, S4, A, B, C;

    while(scanf("%lf %lf %lf %lf %lf %lf %lf %lf", &S1.x, &S1.y, &S2.x, &S2.y, &S3.x, &S3.y,
                &S4.x, &S4.y) > 0)
    {
        if(areTheSame(S1, S3))
        {
            B = S3;
            A = S2;
            C = S4;
        }

        if(areTheSame(S1, S4))
        {
            B = S4;
            A = S2;
            C = S3;
        }

        if(areTheSame(S2, S3))
        {
            B = S2;
            A = S1;
            C = S4;
        }

        if(areTheSame(S2, S4))
        {
            B = S2;
            A = S1;
            C = S3;
        }

        Point D = getPointFromMid(B, getMidPoint(A, C));

        printf("%.3lf %.3lf\n", D.x, D.y);
    }
    return 0;
}


