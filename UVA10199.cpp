/*******************************************************
 * Author: Nguyen Truong Duy
 *******************************************************/

/* Methodology:
 *  + This problem asks us to find all the articulation points in the given undirected loopless graph.
 *
 *  + Solution: Use Hopcroft - Tarjan's algorithm.
 *  + Time complexity: O(V + E)
 *
 *  + Brief explannation of the idea:
 *      - We keep track of the following information:
 *        dfsId[v] = the number indicating the order the node v is visited by DFS algorithm.
 *        lowLink[v] = the smallest dfsId that can be reached from v using a backedge from v (or its descendants)
 *              to one of its proper ancestor in the DFS tree.
 *
 *      - An articulation point is a vertex whose removal increasing the number of connect components of a graph.
 *        Hence, u is an articulation point if and only if there EXISTS some child v of u such that
 *              lowLink[v] >= dfsNum[u] (This means when removing v, we cannot reach u)
 *
 *      - Special case: the root of the DFS tree is an articulation point if and only if it has more than 1
 *              child in the DFS tree.
 */

#include <cstdio>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX_LEN_NAME = 30;

void findArticulationPoints(const vector<vector<int> > & adjList, vector<int> & articulationVect);
int dfsToFindArticulation(const vector<vector<int> > & adjList, int u, int directParent, int *dfsNum, vector<int> & dfsId,
                          vector<int> & lowLink, vector<bool> & isArticulation);

int main(void)
{
    vector<vector<int> > adjList;
    int numV, numE, caseId, idOne, idTwo;
    vector<int> emptyList, articulationVect;
    vector<string> nameVect, resultVect;
    map<string, int> mapNameToId;
    char name[MAX_LEN_NAME + 1];

    bool isFirst = true;
    caseId = 1;
    while(1)
    {
        scanf("%d", &numV);
        if(!numV)
            break;

        adjList.assign(numV, emptyList);
        nameVect.clear();
        mapNameToId.clear();

        for(int id = 0; id < numV; id++)
        {
            scanf("%s", name);
            nameVect.push_back(name);
            mapNameToId[name] = id;
        }

        scanf("%d", &numE);
        for(int e = 0; e < numE; e++)
        {
            // Assumption: the input is valid. Name in this part must be listed before.
            scanf("%s", name);
            idOne = mapNameToId[name];
            scanf("%s", name);
            idTwo = mapNameToId[name];
            adjList[idOne].push_back(idTwo);
            adjList[idTwo].push_back(idOne);
        }

        findArticulationPoints(adjList, articulationVect);

        if(isFirst)
            isFirst = false;
        else
            printf("\n");

        printf("City map #%d: %d camera(s) found\n", caseId, (int) articulationVect.size());
        resultVect.clear();
        for(int i = 0; i < (int) articulationVect.size(); i++)
            resultVect.push_back(nameVect[articulationVect[i]]);
        sort(resultVect.begin(), resultVect.end());
        for(int i = 0; i < (int) resultVect.size(); i++)
            printf("%s\n", resultVect[i].c_str());

        caseId++;
    }
    return 0;
}

void findArticulationPoints(const vector<vector<int> > & adjList, vector<int> & articulationVect)
{
    articulationVect.clear();

    int numV = (int) adjList.size();
    vector<int> dfsId(numV, -1);
    vector<int> lowLink(numV, -1);
    int dfsNum = 0;
    vector<bool> isArticulation(numV, false);

    for(int u = 0; u < numV; u++)
        if(dfsId[u] < 0)
        {
            // Not visited by DFS yet
            int numRootChild = dfsToFindArticulation(adjList, u, u, &dfsNum, dfsId, lowLink, isArticulation);

            if(numRootChild > 1)
                isArticulation[u] = true;
            else
                // isArticulation[u] will be turned on during the DFS traversal. So we must turn it off
                isArticulation[u] = false;
        }

   for(int u = 0; u < numV; u++)
        if(isArticulation[u])
            articulationVect.push_back(u);
}

int dfsToFindArticulation(const vector<vector<int> > & adjList, int u, int directParent, int *dfsNum, vector<int> & dfsId,
                          vector<int> & lowLink, vector<bool> & isArticulation)
{
    dfsId[u] = *dfsNum;
    lowLink[u] = *dfsNum;
    (*dfsNum)++;

    int numChild = 0;

    for(int i = 0; i < (int) adjList[u].size(); i++)
    {
        int v = adjList[u][i];

        if(dfsId[v] < 0)
        {
            numChild++;

            dfsToFindArticulation(adjList, v, u, dfsNum, dfsId, lowLink, isArticulation);

            if(lowLink[v] >= dfsId[u])
            {
                // u is an articulation point
                isArticulation[u] = true;
            }

            if(lowLink[v] < lowLink[u])
                lowLink[u] = lowLink[v];
        }
        else
        {
            if(v != directParent && dfsId[v] < lowLink[u])
            {
                // v is an ancestor of u (v != parent of u) and u-v is a backedge
                lowLink[u] = dfsId[v];
            }
        }
    }

    return numChild;
}
