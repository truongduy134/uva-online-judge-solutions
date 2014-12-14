/*******************************************************
 * Author: Nguyen Truong Duy
 *******************************************************/

/* Methodology:
 * - From the list of path-value pairs, we construct a C++ map (whose underlying
 * structure is balanced search tree) whose keys are strings representing the
 * path from root to tree nodes, and values are integers the nodes contain.
 * The comparision order of keys in our map is as follows: we compare the length
 * of two strings, and if they have the same length, we compare them with
 * alphabetical order.
 * - While constructing the map, we can check at the same time if each tree node
 * is given a value exactly once (i.e. there must be no two elements in the
 * input list of path-value pairs that have the same path string). If the
 * condition is violated, output that the input tree is not complete.
 * - Then we check if every node in the tree is given a value. For each key
 * S with length L, we check if the map contains key S[0], S[1], ..., S[L - 2]
 * - Then to print the values in the tree in level order, just do an in-order
 * traversal of our C++ map.
 */

#include <cstdio>
#include <cstring>
#include <map>
#include <string>
#include <utility>
#include <vector>

using namespace std;

#define MAX_STRLEN 500

struct CompareTreePaths {
  bool operator() (const string& path1, const string& path2) const {
    if (path1.length() == path2.length()) {
      return path1 < path2;
    }
    return path1.length() < path2.length();
  }
};

bool buildTree(
  const vector<pair<string, int> >& treeNodes,
  vector<int>& levelOrder
);
bool isValidTreePath(
  const string& nodePath,
  const map<string, int, CompareTreePaths>& tree
);

int main(void) {
  char pairInfo[MAX_STRLEN + 1];
  vector<pair<string, int> > treeNodes;
  int value;
  char nodePath[MAX_STRLEN + 1];
  vector<int> levelOrder;

  while (1) {
    treeNodes.clear();
    while (scanf("%s", pairInfo) > 0 && pairInfo[1] != ')') {
      pairInfo[strlen(pairInfo) - 1] = '\0';
      nodePath[0] = '\0';
      sscanf(pairInfo + 1, "%d,%s", &value, nodePath);
      treeNodes.push_back(pair<string, int>(string(nodePath), value));
    }
    if (treeNodes.empty()) {
      break;
    }

    if (!buildTree(treeNodes, levelOrder)) {
      printf("not complete\n");
    } else {
      printf("%d", levelOrder[0]);
      for (int i = 1; i < levelOrder.size(); ++i) {
        printf(" %d", levelOrder[i]);
      }
      printf("\n");
    }
  }

  return 0;
}

bool buildTree(
    const vector<pair<string, int> >& treeNodes,
    vector<int>& levelOrder) {
  levelOrder.clear();

  map<string, int, CompareTreePaths> tree;
  for (int i = 0; i < treeNodes.size(); ++i) {
    if (tree.find(treeNodes[i].first) != tree.end()) {
      // Two values are mapped to the same tree node
      return false;
    }
    tree.insert(treeNodes[i]);
  }

  for (map<string, int, CompareTreePaths>::const_iterator it = tree.begin();
       it != tree.end(); ++it) {
    if (isValidTreePath(it->first, tree)) {
      levelOrder.push_back(it->second);
    } else {
      return false;
    }
  }

  return true;
}

bool isValidTreePath(
    const string& nodePath,
    const map<string, int, CompareTreePaths>& tree) {
  string curPath;
  if (tree.find(curPath) == tree.end()) {
    return false;
  }
  for (int i = 0; i < nodePath.size(); ++i) {
    curPath.push_back(nodePath[i]);
    if (tree.find(curPath) == tree.end()) {
      return false;
    }
  }
  return true;
}
