/*******************************************************
 * Author: Nguyen Truong Duy
 *******************************************************/

/* Methodology:
 * - Straightforward problem.
 * - We count the number of local extremes (local maximum or local minimum) for
 * each element in the array in a circular manner. That is, A[i] (0 <= i < N)
 * is a local extreme if
 *      A[i] = max(A[(i - 1 + N) % N], A[i], A[(i + 1) % N]) or
 *      A[i] = min(A[(i - 1 + N) % N], A[i], A[(i + 1) % N])
 * - Note that we can assume no two consecutive elements are the same.
 *
 * Time complexity: O(N) where N is the number of elements
 */

#include <cstdio>
#include <vector>

using namespace std;

int countLocalExtremes(const vector<int>& arr) {
  int numExtremes = 0;

  for (int i = 1; i < arr.size() - 1; ++i) {
    if ((arr[i] > arr[i - 1] && arr[i] > arr[i + 1]) ||
        (arr[i] < arr[i - 1] && arr[i] < arr[i + 1])) {
      numExtremes++;
    }
  }

  return numExtremes;
}

int main(void) {
  int size;
  vector<int> arr;

  while (1) {
    scanf("%d", &size);
    if (!size) {
      break;
    }

    arr.assign(size + 2, 0);
    for (int i = 1; i <= size; ++i) {
      scanf("%d", &arr[i]);
    }
    // Musical loop
    arr[0] = arr[size];
    arr[size + 1] = arr[1];

    printf("%d\n", countLocalExtremes(arr));
  }

  return 0;
}
