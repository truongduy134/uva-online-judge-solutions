/*******************************************************
 * Author: Nguyen Truong Duy
 *******************************************************/

/**
 * Methodology:
 * - Assume the input nodes A and B are always valid brothers in the family tree
 * (e.g. A and B cannot be the same, or A is a father of B, etc.)
 * - Observe that the family tree in the problem is a complete binary tree
 * - Let T(h) be the number of nodes in the complete binary tree of height h
 * - Let H(x) >= 1 be the level in the complete binary tree of node with ID x
 * - Then the number of distinct people in the family tree with N generations
 * and with A and B be brothers with the same parent is:
 *    T(N) - (T(max(H(A), H(B)) - 1) = T(N) - T(max(H(A), H(B))) + 1
 */

#include <stdio.h>

int powerOfTwo(int power) {
  int i;
  int result = 1;

  for (i = 1; i <= power; ++i) {
    result <<= 1;
  }

  return result;
}

int numberOfNodesInCompleteBinaryTree(int height) {
  return powerOfTwo(height) - 1;
}

int max(int a, int b) {
  return (a > b) ? a : b;
}

int heightOfNode(int nodeID) {
  int minID = 1;
  int maxID = 2;
  int height = 1;

  while (!(nodeID >= minID && nodeID < maxID)) {
    minID <<= 1;
    maxID <<= 1;
    height++;
  }

  return height;
}

int main(void) {
  int numCases;
  int numGenerations, nodeA, nodeB, heightA, heightB, numDistinctNodes;

  scanf("%d", &numCases);

  while (numCases) {
    scanf("%d %d %d", &numGenerations, &nodeA, &nodeB);

    heightA = heightOfNode(nodeA);
    heightB = heightOfNode(nodeB);
    numDistinctNodes =
      numberOfNodesInCompleteBinaryTree(numGenerations) -
      numberOfNodesInCompleteBinaryTree(
        numGenerations - max(heightA, heightB) + 1
      ) + 1;
    printf("%d\n", numDistinctNodes);

    numCases--;
  }

  return 0;
}
