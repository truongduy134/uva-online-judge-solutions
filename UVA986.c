/*******************************************************
 * Author: Nguyen Truong Duy
 *******************************************************/

/* Methodology:
 *  + We use dynamic programming to solve this problem.
 *  + The state of the problem corresponding to the value k (the height of wanted peaks) involes:
 *      - x, y: the coordinates of the current point.
 *      - r: the number of peaks allowed
 *      - d: the direction in the previous move (0 or 1, UP or DOWN)
 *  + We have x < 2 * n (n is the given input). Since at each step, we can only move up or down, and
 *      we have to finish at (2n, 0), y < n
 *
 *  + Define f(x, y, r, d) = the number of admissible paths starting from (x, y) to (2n, 0) that
 *      have eactly r peaks of height k, and the direction from the previous point to (x, y) that
 *      we choose is d (0 or 1, UP or DOWN).
 *
 *  + Recurrence relation:
 *      - At each step, we have 2 choices (go up or down)
 *      - So, f(x, y, r, d) = P(UP) + P(DOWN) where
 *          + P(UP) = f(x + 1, y + 1, r, UP) (When we decide to go up)
 *          + P(DOWN) = f(x + 1, y - 1, r - 1, DOWN) (if d = UP and y = k ).
 *            P(DOWN) = f(x + 1, y - 1, r, DOWN) otherwise
 *  + Base case:
 *      f(x, y, r, d) = 0 if r < 0 OR y < 0 OR y > n
 *      f(2n, 0, 0, d) = 1
 *      f(2n, 0, r, d) = 0 if r > 0
 *      f(2n, y, r, d) = 0 if y != 0
 */

#include <stdio.h>
#include <string.h>

const int MAX_Y = 20;
const int MAX_X = 40;
const int MAX_NUM_PEAK = 20;
const int MAX_TARGET_HEIGHT = 20;
const int NUM_DIRECTION = 2;
const int UP = 0;
const int DOWN = 1;

int countNumPath(int x, int y, int numPeak, int prevDirection, int targetHeight, int numRow, int numCol,
                 int memo[MAX_X][MAX_Y][MAX_NUM_PEAK][NUM_DIRECTION]);

int main(void)
{
    int memo[MAX_X][MAX_Y][MAX_NUM_PEAK][NUM_DIRECTION], n, numPeak, targetHeight;

    while(scanf("%d %d %d", &n, &numPeak, &targetHeight) > 0)
    {
        memset(memo, -1, MAX_X * MAX_Y * MAX_NUM_PEAK * NUM_DIRECTION * sizeof(int));

        printf("%d\n", countNumPath(0, 0, numPeak, UP, targetHeight, 2 * n, n, memo));
    }
    return 0;
}

int countNumPath(int x, int y, int numPeak, int prevDirection, int targetHeight, int maxX, int maxY,
                 int memo[MAX_X][MAX_Y][MAX_NUM_PEAK][NUM_DIRECTION])
{
    /*printf("State = (%d, %d, %d, %d, %d)\n", row, col, numPeak, prevDirection, targetHeight);*/
    if(y < 0 || y > maxY)
        return 0;
    if(numPeak < 0)
        return 0;
    if(x == maxX)
    {
        /* The largest x */
        if(y != 0 || numPeak > 0)
            return 0;
        return 1;
    }

    if(memo[x][y][numPeak][prevDirection] >= 0)
        return memo[x][y][numPeak][prevDirection];

    int numPath = 0;
    /* Try to go up */
    numPath += countNumPath(x + 1, y + 1, numPeak, UP, targetHeight, maxX, maxY, memo);
    /* Try to go down */
    int numPeakLeft = numPeak;
    if(prevDirection == UP && y == targetHeight)
        numPeakLeft--;
    numPath += countNumPath(x + 1, y - 1, numPeakLeft, DOWN, targetHeight, maxX, maxY, memo);

    memo[x][y][numPeak][prevDirection] = numPath;
    return numPath;
}
