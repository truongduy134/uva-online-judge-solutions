#include <cstdio>
#include <queue>
#include <vector>

using namespace std;

#define MAX_LEN 20

int countMaximalConnectedSubgraph(const vector<vector<int> > & adjList);
void breathFirstSearch(const vector<vector<int> > & adjList, int v, vector<bool> & visited);

int main(void)
{
    vector<vector<int> > adjList;
    vector<int> emptyList;
    char line[MAX_LEN + 1], trash[MAX_LEN + 1];
    int T, vOne, vTwo, numV;

 //   freopen("in.txt", "r", stdin);

    scanf("%d", &T);
    gets(trash);
    gets(trash);
    while(T)
    {
        gets(line);
        numV = line[0] - 'A' + 1;

        adjList.assign(numV, emptyList);
        while(gets(line) != NULL && line[0] != '\0')
        {
            vOne = line[0] - 'A';
            vTwo = line[1] - 'A';
            adjList[vOne].push_back(vTwo);
            adjList[vTwo].push_back(vOne);
        }

        printf("%d\n", countMaximalConnectedSubgraph(adjList));
        if(T != 1)
            printf("\n");
        T--;
    }

    return 0;
}

int countMaximalConnectedSubgraph(const vector<vector<int> > & adjList)
{
    int numV = (int) adjList.size();
    vector<bool> visited(numV, false);

    int numMaximalConnectedSubgraph = 0;

    for(int v = 0; v < numV; v++)
        if(!visited[v])
        {
            numMaximalConnectedSubgraph++;
            breathFirstSearch(adjList, v, visited);
        }

    return numMaximalConnectedSubgraph;
}

void breathFirstSearch(const vector<vector<int> > & adjList, int v, vector<bool> & visited)
{
    queue<int> vQueue;
    vQueue.push(v);
    visited[v] = true;

    while(!vQueue.empty())
    {
        int curV = vQueue.front();
        vQueue.pop();

        for(int i = 0; i < (int) adjList[curV].size(); i++)
        {
            int nextV = adjList[curV][i];

            if(!visited[nextV])
            {
                visited[nextV] = true;
                vQueue.push(nextV);
            }
        }
    }
}
