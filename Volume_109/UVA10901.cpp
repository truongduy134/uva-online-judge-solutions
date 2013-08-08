#include <cstdio>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

int main(void)
{
 //   freopen("in.txt", "r", stdin);
 //   freopen("out.txt", "w", stdout);

    int numTest, numStation, cargoCap, queueCap;
    scanf("%d", &numTest);
    while(numTest)
    {
        // Reading input
        scanf("%d %d %d", &numStation, &cargoCap, &queueCap);

        vector<queue<int> > queueList(numStation);
        for(int i = 0; i < numStation; i++)
        {
            queue<int> stationQueue;
            queueList.push_back(stationQueue);
        }

        int queueSize, cargoDest, numCargoLeft = 0;
        for(int i = 0; i < numStation; i++)
        {
            scanf("%d", &queueSize);
            numCargoLeft += queueSize;
            for(int j = 0; j < queueSize; j++)
            {
                scanf("%d", &cargoDest);
                // Careful: 0 and 1-indexing
                queueList[i].push(cargoDest - 1);
            }
        }

        // Simulate
        int time = 0, topCargo, station = 0;
        stack<int> cargoTruck;

        while(1)
        {
            // Unload
            bool fail = false;
            while(!cargoTruck.empty() && !fail)
            {
                topCargo = cargoTruck.top();

                if(topCargo == station)
                {
                    cargoTruck.pop();
                    numCargoLeft--;
                    time++;
                }
                else
                {
                    if(queueList[station].size() < queueCap)
                    {
                        cargoTruck.pop();
                        queueList[station].push(topCargo);
                        time++;
                    }
                    else
                        fail = true;
                }
            }

            // Load
            while(cargoTruck.size() < cargoCap && !queueList[station].empty())
            {
                time++;
                cargoTruck.push(queueList[station].front());
                queueList[station].pop();
            }


            if(numCargoLeft)
            {
                // Move to the next station
                time += 2;
                station++;
                if(station == numStation)
                    station = 0;
            }
            else
                break;
        }

        printf("%d\n", time);
        numTest--;
    }
    return 0;
}
