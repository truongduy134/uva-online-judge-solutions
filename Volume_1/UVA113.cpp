/*******************************************************
 * Author: Nguyen Truong Duy
 *******************************************************/

/* Methodology:
 * - 1 <= p < 10^101 is actually in the value range of double type
 * - Because k^n = p, k = p^(1 / n)
 * - Use double type for all calculations. And do not cast the results to int
 *   type when printing the ouputs (since casting introduces more round-off
 *   errors). Instead, use "%.0lf" when printing outputs.
 */

#include <cstdio>
#include <cmath>

int main(void) {
  double p;
  int n;

  while (scanf("%d %lf", &n, &p) > 0) {
    printf("%.0lf\n", pow(p, 1.0 / n));
  }

  return 0;
}
