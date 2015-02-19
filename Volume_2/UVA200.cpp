/*******************************************************
 * Author: Nguyen Truong Duy
 *******************************************************/

//// C++11 ////

/**
 * Methodology:
 * - This problem can be solved with topological sorting.
 * - Construct a directed graph G = (V, E) where V is the set of alphabets
 * presented in the list of input strings. An edge (u, v) means u is lower
 * than v in the new alphabetical ordering.
 * - To populate all edges in G, consider all string pairs (s, t). Suppose
 * s < t and there exists index i such that s[i] != t[i] and
 * s[0 ... i - 1] == t[0 ... i - 1]. Then we have an edge (s[i], t[i])
 * - We can assume G is a DAG and connected.
 * - Running topological sort on G with the starting vertex (vertex with
 * in-degree equal zero) gives the final answer
 *
 * - Time complexity: O(N^2 * L) where N is the number of strings and L is
 * the maximum length of all strings
 */

#include <algorithm>
#include <cstdio>
#include <string>
#include <vector>

using namespace std;

#define NUM_ALPHABET 26
#define MAX_LENGTH 20

int findMax(int a, int b) {
  return (a < b) ? b : a;
}

void convertAdjMatToAdjList(
    int adjMat[][NUM_ALPHABET],
    int numV,
    vector<vector<int> >& adjList) {
  adjList.assign(numV, vector<int>());
  for (int i = 0; i < numV; ++i) {
    for (int j = 0; j < numV; ++j) {
      if (adjMat[i][j]) {
        adjList[i].push_back(j);
      }
    }
  }
}

void dfs(
    const vector<vector<int> >& adjList,
    int startV,
    vector<bool>& visited,
    vector<int>& topoOrder) {
  visited[startV] = true;
  for (auto neighborV : adjList[startV]) {
    if (!visited[neighborV]) {
      dfs(adjList, neighborV, visited, topoOrder);
    }
  }
  topoOrder.push_back(startV);
}

// Assume the graph has no isolated vertex. So the start vertex is a vertex
// with in-degree equal to 0
int findStartVertex(const vector<vector<int> >& adjList) {
  vector<int> inDegree(adjList.size(), 0);

  for (auto&& neighbors : adjList) {
    for (auto vertex : neighbors) {
      inDegree[vertex]++;
    }
  }

  for (int i = 0; i < adjList.size(); ++i) {
    if (!inDegree[i] && adjList[i].size()) {
      return i;
    }
  }

  return -1;  // Dummy code
};

void getTopologicalOrder(
    const vector<vector<int> >& adjList,
    vector<int>& topoOrder) {
  vector<bool> visited(adjList.size(), false);
  int startV = findStartVertex(adjList);
  dfs(adjList, startV, visited, topoOrder);
  reverse(topoOrder.begin(), topoOrder.end());
}

int main(void) {
  int adjMat[NUM_ALPHABET][NUM_ALPHABET] = {{0}};
  vector<vector<int> > adjList;
  vector<string> strList;
  char str[MAX_LENGTH + 1];
  int startV;

  while (1) {
    scanf("%s", str);
    if (str[0] == '#') {
      break;
    }
    strList.push_back(str);
  }

  // Construct DAG
  for (int i = 0; i < strList.size(); ++i) {
    for (int j = i + 1; j < strList.size(); ++j) {
      int maxLen = findMax(strList[i].size(), strList[j].size());
      int k = 0;
      while (k < maxLen && strList[i][k] == strList[j][k]) {
        k++;
      }
      if (k < maxLen) {
        adjMat[strList[i][k] - 'A'][strList[j][k] - 'A'] = 1;
      }
    }
  }
  convertAdjMatToAdjList(adjMat, NUM_ALPHABET, adjList);

  // Generate topological order
  vector<int> topoOrder;
  getTopologicalOrder(adjList, topoOrder);

  for(int i = 0; i < topoOrder.size(); ++i) {
    printf("%c", topoOrder[i] + 'A');
  }
  printf("\n");
  return 0;
}
