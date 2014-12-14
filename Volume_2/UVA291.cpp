/*******************************************************
 * Author: Nguyen Truong Duy
 *******************************************************/

//// C++11 ////

/* Methodology:
 * - Model the house of Santa Claus as a undirected graph with 5 vertices
 *   (labeled as 1, 2, 3, 4, 5) and 8 edges.
 * - Use recursion and backtracking technique to populate all Euler paths
 *   in the graph starting from vertex 1 in the lower left corner.
 */

#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

using namespace std;

#define NUM_VERTICES 5
#define NUM_EDGES 8

void constructHouseGraph(int adjMat[][NUM_VERTICES]);
void findAllEulerPaths(
  int startV, int adjMat[][NUM_VERTICES],
  string& initialPath, vector<string>& eulerPaths);

int main(void) {
  int adjMat[NUM_VERTICES][NUM_VERTICES];

  constructHouseGraph(adjMat);

  vector<string> eulerPaths;
  string initialPath;
  initialPath.push_back('0' + 1);
  findAllEulerPaths(0, adjMat, initialPath, eulerPaths);

  for (int i = 0; i < eulerPaths.size(); ++i) {
    printf("%s\n", eulerPaths[i].c_str());
  }

  return 0;
}

// Return the number of edges in the House of Santa Claus graph
void constructHouseGraph(int adjMat[][NUM_VERTICES]) {
  memset(adjMat, 0, NUM_VERTICES * NUM_VERTICES * sizeof(int));
  adjMat[0][1] = adjMat[1][0] = 1;
  adjMat[0][4] = adjMat[4][0] = 1;
  adjMat[0][2] = adjMat[2][0] = 1;
  adjMat[1][4] = adjMat[4][1] = 1;
  adjMat[1][2] = adjMat[2][1] = 1;
  adjMat[2][3] = adjMat[3][2] = 1;
  adjMat[2][4] = adjMat[4][2] = 1;
  adjMat[3][4] = adjMat[4][3] = 1;
}

// Euler Paths are populated in increasing order
void findAllEulerPaths(
    int startV, int adjMat[][NUM_VERTICES],
    string& curPath, vector<string>& eulerPaths) {
  if (curPath.length() >= NUM_EDGES + 1) {
    // If there are NUM_EDGES + 1 vertices, the path is of length NUM_EDGES
    eulerPaths.push_back(curPath);
    return;
  }

  for (int nextV = 0; nextV < NUM_VERTICES; nextV++) {
   if (nextV != startV && adjMat[startV][nextV]) {
      adjMat[nextV][startV] = adjMat[startV][nextV] = 0;
      curPath.push_back('0' + nextV + 1);

      // Recurse
      findAllEulerPaths(nextV, adjMat, curPath, eulerPaths);

      // Backtrack
      adjMat[nextV][startV] = adjMat[startV][nextV] = 1;
      curPath.pop_back();
    }
  }
}
