/*******************************************************
 * Author: Nguyen Truong Duy
 *******************************************************/

/* Methodology:
 *  + Problem summary: This problem can be modelled as a directed graph problem.
 *      - Each letter is a vertex.
 *        There is a directed edge from u to v if u < v
 *      - We must generate all topological orders
 *      - A topological order can be seen as a string.
 *      - Output those strings in lexicographical order.
 *
 *  + To generate all topological orders, we must use recursion.
 *  + Let G be a directed graph.
 *    Note that G is acyclic (Otherwise, the topological order is not defined)
 *    Hence, there exists a vertex u whose in degree is 0. Note that there exists
 *         a topological order in G that has u as the first vertex
 *  + Therefore, we have the following recurrence:
 *        {Ord | Ord is a topological order of G} 
 *		= {u followed by Ord' | u is a vertex in G whose in-degree is 0 and 
 *								Ord' is a topological order of G - {u} }
 *      (G - {u} is a directed graph obtained by removing u and its edges from G)
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <algorithm>
#include <string>
#include <queue>

using namespace std;

const int MAX_LEN_LINE = 100;
const int NUM_ALPHA = 26;
char DELIM[2] = " ";

void generateAllTopoOrder(const vector<char> &varList, const vector<vector<int> > & adjList,
                          vector<string> & topoOrderList, vector<int> & inDegreeList,
                          vector<int> & topoOrder, vector<bool> & visited);
void getSortedListOfTopoOrder(const vector<char> &varList, const vector<vector<int> > & adjList,
                              vector<string> & topoOrderList);

int main(void)
{
    vector<vector<int> > adjList;
    vector<char> varList;
    vector<int> mapCharToId, emptyList;
    vector<string> topoOrderList;
    char line[MAX_LEN_LINE + 1], *token;
    int idOne, idTwo;

    bool isFirst = true;
    while(gets(line) != NULL)
    {
        adjList.clear();
        varList.clear();

        token = strtok(line, DELIM);

        while(token != NULL)
        {
            varList.push_back(token[0]);

            token = strtok(NULL, DELIM);
        }

        sort(varList.begin(), varList.end());
        mapCharToId.assign(NUM_ALPHA, -1);

        for(int i = 0; i < (int) varList.size(); i++)
            mapCharToId[(int) varList[i] - 'a'] = i;

        adjList.assign(varList.size(), emptyList);

        gets(line);
        token = strtok(line, DELIM);
        while(token != NULL)
        {
            idOne = mapCharToId[(int) token[0] - 'a'];
            token = strtok(NULL, DELIM);
            idTwo = mapCharToId[(int) token[0] - 'a'];
            adjList[idOne].push_back(idTwo);

            token = strtok(NULL, DELIM);
        }

        getSortedListOfTopoOrder(varList, adjList, topoOrderList);

        if(isFirst)
            isFirst = false;
        else
            printf("\n");
        for(int i = 0; i < (int) topoOrderList.size(); i++)
            printf("%s\n", topoOrderList[i].c_str());
    }

    return 0;
}

void getSortedListOfTopoOrder(const vector<char> &varList, const vector<vector<int> > & adjList,
                              vector<string> & topoOrderList)
{
    topoOrderList.clear();

    int numV = (int) adjList.size();
    vector<int> inDegreeList(numV, 0);

    // Compute in degree
    for(int u = 0; u < numV; u++)
    {
        for(int ind = 0; ind < (int) adjList[u].size(); ind++)
        {
            int v = adjList[u][ind];
            inDegreeList[v]++;
        }
    }

    // Backtrack with zero-in-degree vertices to generate all topological order
    vector<int> topoOrder;
    vector<bool> visited(numV, false);

    generateAllTopoOrder(varList, adjList, topoOrderList, inDegreeList, topoOrder, visited);

    sort(topoOrderList.begin(), topoOrderList.end());
}

void generateAllTopoOrder(const vector<char> &varList, const vector<vector<int> > & adjList,
                          vector<string> & topoOrderList, vector<int> & inDegreeList,
                          vector<int> & topoOrder, vector<bool> & visited)
{
    int numV = (int) adjList.size();

    if((int) topoOrder.size() == numV)
    {
        string order(numV, 'a');
        for(int i = 0; i < numV; i++)
            order[i] = varList[topoOrder[i]];
        topoOrderList.push_back(order);
        return;
    }

    for(int v = 0; v < numV; v++)
        if(inDegreeList[v] == 0 && visited[v] == false)
        {
            // v can be the start of the topological order
            visited[v] = true;
            for(int i = 0; i < (int) adjList[v].size(); i++)
            {
                // Suppose we remove v from the graph. Then the in-degrees of all neighbors of v must be
                // decrement
                int u = adjList[v][i];
                inDegreeList[u]--;
            }
            topoOrder.push_back(v);

            // Recurse
            generateAllTopoOrder(varList, adjList, topoOrderList, inDegreeList, topoOrder, visited);

            // Backtrack
            visited[v] = false;
            for(int i = 0; i < (int) adjList[v].size(); i++)
            {
                int u = adjList[v][i];
                inDegreeList[u]++;
            }
            topoOrder.pop_back();
        }
}
