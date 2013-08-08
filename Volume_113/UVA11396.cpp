#include <cstdio>
#include <vector>
using namespace std;

#define UNVISITED 0
#define COLOR_ONE 1
#define COLOR_TWO 2

bool isTwoColorable(vector<vector<int> > & adjList, vector<int> & stateArr, int v, int color)
{
    stateArr[v] = color;

    int nextColor = COLOR_ONE;
    if(color == COLOR_ONE)
        nextColor = COLOR_TWO;
    int u;

    bool flagTwoColor = true;
    for(int i = 0; i < (int) adjList[v].size() && flagTwoColor; i++)
    {
        u = adjList[v][i];
        if(stateArr[u] == UNVISITED)
            flagTwoColor = flagTwoColor && isTwoColorable(adjList, stateArr, u, nextColor);
        else
        {
            if(stateArr[u] != nextColor)
                flagTwoColor = false;
        }
    }

    return flagTwoColor;
}
bool canDecomposeIntoClaw(vector<vector<int> > & adjList)
{
    vector<int> stateArr(adjList.size(), UNVISITED);

    // Because in the given graph, all vertices have degree 3.
    return isTwoColorable(adjList, stateArr, 0, COLOR_ONE);
}

int main(void)
{
    int numV, v1, v2;
    vector<vector<int> > adjList;
    vector<int> initList;

   // freopen("in.txt", "r", stdin);
    while(1)
    {
        scanf("%d", &numV);
        if(numV == 0)
            break;

        adjList.assign(numV, initList);
        while(1)
        {
            scanf("%d %d", &v1, &v2);
            if(v1 == 0 && v2 == 0)
                break;
            v1--;
            v2--;
            adjList[v1].push_back(v2);
            adjList[v2].push_back(v1);
        }

        if(canDecomposeIntoClaw(adjList))
            printf("YES\n");
        else
            printf("NO\n");
    }

    return 0;
}
