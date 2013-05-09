#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

void getTopoOrder(const vector<vector<int> > & adjList, vector<int> & topoOrder);
void getInDegree(const vector<vector<int> > & adjLIst, vector<int> & inDegree);

int main(void)
{
    int numV, numE, vOne, vTwo;
    vector<vector<int> > adjList;
    vector<int> emptyList, topoOrder;

   // freopen("in.txt", "r", stdin);

    while(1)
    {
        scanf("%d %d", &numV, &numE);
        if(numV == 0 && numE == 0)
            break;

        adjList.assign(numV, emptyList);

        for(int e = 0; e < numE; e++)
        {
            scanf("%d %d", &vOne, &vTwo);
            adjList[vOne - 1].push_back(vTwo - 1);
        }

        getTopoOrder(adjList, topoOrder);

        printf("%d", topoOrder[0] + 1);
        for(int v = 1; v < (int) topoOrder.size(); v++)
            printf(" %d", topoOrder[v] + 1);
        printf("\n");

    }
    return 0;
}

void getTopoOrder(const vector<vector<int> > & adjList, vector<int> & topoOrder)
{
    topoOrder.clear();

    int numV = (int) adjList.size();
    vector<int> inDegree;

    getInDegree(adjList, inDegree);

    int v, nextV;
    queue<int> vQueue;
    for(v = 0; v < numV; v++)
        if(!inDegree[v])
            vQueue.push(v);

    while(!vQueue.empty())
    {
        v = vQueue.front();
        vQueue.pop();

        topoOrder.push_back(v);

        for(int ind = 0; ind < (int) adjList[v].size(); ind++)
        {
            nextV = adjList[v][ind];
            inDegree[nextV]--;
            if(!inDegree[nextV])
                vQueue.push(nextV);
        }
    }
}

void getInDegree(const vector<vector<int> > & adjList, vector<int> & inDegree)
{
    int v, ind, neighborV, numV = (int) adjList.size();

    inDegree.assign(numV, 0);

    for(v = 0; v < numV; v++)
        for(ind = 0; ind < (int) adjList[v].size(); ind++)
        {
            neighborV = adjList[v][ind];
            inDegree[neighborV]++;
        }
}
