#include <cstdio>
#include <queue>
#include <utility>
#include <vector>
#include <cstring>

using namespace std;

#define INIT_ENERGY 100

bool canReach(const vector<vector<int> > & adjList, const vector<int> & roomEnergy,
              int startR, int initEnergy, int endR, int maxEnergyNeeded);

int main(void)
{
    int numRoom, numNeighbor, neighbor, negativeEnergy;
    vector<int> roomEnergy, emptyList;
    vector<vector<int> > adjList;

 //   freopen("in.txt", "r", stdin);

    while(1)
    {
        scanf("%d", &numRoom);
        if(numRoom < 0)
            break;

        roomEnergy.assign(numRoom, 0);
        adjList.assign(numRoom, emptyList);
        negativeEnergy = 0;

        for(int room = 0; room < numRoom; room++)
        {
            scanf("%d %d", &roomEnergy[room], &numNeighbor);

            if(roomEnergy[room] < 0)
                negativeEnergy -= roomEnergy[room];

            for(int i = 0; i < numNeighbor; i++)
            {
                scanf("%d", &neighbor);
                adjList[room].push_back(neighbor - 1);
            }
        }

        if(canReach(adjList, roomEnergy, 0, INIT_ENERGY, numRoom - 1, negativeEnergy))
            printf("winnable\n");
        else
            printf("hopeless\n");
    }

    return 0;
}

bool canReach(const vector<vector<int> > & adjList, const vector<int> & roomEnergy,
              int startR, int initEnergy, int endR, int totalNegativeEnergy)
{
    int maxEnergyNeeded = totalNegativeEnergy + 1;
    if(initEnergy > maxEnergyNeeded)
        initEnergy = maxEnergyNeeded;

    queue<pair<int, int> > vQueue;

    int numV = (int) adjList.size();
    bool visited[numV][maxEnergyNeeded + 2];

    memset((bool *) visited, false, numV * (maxEnergyNeeded + 2) * sizeof(bool));

    vQueue.push(make_pair(startR, initEnergy));
    visited[startR][initEnergy] = true;

    pair<int, int> state;
    int curR, energy, nextR, nextEnergy;
    while(!vQueue.empty())
    {
        state = vQueue.front();
        curR = state.first;
        energy = state.second;
        vQueue.pop();

        if(curR == endR)
            return true;

        for(int i = 0; i < (int) adjList[curR].size(); i++)
        {
            nextR = adjList[curR][i];
            nextEnergy = energy + roomEnergy[nextR];
            if(nextEnergy > 5 * maxEnergyNeeded)
                nextEnergy = maxEnergyNeeded;

            if(nextEnergy > 0 && visited[nextR][nextEnergy] == false)
            {
                visited[nextR][nextEnergy] = true;
                vQueue.push(make_pair(nextR, nextEnergy));
            }
        }
    }

    return false;
}
