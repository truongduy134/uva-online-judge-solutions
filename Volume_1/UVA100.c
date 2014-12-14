/*******************************************************
 * Author: Nguyen Truong Duy
 *******************************************************/

/* Methodology:
 * - Straightforward problem.
 * - Gotchas:
 * 1) For each input pair i and j, it is possible that i > j. However, when
 *    printing the output, i and j should appear in the order they are provided.
 * 2) Follow step-by-step the provided algorithm in the problem description.
 */

#include <stdio.h>

int cycleLength(int n);

int main(void) {
  int i, j, low, high, len, maxLen, n;

  while (scanf("%d %d", &i, &j) > 0) {
    if (i > j) {
      high = i;
      low = j;
    } else {
      high = j;
      low = i;
    }

    maxLen = 0;
    for (n = low; n <= high; ++n) {
      len = cycleLength(n);
      if (len > maxLen) {
        maxLen = len;
      }
    }

    printf("%d %d %d\n", i, j, maxLen);
  }

  return 0;
}

int cycleLength(int n) {
  int count = 1;

  while (n > 1) {
    if (n & 1) {
      n = 3 * n + 1;
    } else {
      n >>= 1;
    }
    count++;
  }

  return count;
}
