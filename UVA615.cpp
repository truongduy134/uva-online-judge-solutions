#include <cstdio>
#include <map>
#include <vector>
#include <queue>

using namespace std;

bool isTree(const vector<vector<int> > & adjList, int numV, int numE);
bool isConnected(const vector<vector<int> > & adjList);
bool readInputAndBuildGraph(vector<vector<int> > & adjList, int *numV, int *numE);

int main(void)
{
    int caseId, numV, numE;
    vector<vector<int> > adjList;

  //  freopen("in.txt", "r", stdin);

    caseId = 1;
    while(readInputAndBuildGraph(adjList, &numV, &numE))
    {
        if(isTree(adjList, numV, numE))
            printf("Case %d is a tree.\n", caseId);
        else
            printf("Case %d is not a tree.\n", caseId);

        caseId++;
    }

    return 0;
}

bool readInputAndBuildGraph(vector<vector<int> > & adjList, int *numV, int *numE)
{
    vector<int> emptyList;
    map<int, int> mapValueToVertexId;
    map<int, int>::iterator itOne, itTwo;
    int valOne, valTwo, idOne, idTwo, vId;

    adjList.clear();
    vId = 0;
    *numE = 0;

    while(1)
    {
        scanf("%d %d", &valOne, &valTwo);
        if(valOne < 0 && valTwo < 0)
            return false;
        if(valOne == 0 && valTwo == 0)
            break;
        (*numE)++;

        itOne = mapValueToVertexId.find(valOne);
        if(itOne == mapValueToVertexId.end())
        {
            idOne = vId;
            vId++;
            mapValueToVertexId[valOne] = idOne;
        }
        else
            idOne = itOne->second;

        itTwo = mapValueToVertexId.find(valTwo);
        if(itTwo == mapValueToVertexId.end())
        {
            idTwo = vId;
            vId++;
            mapValueToVertexId[valTwo] = idTwo;
        }
        else
            idTwo = itTwo->second;

        if(idOne >= (int) adjList.size())
            adjList.push_back(emptyList);
        if(idTwo >= (int) adjList.size())
            adjList.push_back(emptyList);
        adjList[idOne].push_back(idTwo);
        if(idOne != idTwo)
            adjList[idTwo].push_back(idOne);
    }
    *numV = vId;

    return true;
}
bool isTree(const vector<vector<int> > & adjList, int numV, int numE)
{
    if(adjList.size() == 0)
        return true;

    if(numE != numV - 1)
        return false;

    if(!isConnected(adjList))
        return false;

    return true;
}

bool isConnected(const vector<vector<int> > & adjList)
{
    int numV = (int) adjList.size(), thisV, nextV;
    queue<int> vQueue;
    vector<bool> visited(numV, false);

    visited[0] = true;
    vQueue.push(0);

    while(!vQueue.empty())
    {
        thisV = vQueue.front();
        vQueue.pop();

        for(int ind = 0; ind < (int) adjList[thisV].size(); ind++)
        {
            nextV = adjList[thisV][ind];
            if(!visited[nextV])
            {
                visited[nextV] = true;
                vQueue.push(nextV);
            }
        }
    }

    for(int ind = 0; ind < numV; ind++)
        if(!visited[ind])
            return false;
    return true;
}
