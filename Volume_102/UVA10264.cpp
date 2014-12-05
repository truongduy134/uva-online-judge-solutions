/*******************************************************
 * Author: Nguyen Truong Duy
 *******************************************************/

/* Methodology:
 * - The trick in this problem is to find a good representation of a corner, and
 * how to find neighbor corners efficiently with that representation.
 * - Since the number of dimensions N < 15, we can use integers to represent
 * corners. Each integer indicates the id of a corner. Moreover, we can use
 * bitwise operations to find ids of neighbors efficiently.
 * - Each corner has N neighbors. The i-th neighbor of a corner with id x has
 * id equals to x BITWISE XOR pow(2, i)
 *
 * - Time complexity: O(2^N * N) where N is the number of dimensions
 */

#include <cstdio>
#include <vector>

using namespace std;

int computePotency(
    int corner,
    int dimension,
    const vector<int>& weights) {
  int potency = 0;
  for (int position = 0; position < dimension; position++) {
    int neighbor = corner ^ (1 << position);
    potency += weights[neighbor];
  }
  return potency;
}

int maxPotencySumNeighborPair(int dimension, const vector<int>& potencies) {
  int maxSum = 0;
  for (int corner = 0; corner < potencies.size(); ++corner) {
    for (int position = 0; position < dimension; ++position) {
      int nextCorner = corner ^ (1 << position);
      int sum = potencies[corner] + potencies[nextCorner];
      if (sum > maxSum) {
        maxSum = sum;
      }
    }
  }
  return maxSum;
}

int main(void) {
  int dimension;
  vector<int> weights, potencies;

  while (scanf("%d", &dimension) > 0) {
    int numCorners = 1 << dimension;

    weights.assign(numCorners, 0);
    potencies.assign(numCorners, 0);

    for (int i = 0; i < numCorners; ++i) {
      scanf("%d", &weights[i]);
    }

    for (int corner = 0; corner < numCorners; ++corner) {
      potencies[corner] = computePotency(corner, dimension, weights);
    }

    printf("%d\n", maxPotencySumNeighborPair(dimension, potencies));
  }

  return 0;
}
