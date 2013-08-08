#include <cstdio>
#include <map>
#include <vector>
#include <algorithm>
#include <string>
#include <queue>

using namespace std;

#define MAX_LEN 60

void getTopoOrder(const vector<vector<int> > & adjList, vector<int> & topoOrder)
{
    int numV = (int) adjList.size();
    vector<int> inDegreeArr(numV, 0);

    // Caculate in-degree
    for(int u = 0; u < numV; u++)
        for(int i = 0; i < (int) adjList[u].size(); i++)
            inDegreeArr[adjList[u][i]]++;

    int v, nextV;
    priority_queue<int, vector<int>, greater<int> > vQueue;

    for(int i = 0; i < numV; i++)
        if(inDegreeArr[i] == 0)
            vQueue.push(i);

    while(!vQueue.empty())
    {
        v = vQueue.top();
        vQueue.pop();

        topoOrder.push_back(v);

        for(int i = 0; i < (int) adjList[v].size(); i++)
        {
            nextV = adjList[v][i];
            inDegreeArr[nextV]--;
            if(inDegreeArr[nextV] == 0)
                vQueue.push(nextV);
        }
    }
}
int main(void)
{
    char drinkName[MAX_LEN], drinkOne[MAX_LEN], drinkTwo[MAX_LEN];
    int numBeverage, numEdge, caseId;
    map<string, int> mapDrinkToId;
    vector<string> mapIdToDrink;
    vector<vector<int> > adjList;
    vector<int> initList, topoOrder;

  //  freopen("in.txt", "r", stdin);
  //  freopen("out.txt", "w", stdout);

    caseId = 1;
    while(scanf("%d", &numBeverage) > 0)
    {
        mapDrinkToId.clear();
        mapIdToDrink.clear();
        topoOrder.clear();
        adjList.assign(numBeverage, initList);

        for(int i = 0; i < numBeverage; i++)
        {
            scanf("%s", drinkName);
            mapIdToDrink.push_back(drinkName);
            mapDrinkToId[drinkName] = i;
        }

        scanf("%d", &numEdge);
        for(int i = 0; i < numEdge; i++)
        {
            scanf("%s %s", drinkOne, drinkTwo);
            adjList[mapDrinkToId[drinkOne]].push_back(mapDrinkToId[drinkTwo]);
        }

        for(int i = 0; i < numBeverage; i++)
            sort(adjList[i].begin(), adjList[i].end());

        getTopoOrder(adjList, topoOrder);

        printf("Case #%d: Dilbert should drink beverages in this order:", caseId);
        for(int i = 0; i < numBeverage; i++)
            printf(" %s", mapIdToDrink[topoOrder[i]].c_str());
        printf(".\n\n");

        caseId++;
    }
    return 0;
}
