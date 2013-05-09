#include <cstdio>
#include <map>
#include <string>
#include <cstring>

using namespace std;

#define MAX_NUM_V 200
#define MAX_LEN_NAME 30

int getId(char name[], map<string, int> & mapNameToId, int * nextIdToAssign);
void findMaximumLoadBetweenAllPairs(int maxLoadMat[][MAX_NUM_V], int numV);
int getMin(int a, int b);

int main(void)
{
    int maxLoadMat[MAX_NUM_V][MAX_NUM_V], numV, numE, caseId, nextIdToAssign,
        v1, v2, weight;
    map<string, int> mapNameToId;
    char name[MAX_LEN_NAME + 1];

    //freopen("in.txt", "r", stdin);

    caseId = 1;
    while(1)
    {
        scanf("%d %d", &numV, &numE);
        if(numV == 0 && numE == 0)
            break;

        mapNameToId.clear();
        nextIdToAssign = 0;
        memset(maxLoadMat, 0, MAX_NUM_V * MAX_NUM_V * sizeof(int));

        for(int e = 0; e < numE; e++)
        {
            scanf("%s", name);
            v1 = getId(name, mapNameToId, &nextIdToAssign);
            scanf("%s", name);
            v2 = getId(name, mapNameToId, &nextIdToAssign);
            scanf("%d", &weight);
            maxLoadMat[v1][v2] = weight;
            maxLoadMat[v2][v1] = weight;
        }

        findMaximumLoadBetweenAllPairs(maxLoadMat, numV);

        scanf("%s", name);
        v1 = getId(name, mapNameToId, &nextIdToAssign);
        scanf("%s", name);
        v2 = getId(name, mapNameToId, &nextIdToAssign);

        if(v1 < numV && v2 < numV)
        {
            printf("Scenario #%d\n%d tons\n\n", caseId, maxLoadMat[v1][v2]);
        }

        caseId++;
    }
    return 0;
}

int getId(char name[], map<string, int> & mapNameToId, int * nextIdToAssign)
{
    map<string, int>::iterator it = mapNameToId.find(name);
    int returnId;

    if(it == mapNameToId.end())
    {
        returnId = *nextIdToAssign;
        mapNameToId[name] = *nextIdToAssign;
        (*nextIdToAssign)++;
    }
    else
        returnId = it->second;

    return returnId;
}

// This is a maxi-min problem. We use Floy-Warshall's Algorithm
void findMaximumLoadBetweenAllPairs(int maxLoadMat[][MAX_NUM_V], int numV)
{
    int u, v, k, load;

    for(k = 0; k < numV; k++)
        for(u = 0; u < numV; u++)
            for(v = 0; v < numV; v++)
            {
                if(maxLoadMat[u][k] && maxLoadMat[k][v])
                {
                    load = getMin(maxLoadMat[u][k], maxLoadMat[k][v]);
                    if(load > maxLoadMat[u][v])
                        maxLoadMat[u][v] = load;
                }
            }
}

int getMin(int a, int b)
{
    if(a > b)
        return b;
    return a;
}
