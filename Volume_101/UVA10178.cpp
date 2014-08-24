/*******************************************************
 * Author: Nguyen Truong Duy
 *******************************************************/

/**
 * Methodlogy:
 * - Since the graph is planar, we can use Euler's formula:
 *      V - E + F = 1 + C
 * where V is the number of vertices, E is the number of edges,
 *       F is the number of faces, C is the number of connected components.
 * - Therefore, F = 1 + C - V + E
 * - To count the number of connected components, we can use BFS or DFS.
 *
 * Time complexity: O(V + E)
 */

#include <cstdio>
#include <queue>
#include <vector>
#include <map>

using namespace std;

void breadthFirstSearch(
    const vector<vector<int> >& adjList,
    vector<bool>& visited,
    int startV) {
  queue<int> bfsQueue;
  bfsQueue.push(startV);
  visited[startV] = true;

  while (!bfsQueue.empty()) {
    int curV = bfsQueue.front();
    bfsQueue.pop();

    for (int i = 0; i < adjList[curV].size(); ++i) {
      int neighborV = adjList[curV][i];
      if (!visited[neighborV]) {
        visited[neighborV] = true;
        bfsQueue.push(neighborV);
      }
    }
  }
}

int countNumConnectedComponents(const vector<vector<int> >& adjList) {
  int numV = adjList.size();
  vector<bool> visited(numV, false);
  int numCC = 0;
  
  for (int v = 0; v < numV; ++v) {
    if (!visited[v]) {
      numCC++;
      breadthFirstSearch(adjList, visited, v);
    }
  }   

  return numCC;
}

// Assume the input graph is planar
int countNumFaces(const vector<vector<int> >& adjList) {
  int numV = adjList.size();
  int numE = 0;
  for (int i = 0; i < numV; ++i) {
    numE += adjList[i].size();
  }
  numE >>= 1;
  int numCC = countNumConnectedComponents(adjList);

  return 1 + numCC - numV + numE;
}

int getVertexId(map<char, int>& mapNameToId, char name) {
  map<char, int>::iterator it = mapNameToId.find(name);
  if (it != mapNameToId.end()) {
    return it->second;
  }
  int newId = mapNameToId.size();
  mapNameToId[name] = newId;
  return newId;
}
 
int main(void) {
  int numV, numE;
  char v1[2], v2[2];
  vector<vector<int> > adjList;
  map<char, int> mapNameToId;

  while (scanf("%d %d", &numV, &numE) > 0) {
    adjList.assign(numV, vector<int>());
    mapNameToId.clear();      
        
    for (int i = 0; i < numE; i++) {
      scanf("%s %s", v1, v2);
      int id1 = getVertexId(mapNameToId, v1[0]);
      int id2 = getVertexId(mapNameToId, v2[0]);
      adjList[id1].push_back(id2);
      adjList[id2].push_back(id1);  // Undirected edge 
    }

    printf("%d\n", countNumFaces(adjList));
  }
    
  return 0;
}

