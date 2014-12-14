/*******************************************************
 * Author: Nguyen Truong Duy
 *******************************************************/

#include <cstdio>

/* Methodology:
 * - Let f(N) = max {gcd(i, j) | i != j and 1 <= i, j <= N}
 * - Clearly f(N) <= N / 2, or equivalently f(N) <= floor(N / 2) (*)
 * - (*) is true because f(N) * x = y <= N for some 1 <= x, y <= N.
 *   f(N) cannot be N because gcd(i, j) = N for 1 <= i, j <= N if and
 *   only if i = j = N. However, we have a condition that i != j.
 *   Since x >= 1, y <= N, f(N) < N and all of them are integers,
 *   we conclude that f(N) <= N / 2, or equivalently f(N) <= floor(N / 2)
 * - For N is even, equality happens because gcd(N, N / 2) = N / 2
 *   For N is odd, equality happens because
 *          gcd(N - 1, (N - 1) / 2) = (N - 1) / 2 = floor(N / 2)
 * - Therefore, f(N) = floor(N / 2) for all N >= 2.
 * - Time complexity: O(1)
 *
 * - Note that since N can be as large as 10^18, we should use long long
 *   or unsigned long long type.
 */

int main(void) {
  unsigned long long n, maxGcd;
  int T;

  scanf("%d", &T);
  while (T) {
    scanf("%llu", &n);
    maxGcd = n >> 1;
    printf("%llu\n", maxGcd);

    T--;
  }

  return 0;
}
