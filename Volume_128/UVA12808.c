/*******************************************************
 * Author: Nguyen Truong Duy
 *******************************************************/

/**
 * Methodology:
 * - This problem is about projectile motion.
 * - With the height H and initial horizontal speed V, we can apply projectile
 * motion formulae to find the landing position, which equals to:
 *      x = V * sqrt(2 * H / g)
 * - Having landing position x, length pool L and distance from balcony to pool
 * D, we can conclude the person falls in the EDGE, POOL or FLOOR region.
 *
 * - Gotcha: H, D, L is in mm, and V is in mm/s, but the gravitational
 * acceleration g is in m/s^2
 */

#include <stdio.h>
#include <math.h>

#define G_ACCELERATION 9810.0   /* In mm/s^2 */

double findLandingPosition(double height, double horizonSpeed) {
  return horizonSpeed * sqrt(2 * height / G_ACCELERATION);
}

int main(void) {
  int numTests, poolLength, distance, height, horizonSpeed;
  double landingPos;

  scanf("%d", &numTests);

  while (numTests) {
    scanf("%d %d %d %d", &poolLength, &distance, &height, &horizonSpeed);

    landingPos = findLandingPosition(height, horizonSpeed);
    if (landingPos < distance - 500.0 ||
        landingPos > distance + poolLength + 500.0) {
      printf("FLOOR\n");
    } else {
      if (landingPos > distance + 500.0 &&
          landingPos < distance + poolLength - 500.0) {
        printf("POOL\n");
      } else {
        printf("EDGE\n");
      }
    }

    numTests--;
  }

  return 0;
}
