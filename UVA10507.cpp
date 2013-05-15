/********************************************************************************
 * Author: Nguyen Truong Duy
 ********************************************************************************/
#include <cstdio>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

#define NUM_DIRECT_WAKE_UP 3
#define MAX_LEN 10
#define MAX_NUM_ALPHA 26
#define NUM_TO_WAKE_UP 3

/* Methodology:
 *	+ This problem can be solved using the technique similar to Breadth-First Search.
 *	+ For each sleeping area, we keep track of the following information:
 *		+ The number of its neighbors that have waken up.
 *	+ We maintain a queue of waken-up area and the year they wake up.
 *	+ While the queue is not empty:
 *		+ Pop the front element A of the queue.
 *		+ For each sleeping neighbor B of this element A, we update the above piece of information.
		+ If the number of neigbors of B that have waken up is equal to NUM_TO_WAKE_UP = 3, we push its to the queue with its waking time.
 *	+ In the end, if the total of waking up area is not equal to sleeping area, the brain does not wake up.
 *	+ Otherwise, return the latest waking up year among all areas
 */
int determineWhenToWakeUp(const vector<vector<int> > & adjList, int numSleepArea, int wakeAreas[]);

int main(void)
{
	int numSleepArea, wakeAreas[NUM_DIRECT_WAKE_UP], numE, yearToWakeUp;
	vector<vector<int> > adjList;
	vector<int> emptyList;
	char str[MAX_LEN + 1];

	while(scanf("%d", &numSleepArea) > 0)
	{
		adjList.assign(MAX_NUM_ALPHA, emptyList);

		scanf("%d", &numE);
		scanf("%s", str);

		for(int i = 0; i < NUM_DIRECT_WAKE_UP; i++)
			wakeAreas[i] = (int) str[i] - 'A';

		for(int i = 0; i < numE; i++)
		{
			scanf("%s", str);
			adjList[(int) str[0] - 'A'].push_back((int) str[1] - 'A');
			adjList[(int) str[1] - 'A'].push_back((int) str[0] - 'A');
		}

		yearToWakeUp = determineWhenToWakeUp(adjList, numSleepArea, wakeAreas);
		if(yearToWakeUp < 0)
			printf("THIS BRAIN NEVER WAKES UP\n");
		else
			printf("WAKE UP IN, %d, YEARS\n", yearToWakeUp);
	}
	return 0;
}

int determineWhenToWakeUp(const vector<vector<int> > & adjList, int numSleepArea, int wakeAreas[])
{
	vector<int> numNeighborWakeUp(MAX_NUM_ALPHA, 0);
	vector<bool> areaWakeUpStatus(MAX_NUM_ALPHA, false);
	queue<pair<int, int> > wakeUpQueue;

	int numWakeUp = 0, latestWakeUpYear = 0;
	for(int i = 0; i < NUM_DIRECT_WAKE_UP; i++)
	{
		areaWakeUpStatus[wakeAreas[i]] = true;
		wakeUpQueue.push(pair<int, int> (wakeAreas[i], 0));
	}

	int areaId, year, neighborId;
	while(!wakeUpQueue.empty())
	{
		areaId = wakeUpQueue.front().first;
		year = wakeUpQueue.front().second;
		wakeUpQueue.pop();

		if(year > latestWakeUpYear)
			latestWakeUpYear = year;

		numWakeUp++;

		for(int i = 0; i < (int) adjList[areaId].size(); i++)
		{
			neighborId = adjList[areaId][i];

			if(areaWakeUpStatus[neighborId] == false)
			{
				numNeighborWakeUp[neighborId]++;

				if(numNeighborWakeUp[neighborId] == NUM_TO_WAKE_UP)
				{
					areaWakeUpStatus[neighborId] = true;
					wakeUpQueue.push(pair<int, int> (neighborId, year + 1));
				}
			}
		}	
	}

	if(numWakeUp != numSleepArea)
		return -1;
	return latestWakeUpYear;
}
