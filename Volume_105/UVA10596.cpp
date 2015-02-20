/*******************************************************
 * Author: Nguyen Truong Duy
 *******************************************************/

//// C++11 ////

/**
 * Methodology:
 * - The problem essentially asks if there exists an Euler tour that visits
 * all edges in the given graph
 * - A graph has an Euler tour if and only if it is connected and every vertex
 * has an even degree (*)
 * - Gotchas:
 *  + For this problem, we should exclude isolated vertices when checking
 * connectivity. That means if the graph has 1 connected component whose
 * number of edges is larger than 0 and every other vertices (not in this
 * connected component) are isolated vertices, then connectivity requirement
 * in (*) is satisfied
 *  + If the number of edges is 0, then the ouput should be "Not Possible"
 *
 * - Time complexity: O(V + E)
 */

#include <cstdio>
#include <vector>

using namespace std;

void dfs(
    const vector<vector<int> >& adjList,
    int startV,
    vector<bool>& visited) {
  visited[startV] = true;
  for (auto&& neighborV : adjList[startV]) {
    if (!visited[neighborV]) {
      dfs(adjList, neighborV, visited);
    }
  }
}

bool existEulerTour(const vector<vector<int> >& adjList) {
  // Checks if every vertex has even degree
  for (auto&& neighbors : adjList) {
    if (neighbors.size() & 1) {
      return false;
    }
  }

  // Checks if the graph is connected
  vector<bool> visited(adjList.size(), false);
  // Excludes all isolated vertices in our traversal
  for (int v = 0; v < adjList.size(); ++v) {
    if (!adjList[v].size()) {
      visited[v] = true;
    }
  }
  int startV = -1;
  for (int v = 0; v < visited.size(); ++v) {
    if (!visited[v]) {
      startV = v;
      break;
    }
  }
  if (startV >= 0) {
    dfs(adjList, startV, visited);
  }
  for (auto&& boolValue : visited) {
    if (!boolValue) {
      return false;
    }
  }

  return true;
}

int main(void) {
  int numV, numE, u, v;
  vector<vector<int> > adjList;

  while (scanf("%d %d", &numV, &numE) > 0) {
    adjList.assign(numV, vector<int>());
    for (int i = 0; i < numE; ++i) {
      scanf("%d %d", &u, &v);
      adjList[u].push_back(v);
      adjList[v].push_back(u);
    }

    if (numE && existEulerTour(adjList)) {
      printf("Possible\n");
    } else {
      printf("Not Possible\n");
    }
  }
  return 0;
}
