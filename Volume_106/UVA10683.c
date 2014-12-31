/*******************************************************
 * Author: Nguyen Truong Duy
 *******************************************************/

/* Methodology:
 * - In traditional system, a day has A = 24 * 60 * 60 * 100 cc (where
 *   cc denotes one-hundred of second).
 * - In decimal system, a day has B = 10 * 100 * 100 * 100 cc.
 * - From an input string of time in traditional system, we calculate the
 *   number of cc for that time, called T.
 * - Then the number of cc of the same time in decimal system is
 *      U = T * A / B
 * - From B, we can find the values of h, m, s, cc in the decimal system.
 *   In particular, cc = U % 100, s = (U / 100) % 100, and
 *   m = ((U / 100) / 100) % 100, h = ((U / 100) / 100) / 100
 *
 * - Time complexity: O(1)
 */

#include <stdio.h>

#define STR_SIZE 8
#define TO_DECIMAL(a, b) (((a) - '0') * 10 + (b) - '0')

const int NUM_CC_TRADITION = 24 * 60 * 60 * 100;
const int NUM_CC_DECIMAL = 10 * 100 * 100 * 100;
double CC_DECIMAL_TRADITION_RATIO;

struct TimeRecord {
  int h, m, s, c;
};

void getTraditionTime(char timeStr[], struct TimeRecord* timeStruct) {
  timeStruct->h = TO_DECIMAL(timeStr[0], timeStr[1]);
  timeStruct->m = TO_DECIMAL(timeStr[2], timeStr[3]);
  timeStruct->s = TO_DECIMAL(timeStr[4], timeStr[5]);
  timeStruct->c = TO_DECIMAL(timeStr[6], timeStr[7]);
}

void getDecimalTime(char timeStr[], struct TimeRecord* decTime) {
  struct TimeRecord traditionTime;
  getTraditionTime(timeStr, &traditionTime);

  int traditionCC = (((traditionTime.h * 60) + traditionTime.m) * 60 +
                    traditionTime.s) * 100 + traditionTime.c;
  int decimalCC = traditionCC * CC_DECIMAL_TRADITION_RATIO;

  decTime->c = decimalCC % 100;
  decimalCC /= 100;
  decTime->s = decimalCC % 100;
  decimalCC /= 100;
  decTime->m = decimalCC % 100;
  decTime->h = decimalCC / 100;
}

int main(void) {
  char timeStr[STR_SIZE + 1];
  struct TimeRecord decTime;

  CC_DECIMAL_TRADITION_RATIO = NUM_CC_DECIMAL * 1.0 / NUM_CC_TRADITION;
  while (scanf("%s", timeStr) > 0) {
    getDecimalTime(timeStr, &decTime);
    printf("%d%02d%02d%02d\n", decTime.h, decTime.m, decTime.s, decTime.c);
  }

  return 0;
}
