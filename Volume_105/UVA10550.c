/*******************************************************
 * Author: Nguyen Truong Duy
 *******************************************************/

/**
 * Methodology:
 * - The tricky part of the problem is that we rotate the dial plate so that
 *   the desired number arrives at the "read head". Hence, the numbers are
 *   actually moving around, and not fixed like those in a clock.
 * - For example, if the next desired number in lock combination is 10, and
 *   the current number at the "read head" is 0, then the dial must turn
 *   270 degree clockwise, or 90 degree counterclockwise so that the number 10
 *   arrives at the "read head".
 *
 * - You can assume no two consecutive numbers in intial position and lock
 *   combination are the same.
 */

#include <stdio.h>

#define DEG_PER_UNIT 9  /* Total 40 units on a circle */
#define CLOCKWISE 1

int getClockwiseAngle(int from, int to) {
  if (to < from) {
    to += 40;
  }
  return (to - from) * DEG_PER_UNIT;
}

/* Compute the total number of degrees that the dial
 * must be turned to open the lock
 */
int getTotalDegDialTurned(
    int initPos,
    int fstPos,
    int sndPos,
    int thdPos) {
  int totalDeg;

  /* 2 clockwise full circles */
  totalDeg = 360 + 360;
  /* Turn dial clockwise until meeting the 1st number in combination */
  totalDeg += 360 - getClockwiseAngle(initPos, fstPos);
  /* 1 counter-clockwise full turn */
  totalDeg += 360;
  /* Turn dial counterclockwise until meeting the 2nd number */
  totalDeg += getClockwiseAngle(fstPos, sndPos);
  /* Turn dial clockwise until metting the 3rd number */
  totalDeg += 360 - getClockwiseAngle(sndPos, thdPos);

  return totalDeg;
}

int main(void) {
  int initPos, fstPos, sndPos, thdPos;

  while (1) {
    scanf("%d %d %d %d", &initPos, &fstPos, &sndPos, &thdPos);
    if (!(initPos || fstPos || sndPos || thdPos)) {
      break;
    }

    printf("%d\n", getTotalDegDialTurned(initPos, fstPos, sndPos, thdPos));
  }

  return 0;
}
