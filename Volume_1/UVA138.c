/*******************************************************************************
 * Author: Nguyen Truong Duy
 ********************************************************************************/

/* Methodology:
 *  + Let n be the number of houses (n >= 2), and x be the house id.
 *  + We have the equation: 1 + 2 + ... + x - 1 = x + 1 + ... + n
 *  + Simplifying the above equation, we have (n^2 + n) / 2 = x^2
 *  + We search from n = 2 until we find enough 10 solutions. For each n, compute
 *        (n^2 + n) / 2, and if it is square, then we find 1 solution.
 */

#include <stdio.h>
#include <math.h>

#define NUM_TO_FOUND 10

int main(void) {
    int numHouse = 2;
    int numFound = 0;

    while (numFound < NUM_TO_FOUND) {
        long long triangleNum = ((long long) numHouse * (numHouse + 1)) >> 1;

        long long squareRoot = (long long) floor(sqrt(triangleNum));
        if (squareRoot * squareRoot == triangleNum) {
            int houseId = squareRoot;
            printf("%10d%10d\n", houseId, numHouse);
            numFound++;
        }

        numHouse++;
    }

    return 0;
}
