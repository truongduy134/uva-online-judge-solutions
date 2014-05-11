/*******************************************************
 * Author: Nguyen Truong Duy
 *******************************************************/

/* Methodology:
 *  + Observation: If a number is square in base T, its decimal value is also a square in base 10
 *  + Note that all inputs (corresponding to the wanted base) has decimal value less than 10^9.
 *
 *  + Populate all square numbers less than 10^9 in base 10. Let S be such a set.
 *  + For each input number n, find the minimum base X than n is valid (For example, if n = 61, it is a valid number in base 7 or larger)
 *  + For each base B from X to 99, calculate the decimal value D of n in base B. If D is in S, return B
 */

#include <cstdio>
#include <set>

using namespace std;

#define MAX_STRING_LEN 100
#define MAX_VALUE 1000000000L
#define MAX_BASE 100

int getDecimalValue(const char * numStr, int fromBase) {
    // Return -1 if the final value larger than or equal to MAX_VALUE

    long long decimal = 0;
    for (int i = 0; numStr[i] != '\0'; i++) {
        decimal *= fromBase;
        decimal += (numStr[i] - '0');

        if (decimal >= MAX_VALUE) {
            return -1;
        }
    }

    return (int) decimal;
}

int findMinBaseToBeValid(const char * numStr) {
    // Assume numStr contains digit characters only

    int maxDigit = numStr[0] - '0';

    for (int i = 1; numStr[i] != '\0'; i++) {
        int digit = numStr[i] - '0';
        if (digit > maxDigit) {
            maxDigit = digit;
        }

        if (maxDigit == 9) {
            break;
        }
    }

    return maxDigit + 1;
}

int findMinBaseToBeSquare(const char * numStr, const set<int> & squareSet) {
    // Assume such a base exists and less than MAX_BASe

    for (int base = findMinBaseToBeValid(numStr); base < MAX_BASE; base++) {
        int decimal = getDecimalValue(numStr, base);
        if (decimal < 0) {
            break;
        }

        if (squareSet.find(decimal) != squareSet.end()) {
            return base;
        }
    }

    return -1;  // Dummy
}

void precalculateSquares(set<int> & squareSet) {
    int i = 0;
    int square;

    while ((square = i * i) < MAX_VALUE) {
        squareSet.insert(square);
        i++;
    }
}

int main(void) {
    char numStr[MAX_STRING_LEN + 1];

    set<int> squareSet;

    precalculateSquares(squareSet);

    while(1) {
        scanf("%s", numStr);
        if (numStr[0] == '0' && numStr[1] == '\0') {
            break;
        }

        printf("%d\n", findMinBaseToBeSquare(numStr, squareSet));
    }

    return 0;
}