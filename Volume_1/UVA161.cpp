/*******************************************************
 * Author: Nguyen Truong Duy
 *******************************************************/

/* Methodology:
 * - For this problem, it is okay to assume that initially all lights are green
 * and the color cycle is green - orange - red, etc.
 * - The problem asks us to determine the first time all signals are green (
 * orange does not count) after at least one of them turns orange.
 * - For a light with green cycle T, it will be green at time 0 to time
 * (T - 5 - 1) = (T - 6), and not green at time T - 5 to 2T - 1, then green
 * again from time 2T to 2T - 6, and so on. (**)
 * - Since we are considering a period of 5 hours only, we consider time 0 to
 * time 5 * 3600.
 * - Let G be an array of 5 * 3600 + 1 elements. If G has only 5 * 3600, the
 * submission is not accepted.
 *   G[i] is true means at the time i, all signals are green.
 *   Initially G[i] is true for all i.
 * - For each signal k, we turn off G[i] (set G[i] to false) for those times
 * that signal k is not green based on observation (**)
 * - After that, we choose the smallest i such that G[i] is true, and there
 * exists j < i such that G[j] is false
 *
 * - Time complexity: O(5 * 3600 * K) where K is the number of signals in each
 * problem instance.
 */

#include <cstdio>
#include <vector>

using namespace std;

#define MIN(a, b) ((a) < (b) ? (a) : (b))

const int MAX_TIME_PERIOD = 5 * 3600 + 1;

int computeNextSyncTime(const vector<int>& timeCycles) {
  vector<bool> areAllGreen(MAX_TIME_PERIOD, true);
  int startNonGreen, doubleCycle, cycle, endNonGreen;

  for (int lightId = 0; lightId < timeCycles.size(); ++lightId) {
    cycle = timeCycles[lightId];
    doubleCycle = cycle << 1;

    // Last 5 seconds in green cycle is actually orange
    for (startNonGreen = cycle - 5; startNonGreen < MAX_TIME_PERIOD;
         startNonGreen += doubleCycle) {
      endNonGreen = MIN(startNonGreen + cycle + 5, MAX_TIME_PERIOD);
      for (int i = startNonGreen; i < endNonGreen; ++i) {
        areAllGreen[i] = false;
      }
    }
  }

  int firstNonGreenInd = 0;
  while (firstNonGreenInd < MAX_TIME_PERIOD && areAllGreen[firstNonGreenInd]) {
    firstNonGreenInd++;
  }

  for (int i = firstNonGreenInd + 1; i < MAX_TIME_PERIOD; ++i) {
    if (areAllGreen[i]) {
      return i;
    }
  }
  return -1;
}

void getTimeStr(int numSeconds, char timeStr[]) {
  int numMinutes = numSeconds / 60;
  numSeconds %= 60;
  int numHours = numMinutes / 60;
  numMinutes %= 60;
  sprintf(timeStr, "%02d:%02d:%02d", numHours, numMinutes, numSeconds);
}

int main(void) {
  vector<int> timeCycles;
  int cycle;
  int timeForNextSync;
  char timeStr[10];

  while (1) {
    timeCycles.clear();
    while (1) {
      scanf("%d", &cycle);
      if (!cycle) {
        break;
      }
      timeCycles.push_back(cycle);
    }
    if (timeCycles.empty()) {
      break;
    }

    timeForNextSync = computeNextSyncTime(timeCycles);
    if (timeForNextSync < 0) {
      printf("Signals fail to synchronise in 5 hours\n");
    } else {
      getTimeStr(timeForNextSync, timeStr);
      printf("%s\n", timeStr);
    }
  }

  return 0;
}
