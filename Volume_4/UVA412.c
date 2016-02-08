/*******************************************************
 * Author: Nguyen Truong Duy
 *******************************************************/

#include <stdio.h>
#include <math.h>

#define MAX_SIZE 50

int gcd(int a, int b) {
  int r;

  while (b) {
    r = a % b;
    a = b;
    b = r;
  }
  return a;
}

int countNumCoprimePairs(int arr[], int n) {
  int i, j, count = 0;

  for (i = 0; i < n; ++i) {
    for (j = i + 1; j < n; ++j) {
      if (gcd(arr[i], arr[j]) == 1) {
        count++;
      }
    }
  }

  return count;
}

double estimatePi(int numCoprimePairs, int dataSize) {
  int numPairs = (dataSize * (dataSize - 1)) >> 1;
  return sqrt(6.0 * numPairs / numCoprimePairs);
}

int main(void) {
  int n, i, numCoprimePairs;
  int arr[MAX_SIZE];
  double pi;

  while (1) {
    scanf("%d", &n);
    if (!n) {
      break;
    }

    for (i = 0; i < n; ++i) {
      scanf("%d", &arr[i]);
    }

    numCoprimePairs = countNumCoprimePairs(arr, n);
    if (!numCoprimePairs) {
      printf("No estimate for this data set.\n");
    } else {
      pi = estimatePi(numCoprimePairs, n);
      printf("%.6lf\n", pi);
    }
  }
  return 0;
}
