/*******************************************************************************
 * Author: Nguyen Truong Duy
 ********************************************************************************/

/* Methodology:
 *  + Let n be the number of points in the regular polygon.
 *  + Let A be the area of the n-sided regular polygon.
 *  + Let R and r be the radius of the outer and inner circles of the n-sided regular polygon respectively.
 *
 *  + Then R = 2 * A / (n * sin(2 * PI / n))
 *  + And r = R * cos(PI / n)
 *  + Let A1, A2 be the area of the outer and inner circles of the n-sided regular polygon respectively.
 *    Then A1 = PI * R^2 and A2 = PI * r^2
 *  + The area for spectators is A1 - A
 *  + The area for officials is A - A2
 */

#include <stdio.h>
#include <math.h>

#define PI (2 * acos(0))

double computeOuterSquareRadius(int numSide, double regularPolygonArea) {
    return 2 * regularPolygonArea / (numSide * sin(2 * PI / numSide));
}

double getOuterCircleArea(int numSide, double regularPolygonArea) {
    double squareRadius = computeOuterSquareRadius(numSide, regularPolygonArea);
    return PI * squareRadius;
}

double computeInnerSquareRadius(int numSide, double regularPolygonArea) {
    double outerSquareRadius = computeOuterSquareRadius(numSide, regularPolygonArea);
    double cosVal = cos(PI / numSide);
    return outerSquareRadius * cosVal * cosVal;
}

double getInnerCircleArea(int numSide, double regularPolygonArea) {
    return PI * computeInnerSquareRadius(numSide, regularPolygonArea);
}

int main(void) {
    int numSide, caseId;
    double polygonArea;

    caseId = 1;
    while (1) {
        scanf("%d %lf", &numSide, &polygonArea);
        if (numSide < 3) {
            break;
        }

        double outerArea = getOuterCircleArea(numSide, polygonArea);
        double innerArea = getInnerCircleArea(numSide, polygonArea);
        double spectatorArea = outerArea - polygonArea;
        double officialArea = polygonArea - innerArea;
        printf("Case %d: %.5lf %.5lf\n", caseId, spectatorArea, officialArea);

        caseId++;
    }

    return 0;
}
