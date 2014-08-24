/*******************************************************
 * Author: Nguyen Truong Duy
 *******************************************************/

/**
 * Methodology:
 * - By definition, the longest road is the longest trail in the graph (i.e it does
 * not use an edge twice)
 * - We define
 *      f(G) = the length of the longest road in the graph G
 *      f(v, G) = the length of the longest road in the graph G starting at v
 * - So f(G) = max {f(v, G)} for all v in V (the vertex set of G)
 * - f(v, G) can be computed using the recurrence:
 *      f(v, G) = 0 if v does not have any adjacent neighbor
 *      f(v, G) = 1 + max {f(w, G - (v, w))} 
 * where w is a neighbor of v, and G - (v, w) is the graph resulted from removing
 * an edge (v, w) from G.
 *
 */

#include <cstdio>
#include <vector>

using namespace std;

int lengthOfLongestRoad(
    vector<vector<int> >& adjMat,
    int curV) {
  int maxNextLength = -1;
  for (int i = 0; i < adjMat.size(); ++i) {
    if (i != curV && adjMat[curV][i]) {
      // Remove this edge
      adjMat[curV][i] = 0;
      adjMat[i][curV] = 0;

      int length = lengthOfLongestRoad(adjMat, i);
      if (length > maxNextLength) {
        maxNextLength = length;
      }

      // Backtrack
      adjMat[curV][i] = 1;
      adjMat[i][curV] = 1;
    }
  }

  return 1 + maxNextLength;
}
 
int lengthOfLongestRoad(vector<vector<int> >& adjMat) {
  int maxLength = 0;
  for (int i = 0; i < adjMat.size(); ++i) {
    int length = lengthOfLongestRoad(adjMat, i);
    if (length > maxLength) {
      maxLength = length;
    }
  }
  return maxLength;
}

int main(void) {
  int numV, numE, u, v;
  vector<vector<int> > adjMat;

  while (1) {
    scanf("%d %d", &numV, &numE);
    if (!(numV && numE)) {
      break;
    }

    adjMat.assign(numV, vector<int>(numV, 0));

    for (int i = 0; i < numE; ++i) {
      scanf("%d %d", &u, &v);
      adjMat[u][v] = 1;
      adjMat[v][u] = 1;
    }

    printf("%d\n", lengthOfLongestRoad(adjMat));
  }
  return 0;
}

