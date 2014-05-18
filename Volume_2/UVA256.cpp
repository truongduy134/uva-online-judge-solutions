/*******************************************************************************
 * Author: Nguyen Truong Duy
 ********************************************************************************/

/* Methodology:
 *  + Consider all squares N that have at most 8 digits
 *  + For x = 1, 2, 3, 4:
 *      + If N has more than 2 * x digits (excluding leading zeroes), then ignore it.
 *      + Otherwise, split N into 2 equal parts A and B, each has x digits (we can add leading zeros
 *          to N where possible).
 *      + If (A + B)^2 = N, then remember N as a squirksome square of 2 * x digits.
 *  + Time complexity: We only need to consider sqrt(10^9) numbers.
 */

#include <cstdio>
#include <vector>

using namespace std;

const int SQUARE_VALUE_UPPERBOUND = 100000000;

void precomputeQuirksomeSquares(vector<vector<int> > & quirksomeSquares) {
    quirksomeSquares.clear();

    for (int i = 0; i < 4; i++) {
        // only consider squares with 2, 4, 6, 8 digits
        quirksomeSquares.push_back(vector<int>());
    }

    vector<int> powerTenUpperbound;
    for (int i = 0, powerTen = 100; i < 4; ++i, powerTen *= 100) {
        powerTenUpperbound.push_back(powerTen);
    }

    int num = 0;
    int square = 0;
    while ((square = num * num) < SQUARE_VALUE_UPPERBOUND) {
        for (int i = 0, powerTen = 10; i < 4; i++, powerTen *= 10) {
            if (square >= powerTenUpperbound[i]) {
                continue;
            }

            int headPart = square / powerTen;
            int tailPart = square % powerTen;
            int sum = headPart + tailPart;
            if (sum * sum == square) {
                quirksomeSquares[i].push_back(square);
            }
        }
        num++;
    }
}

int main(void) {
    int numDigit;
    vector<vector<int> > quirksomeSquares;

    precomputeQuirksomeSquares(quirksomeSquares);

    while (scanf("%d", &numDigit) > 0) {
        int vectorIndex = (numDigit >> 1) - 1;
        for (int i = 0; i < quirksomeSquares[vectorIndex].size(); ++i) {
            switch (numDigit) {
                case 2:
                    printf("%02d\n", quirksomeSquares[vectorIndex][i]);
                    break;
                case 4:
                    printf("%04d\n", quirksomeSquares[vectorIndex][i]);
                    break;
                case 6:
                    printf("%06d\n", quirksomeSquares[vectorIndex][i]);
                    break;
                case 8:
                    printf("%08d\n", quirksomeSquares[vectorIndex][i]);
                    break;
            }
        }
    }

    return 0;
}
