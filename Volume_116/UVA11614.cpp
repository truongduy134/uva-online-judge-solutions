/*******************************************************************************
 * Author: Nguyen Truong Duy
 ********************************************************************************/

/* Methodology:
 *
 * Method 1:
 *  + Use binary search
 *  + Let T(n) = n * (n + 1) / 2 (The n-th triangle number)
 *  + Let M be the number of warriors.
 *  + Then the answer to the problem is the largest n such that T(n) <= M
 *
 *  + Note that n = 1414213562 is the smallest n such that T(n) > 10^18
 *  + Therefore, for each input M, we can binary search on [0, 1414213562] to find the answer.
 *  + Corner case: If M = 0, then the number of rows is 0 
 *
 * Method 2: Closed formula
 *  + If M = 0, then the answer is 0
 *  + Consider M >= 0
 *  + Suppose n is the number of rows that can be formed.
 *    Then we have n * (n + 1) / 2 <= M
 *          => n^2 + n - 2M <= 0
 *    We have delta = 1^2 - 4 * (-2M) = 1 + 8 * M
 *    So n <= (-1 + sqrt(1 + 8 * M)) / 2
 *    Therefore, the largest n satisfied (the largest number of rows that can be formed) is n = floor((-1 + sqrt(1 + 8 * M)) / 2)
 */

#include <cstdio>
#include <cmath>

using namespace std;

#define BOUND_NUM_ROW 1414213562L

unsigned long long computeTriangleNum(int n) {
    long long input = n;
    return (input * (input + 1)) >> 1;
}

int binarySearchNumRow(unsigned long long numPeople) {
    if (numPeople == 0) {
        return 0;
    }

    int low = 1, minLow = 0;
    int high = BOUND_NUM_ROW;

    while (low <= high) {
        int mid = low + ((high - low) >> 1);
        unsigned long long triangleNum = computeTriangleNum(mid);

        if (triangleNum == numPeople) {
            return mid;
        } else if (triangleNum > numPeople) {
            high = mid - 1;
        } else {
            if (computeTriangleNum(mid + 1) > numPeople) {
                return mid;
            }
            low = mid + 1;
        }

    }

    return -1;  // Dummy
}

/* Method 2: Closed formula
int calculateNumRow(unsigned long long numPeople) {
    if (numPeople == 0) {
        return 0;
    }

    return (int) floor((-1 + sqrt(1 + 8 * numPeople)) / 2);
}
*/

int main(void) {
    int numTest;
    unsigned long long numPeople;

    scanf("%d", &numTest);
    while(numTest) {
        scanf("%llu", &numPeople);

        printf("%d\n", binarySearchNumRow(numPeople));
        numTest--;
    }
    return 0;
}
