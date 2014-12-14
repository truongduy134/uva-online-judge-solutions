/*******************************************************
 * Author: Nguyen Truong Duy
 *******************************************************/

/* Methodology:
 * - Straightforward problem.
 * - Gotchas:
 * 1) For each input pair i and j, it is possible that i > j.
 * 2) The length of Ackermann sequence does not include the last number 1.
 * 3) If n = 1, the sequence is actually 1 4 2 1 with length 3.
 */

#include <stdio.h>

int lengthAckermannSequence(int n);

int main(void) {
  int temp, low, high, len, maxLen, value, n;

  while (1) {
    scanf("%d %d", &low, &high);
    if (!(low || high)) {
      break;
    }
    if (low > high) {
      temp = high;
      high = low;
      low = temp;
    }

    maxLen = 0;
    for (n = low; n <= high; ++n) {
      len = lengthAckermannSequence(n);
      if (len > maxLen) {
        value = n;
        maxLen = len;
      }
    }

    printf(
      "Between %d and %d, %d generates the longest sequence of %d values.\n",
      low, high, value, maxLen);
  }

  return 0;
}

int lengthAckermannSequence(int n) {
  int count = 0;

  do {
    if (n & 1) {
      n = 3 * n + 1;
    } else {
      n >>= 1;
    }
    count++;
  } while (n > 1);

  return count;
}
