/*******************************************************
 * Author: Nguyen Truong Duy
 *******************************************************/

/* Methodology:
 *  + Perform a DFS / BFS to find reachable / unreachable nodes in the given
 *      directed graph.
 *  + Note: A vertex u is reachable from u if and only if.
 *      - There is a loop at u.
 *      - There is a cycle starting at and ending at u.
 *  + Time complexity: O(Q * (V + E)) where
 *      - Q is the number of queries.
 *      - V, E are the number of vertices and edges.
 */

#include <cstdio>
#include <vector>

using namespace std;

void getUnreachableNodes(const vector<vector<int> > & adjList, int vStart, vector<int> & unreachableList);
void DFS(const vector<vector<int> > & adjList, int u, vector<bool> & hasReached);

int main(void)
{
    vector<vector<int> > adjList;
    vector<int> unreachableList, emptyList;
    int numV, vStart, vEnd, numQuery;

    while(1)
    {
        scanf("%d", &numV);
        if(!numV)
            break;

        adjList.assign(numV, emptyList);
        while(1)
        {
            scanf("%d", &vStart);
            if(!vStart)
                break;

            vStart--;
            while(1)
            {
                scanf("%d", &vEnd);
                if(!vEnd)
                    break;

                vEnd--;
                adjList[vStart].push_back(vEnd);
            }
        }

        scanf("%d", &numQuery);
        for(int i = 0; i < numQuery; i++)
        {
            scanf("%d", &vStart);
            vStart--;

            getUnreachableNodes(adjList, vStart, unreachableList);

            printf("%d", (int) unreachableList.size());
            for(int i = 0; i < (int) unreachableList.size(); i++)
                printf(" %d", unreachableList[i] + 1);  // Results are 1-indexing
            printf("\n");
        }
    }

    return 0;
}

void getUnreachableNodes(const vector<vector<int> > & adjList, int vStart, vector<int> & unreachableList)
{
    int numV = (int) adjList.size();
    vector<bool> hasReached(numV, false);

    DFS(adjList, vStart, hasReached);

    unreachableList.clear();
    for(int v = 0; v < numV; v++)
        if(!hasReached[v])
            unreachableList.push_back(v);
}

void DFS(const vector<vector<int> > & adjList, int u, vector<bool> & hasReached)
{
    for(int ind = 0; ind < (int) adjList[u].size(); ind++)
    {
        int v = adjList[u][ind];

        if(!hasReached[v])
        {
            hasReached[v] = true;
            DFS(adjList, v, hasReached);
        }
    }
}
