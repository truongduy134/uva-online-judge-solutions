#include <cstdio>
#include <map>
#include <vector>
#include <string>
#include <queue>

using namespace std;

#define MAX_LEN 5

int updateRecord(char cityName[], map<string, int> & mapNameToId, vector<string> & mapIdToName,
                 vector<vector<int> > & adjList, int *id);
void breathFirstSearch(const vector<vector<int> > & adjList, int src, int dest, vector<int> & parentArr);
void printPath(int src, int dest, const vector<int> & parentArr, const vector<string> & mapIdToName);

int main(void)
{
    vector<string> mapIdToName;
    map<string, int> mapNameToId;
    vector<vector<int> > adjList;
    char cityOne[MAX_LEN + 1], cityTwo[MAX_LEN + 1];
    int numLink, id, idOne, idTwo;
    bool isFirst = true, existPath;
    map<string, int>::iterator itOne, itTwo;
    vector<int> parentArr;

    //freopen("in.txt", "r", stdin);

    while(scanf("%d", &numLink) > 0)
    {
            id = 0;
            mapIdToName.clear();
            mapNameToId.clear();
            adjList.clear();

            for(int i = 0; i < numLink; i++)
            {
                scanf("%s %s", cityOne, cityTwo);

                idOne = updateRecord(cityOne, mapNameToId, mapIdToName, adjList, &id);
                idTwo = updateRecord(cityTwo, mapNameToId, mapIdToName, adjList, &id);

                adjList[idOne].push_back(idTwo);
                adjList[idTwo].push_back(idOne);
            }

            scanf("%s %s", cityOne, cityTwo);
            itOne = mapNameToId.find(cityOne);
            itTwo = mapNameToId.find(cityTwo);
            existPath = true;
            if(itOne == mapNameToId.end() || itTwo == mapNameToId.end())
                existPath = false;
            else
            {
                breathFirstSearch(adjList, itOne->second, itTwo->second, parentArr);

                if(parentArr[itTwo->second] < 0)
                    existPath = false;
            }

            if(isFirst)
            {
                isFirst = false;
            }
            else
                printf("\n");
            if(existPath)
            {
                printPath(itOne->second, itTwo->second, parentArr, mapIdToName);
            }
            else
                printf("No route\n");
    }

    return 0;
}

int updateRecord(char cityName[], map<string, int> & mapNameToId, vector<string> & mapIdToName,
                 vector<vector<int> > & adjList, int *id)
{
    vector<int> emptyList;
    int assignId;
    map<string, int>::iterator it = mapNameToId.find(cityName);

    if(it == mapNameToId.end())
    {
        assignId = *id;
        mapNameToId[cityName] = assignId;
        *id = *id + 1;
        mapIdToName.push_back(cityName);
        adjList.push_back(emptyList);
        return assignId;
    }

    return it->second;

}

void breathFirstSearch(const vector<vector<int> > & adjList, int src, int dest, vector<int> & parentArr)
{
    int numV = (int) adjList.size();

    parentArr.assign(numV, -1);
    parentArr[src] = src;

    queue<int> vQueue;
    vQueue.push(src);

    int v, nextV;
    while(!vQueue.empty())
    {
        v = vQueue.front();
        vQueue.pop();

        for(int ind = 0; ind < (int) adjList[v].size(); ind++)
        {
            nextV = adjList[v][ind];

            if(parentArr[nextV] < 0)
            {
                parentArr[nextV] = v;
                vQueue.push(nextV);
            }
        }
    }
}

void printPath(int src, int dest, const vector<int> & parentArr, const vector<string> & mapIdToName)
{
    if(dest == src)
        return;

    int parent = parentArr[dest];
    printPath(src, parent, parentArr, mapIdToName);
    printf("%s %s\n", mapIdToName[parent].c_str(), mapIdToName[dest].c_str());
}
