/*******************************************************
 * Author: Nguyen Truong Duy
 *******************************************************/

/* Methodology:
 *  + Use Floy-Warshall algorithm to find all-pair shortest path.
 *  + Define f(i) to be the sum of the costs of all shortest paths from i to j (1 <= j <= n)
 *  + We need to 1 <= k <= n such that f(k) is smallest.
 *
 *  + Time complexity: O(V^3) where V is the number of vertices.
 *    In this problem, V <= 22 so the performance is acceptable.
 *
 *  + Assumption: the graph is connected.
 */

#include <cstdio>
#include <string>
#include <vector>

using namespace std;

const int INFINITY = 1000000000;
const int MAX_SIZE = 22;
const int MAX_LEN_NAME = 20;

void computeAllPairShortestPath(int minCost[][MAX_SIZE], int numV);
int findBestMeetingPlace(int shortestPathCost[][MAX_SIZE], int numV);

int main(void)
{
    int numV, numE, caseId, u, v, cost, chosenPerson;
    vector<string> nameVect;
    int shortestPathCost[MAX_SIZE][MAX_SIZE];
    char name[MAX_LEN_NAME + 1];

    caseId = 1;
    while(1)
    {
        scanf("%d", &numV);
        if(!numV)
            break;
        scanf("%d", &numE);

        nameVect.clear();
        for(int i = 0; i < numV; i++)
        {
            scanf("%s", name);
            nameVect.push_back(name);
        }

        // Initialize the shortestPathCost matrix
        for(int row = 0; row < numV; row++)
            for(int col = 0; col < numV; col++)
                shortestPathCost[row][col] = INFINITY;
        for(int row = 0; row < numV; row++)
            shortestPathCost[row][row] = 0;

        for(int i = 0; i < numE; i++)
        {
            scanf("%d %d %d", &u, &v, &cost);
            u--;
            v--;
            shortestPathCost[u][v] = cost;
            shortestPathCost[v][u] = cost;
        }

        computeAllPairShortestPath(shortestPathCost, numV);

        chosenPerson = findBestMeetingPlace(shortestPathCost, numV);

        printf("Case #%d : %s\n", caseId, nameVect[chosenPerson].c_str());

        caseId++;
    }
    return 0;
}

void computeAllPairShortestPath(int minCost[][MAX_SIZE], int numV)
{
    int k, u, v;

    for(k = 0; k < numV; k++)
        for(u = 0; u < numV; u++)
            for(v = 0; v < numV; v++)
            {
                if(minCost[u][k] == INFINITY || minCost[k][v] == INFINITY)
                    continue;

                int totalCost = minCost[u][k] + minCost[k][v];
                if(totalCost < minCost[u][v])
                    minCost[u][v] = totalCost;
            }
}

int findBestMeetingPlace(int shortestPathCost[][MAX_SIZE], int numV)
{
    int sumCost, minU, minCost;

    minCost = INFINITY;
    for(int u = 0; u < numV; u++)
    {
        sumCost = 0;
        for(int v = 0; v < numV; v++)
            sumCost += shortestPathCost[u][v];

        if(sumCost < minCost)
        {
            minCost = sumCost;
            minU = u;
        }
    }

    return minU;
}
