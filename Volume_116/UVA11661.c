/*******************************************************
 * Author: Nguyen Truong Duy
 *******************************************************/

/* Methodology:
 * - It is assumed that there are always at least 1 restaurant and 1 drugstore.
 * - If there is a 'Z', then the minimum distance is 0. Hence, in the following
 *   discussion, we exclude the case where there is at least 1 'Z'.
 * - For simple discussion, assume there are 2 virtual restaurants at index
 *   -INFINITY and INFINITY.
 * - Initially, let the minimum distance be m = INIFNITY.
 * - Scan through the array. For each restaurant 'R' at index i, find the
 *   nearest restaurant at index j > i (to the right). For any drugstore 'D' at
 *   index k between (max(0, i), min(j, N)) (N is the length of the highway),
 *   we compute: m = min(m, k - i, j - k)
 * - Time complexity: O(N)
 */

#include <stdio.h>

#define MAX_LENGTH 2000000
#define RESTAURANT 'R'
#define DRUGSTORE 'D'
#define RESTAURANT_DRUGSTORE 'Z'
#define MIN(a, b) (((a) < (b)) ? (a) : (b))

int minDistanceRestaurantAndDrugstore(char road[], int roadLength);

int main(void) {
  int roadLength;
  char road[MAX_LENGTH + 1];

  while(1) {
    scanf("%d", &roadLength);
    if (!roadLength) {
      break;
    }
    scanf("%s", road);
    printf("%d\n", minDistanceRestaurantAndDrugstore(road, roadLength));
  }

  return 0;
}

int minDistanceRestaurantAndDrugstore(char road[], int roadLength) {
  int minDistance = MAX_LENGTH;
  int prevRestaurant = -1, curRestaurant = -1, curPos, i;

  for (curPos = 0; curPos < roadLength; ++curPos) {
    if (road[curPos] == RESTAURANT_DRUGSTORE) {
      minDistance = 0;
      break;
    } else if (road[curPos] == RESTAURANT || curPos == roadLength - 1) {
      prevRestaurant = curRestaurant;
      curRestaurant = curPos;
      if (road[curPos] != RESTAURANT) {
        curRestaurant++;
      }

      for (i = prevRestaurant + 1; i < curRestaurant; ++i) {
        if (road[i] != DRUGSTORE) {
          continue;
        }
        if (prevRestaurant >= 0) {
          minDistance = MIN(minDistance, i - prevRestaurant);
        }
        if (curRestaurant < roadLength) {
          minDistance = MIN(minDistance, curRestaurant - i);
        }
      }
    }
  }

  return minDistance;
}
