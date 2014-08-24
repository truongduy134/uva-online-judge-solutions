/*******************************************************
 * Author: Nguyen Truong Duy
 *******************************************************/

/* Methodology:
 * - This can be modelled as a shortest path problem on an unweighted graph.
 * - Construct an undirected unweighted graph G = (V, E) where V is the set of
 * words in the dictionary. Two words u, v in V is adjacent if u and v have the
 * same length, and differ only by 1 character.
 * - For each query with two words u and v, perform breath-first search from u
 * and count the number of steps to reach v.
 *
 * Time complexity:
 * - Graph contruction: O(N^2 * l) where N is the number of words, l is the
 * maximum length among all words.
 * - Each query: O(N^2) where N is the number of words in the worst case.
 */

#include <cstdio>
#include <vector>
#include <string>
#include <map>
#include <queue>
#include <utility>

using namespace std;

#define END_DICT_CHAR '*'
#define MAX_WORD_SIZE 100

int hammingDistance(const string& strA, const string& strB) {
  if (strA.length() != strB.length()) {
    return -1;
  }

  int dist = 0;
  for (int i = 0; i < strA.length(); ++i) {
    if (strA[i] != strB[i]) {
      dist++;
    }
  }

  return dist;  
}

void constructWordGraph(
    vector<vector<int> >& adjList,
    const vector<string>& dictionary,
    const map<string, int>& mapWordToId) {
  int numWord = dictionary.size();
  adjList.assign(numWord, vector<int>());

  for (int i = 0; i < numWord; ++i) {
    for (int j = i + 1; j < numWord; ++j) {
      if (hammingDistance(dictionary[i], dictionary[j]) == 1) {
        int idA = mapWordToId.find(dictionary[i])->second;
        int idB = mapWordToId.find(dictionary[j])->second;
        adjList[idA].push_back(idB);
        adjList[idB].push_back(idA);
      }
    }
  }
}

int computeShortestPathLength(
    const vector<vector<int> >& adjList,
    int startV,
    int endV) {
  int numV = adjList.size();
  queue<pair<int, int> > bfsQueue;
  bfsQueue.push(pair<int, int>(startV, 0));
  vector<bool> visited(numV, false);

  while (!bfsQueue.empty()) {
    pair<int, int> curNode = bfsQueue.front();
    bfsQueue.pop();

    int curV = curNode.first;
    int dist = curNode.second;
    if (curV == endV) {
      return dist;
    }

    for (int k = 0; k < adjList[curV].size(); ++k) {
      int nextV = adjList[curV][k];
      if (!visited[nextV]) {
        visited[nextV] = true;
        bfsQueue.push(pair<int, int>(nextV, dist + 1));
      }        
    }
  }

  return -1;
}

int main(void) {
  int numTest;
  vector<string> dictionary;
  map<string, int> mapWordToId;
  char word[MAX_WORD_SIZE + 1], word2[MAX_WORD_SIZE + 1];
  char line[MAX_WORD_SIZE + 1];
  vector<vector<int> > adjList;

  scanf("%d", &numTest);

  while (numTest--) {
    dictionary.clear();
    mapWordToId.clear();

    int id = 0;
    while (true) {
      scanf("%s", word);
      if (word[0] == END_DICT_CHAR) {
        break;
      }

      dictionary.push_back(word);
      mapWordToId[word] = id++;          
    }
    
    constructWordGraph(adjList, dictionary, mapWordToId);

    fgets(word, MAX_WORD_SIZE + 1, stdin);
    while (true) {
      if (!fgets(line, MAX_WORD_SIZE + 1, stdin)) {
        break;
      }

      if (sscanf(line, "%s %s", word, word2) == 2) {
        int startId = mapWordToId[word];
        int endId = mapWordToId[word2];
        printf("%s %s %d\n", word, word2,
          computeShortestPathLength(adjList, startId, endId));         
      } else {
        break;
      }
    }

    if (numTest > 0) {
      printf("\n");
    }    
  }
  
  return 0;
}

