#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

bool isConnect(const vector<vector<int> > & adjList)
{
    int numV = (int) adjList.size(), anotherV;

    if(numV == 0)
        return true;

    vector<bool> visited(numV, false);
    queue<int> bfsQueue;

    bfsQueue.push(0);

    while(!bfsQueue.empty())
    {
        anotherV = bfsQueue.front();
        bfsQueue.pop();
        visited[anotherV] = true;

        for(int i = 0; i < (int) adjList[anotherV].size(); i++)
            if(!visited[adjList[anotherV][i]])
            bfsQueue.push(adjList[anotherV][i]);
    }

    for(int i = 0; i < numV; i++)
        if(!visited[i])
            return false;

    return true;
}

bool isEulerian(const vector<vector<int> > & adjList)
{
    for(int i = 0; i < (int) adjList.size(); i++)
        if(adjList[i].size() & 1)
            return false;

    return isConnect(adjList);
}

int main(void)
{
    int numV, numE, u, v;
    vector<vector<int> > adjList;

  //  freopen("in.txt", "r", stdin);

    while(scanf("%d %d", &numV, &numE) > 0)
    {
        adjList.clear();

        for(int i = 0; i < numV; i++)
        {
            vector<int> neighborList;
            adjList.push_back(neighborList);
        }

        for(int i = 0; i < numE; i++)
        {
            scanf("%d %d", &u, &v);
            adjList[u].push_back(v);
            adjList[v].push_back(u);
        }

        if(isEulerian(adjList))
            printf("Possible\n");
        else
            printf("Not Possible\n");
    }

    return 0;
}
