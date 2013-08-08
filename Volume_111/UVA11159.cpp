#include <cstdio>
#include <vector>

using namespace std;

#define MAX_SIZE 101

void buildBipartiteGraph(vector<vector<int> > & adjList, int arrA[], int sizeA, int arrB[], int sizeB);
int getMaximumNumberOfMatching(const vector<vector<int> > & adjList, int sizeLeftSet);
bool findAndAugmentPath(const vector<vector<int> > & adjList, int leftVertex,
                        vector<int> & matchedLeftPartner, vector<bool> & visited);

int main(void)
{
    int T, sizeA, sizeB, arrA[MAX_SIZE], arrB[MAX_SIZE], caseId;
    vector<vector<int> > adjList;

 //   freopen("in.txt", "r", stdin);

    scanf("%d", &T);
    caseId = 1;
    while(caseId <= T)
    {
        scanf("%d", &sizeA);
        for(int i = 0; i < sizeA; i++)
                scanf("%d", &arrA[i]);
        scanf("%d", &sizeB);
        for(int i = 0; i < sizeB; i++)
                scanf("%d", &arrB[i]);

        buildBipartiteGraph(adjList, arrA, sizeA, arrB, sizeB);

        // This is a minimum vertex cover problem!
        // In a bipartite graph, size of minimum vertex cover = size of maximum matching
        printf("Case %d: %d\n", caseId, getMaximumNumberOfMatching(adjList, sizeA));
        caseId++;
    }

    return 0;
}

void buildBipartiteGraph(vector<vector<int> > & adjList, int arrA[], int sizeA, int arrB[], int sizeB)
{
    vector<int> emptyList;
    adjList.assign(sizeA + sizeB, emptyList);

    // Two bipartite sets are the set A and B respectively
    // For a in A, b in B, there is an edge a -> b if b is a multiple of a, i.e.
    //              b % a == 0
    // Special case: 0 is a multiple of 0.
    //               0 is NOT a multiple of a for a != 0
    for(int indA = 0; indA < sizeA; indA++)
        for(int indB = 0; indB < sizeB; indB++)
        {
            if(arrA[indA] == 0)
            {
                if(arrB[indB] == 0)
                    adjList[indA].push_back(indB + sizeA);
            }
            else
            {
                if(arrB[indB] % arrA[indA] == 0)
                    adjList[indA].push_back(indB + sizeA);
            }
        }
}

int getMaximumNumberOfMatching(const vector<vector<int> > & adjList, int sizeLeftSet)
{
    int numV = (int) adjList.size();

    vector<int> matchedLeftPartner(numV, -1);
    vector<bool> visited;

    int numMatching = 0;
    for(int v = 0; v < sizeLeftSet; v++)
    {
        visited.assign(sizeLeftSet, false);
        if(findAndAugmentPath(adjList, v, matchedLeftPartner, visited))
            numMatching++;
    }

    return numMatching;
}

bool findAndAugmentPath(const vector<vector<int> > & adjList, int leftVertex,
                        vector<int> & matchedLeftPartner, vector<bool> & visited)
{
    if(visited[leftVertex])
        return false;

    visited[leftVertex] = true;

    int rightV;
    for(int ind = 0; ind < (int) adjList[leftVertex].size(); ind++)
    {
        rightV = adjList[leftVertex][ind];

        if(matchedLeftPartner[rightV] == -1 || findAndAugmentPath(adjList, matchedLeftPartner[rightV],
                                                                  matchedLeftPartner, visited))
        {
            matchedLeftPartner[rightV] = leftVertex;
            return true;
        }
    }

    return false;
}
