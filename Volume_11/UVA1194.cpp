#include <cstdio>
#include <vector>
#include <cstring>

using namespace std;

#define MAX_NUM_JOB 1005
#define MAX_NUM_MODE 101

bool findAndAugmentPath(const vector<vector<int> > & adjList, int leftV, vector<int> & matchedLeftPartner,
                        vector<bool> & visited);
void buildBipartiteGraph(vector<vector<int> > & adjList, int numModeA, int numModeB, int jobAssignment[][2], int numJob);
int getNumMaximumMatching(const vector<vector<int> > & adjList, int sizeLeftSet);

int main(void)
{
    int numModeA, numModeB, numJob, id;
    vector<vector<int> > adjList;
    int jobAssignment[MAX_NUM_JOB][2];

  //  freopen("in.txt", "r", stdin);

    while(1)
    {
        scanf("%d", &numModeA);
        if(numModeA == 0)
            break;
        scanf("%d %d", &numModeB, &numJob);
        for(int i = 0; i < numJob; i++)
            scanf("%d %d %d", &id, &jobAssignment[i][0], &jobAssignment[i][1]);

        /* Description of the bipartite graph:
         *      + Bipartite set 1: Set of modes of machine A.
         *      + Bipartite set 2: Set of modes of machine B.
         *
         * A vertex (or mode) MA in set 1 is connected to a vertex (or mode) MB in set 2 if and only if
         *          there exists a task that requires to be operated in either MA or MB.
         * So an edge can be seen as representation of a task.
         *
         * Note:
         *      + We do not allow parallel edges.
         *      + We ignore tasks that can be operated in mode 0 of A or mode 0 of B (because they do not
         *              incur a cost)
         *
         * The problem now becomes finding the size of a minimum vertex cover to cover all the edges (or tasks)
         *
         * In a bipartite graph, size of a minimum vertex cover = size of a maximum matching
         */
        buildBipartiteGraph(adjList, numModeA, numModeB, jobAssignment, numJob);

        printf("%d\n", getNumMaximumMatching(adjList, numModeA));
    }

    return 0;
}

void buildBipartiteGraph(vector<vector<int> > & adjList, int numModeA, int numModeB, int jobAssignment[][2], int numJob)
{
    vector<int> emptyList;
    int existEdge[MAX_NUM_MODE][MAX_NUM_MODE];

    adjList.assign(numModeA + numModeB, emptyList);
    memset((int *) existEdge, 0, MAX_NUM_MODE * MAX_NUM_MODE * sizeof(int));

    for(int task = 0; task < numJob; task++)
        if(jobAssignment[task][0] && jobAssignment[task][1] &&
           existEdge[jobAssignment[task][0]][jobAssignment[task][1]] == 0)
        {
            adjList[jobAssignment[task][0]].push_back(numModeA + jobAssignment[task][1]);
            existEdge[jobAssignment[task][0]][jobAssignment[task][1]] = 1;
        }
}

int getNumMaximumMatching(const vector<vector<int> > & adjList, int sizeLeftSet)
{
    int numV = (int) adjList.size();

    vector<int> matchedLeftPartner(numV, -1);
    vector<bool> visited;

    int numMaxMatching = 0;
    for(int leftV = 1; leftV < sizeLeftSet; leftV++)
    {
        visited.assign(sizeLeftSet, false);
        if(findAndAugmentPath(adjList, leftV, matchedLeftPartner, visited))
            numMaxMatching++;
    }

    return numMaxMatching;
}

bool findAndAugmentPath(const vector<vector<int> > & adjList, int leftV, vector<int> & matchedLeftPartner,
                        vector<bool> & visited)
{
    if(visited[leftV])
        return false;

    visited[leftV] = true;

    int rightV;
    for(int ind = 0; ind < (int) adjList[leftV].size(); ind++)
    {
        rightV = adjList[leftV][ind];
        if(matchedLeftPartner[rightV] == -1 || findAndAugmentPath(adjList, matchedLeftPartner[rightV],
                                                                  matchedLeftPartner, visited))
        {
            matchedLeftPartner[rightV] = leftV;
            return true;
        }
    }

    return false;
}
