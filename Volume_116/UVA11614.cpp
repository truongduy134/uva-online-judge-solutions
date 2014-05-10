/*******************************************************************************
 * Author: Nguyen Truong Duy
 ********************************************************************************/

/* Methodology:
 *  + Use binary search
 *  + Let T(n) = n * (n + 1) / 2 (The n-th triangle number)
 *  + Let M be the number of warriors.
 *  + Then the answer to the problem is the smallest n such that T(n) > M
 *
 *  + Note that n = 1414213562 is the smallest n such that T(n) > 10^18
 *  + Therefore, for each input M, we can binary search on [0, 1414213562] to find the answer.
 *  + Corner case: If n = 0, then the number of rows is 0 
 */

#include <cstdio>

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
