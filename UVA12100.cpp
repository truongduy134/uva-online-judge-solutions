#include <cstdio>
#include <queue>
#include <utility>
#include <cstring>
#include <algorithm>

using namespace std;

#define NUM_PRIORITY 9
#define TIME_TO_PRINT 1

int computeTimeToPrintJob(int myJobId, queue<pair<int, int> > & jobQueue, int prioritySieve[]);

int main(void)
{
	queue<pair<int, int> > jobQueue;
	int myJob, prioritySieve[NUM_PRIORITY + 1], T, numJob, priority;

	scanf("%d", &T);
	while(T)
	{
		queue<pair<int, int> > emptyQueue;
		swap(jobQueue, emptyQueue);
		memset(prioritySieve, 0, (NUM_PRIORITY + 1) * sizeof(int));

		scanf("%d %d", &numJob, &myJob);
		for(int id = 0; id < numJob; id++)
		{
			scanf("%d", &priority);
			jobQueue.push(pair<int, int> (id, priority) );
			prioritySieve[priority]++;
		}

		printf("%d\n", computeTimeToPrintJob(myJob, jobQueue, prioritySieve));
		T--;
	}

	return 0;
}

// Simulation
int computeTimeToPrintJob(int myJobId, queue<pair<int, int> > & jobQueue, int prioritySieve[])
{
	int printTime = 0, highestPriorityInQueue = NUM_PRIORITY;
	
	while(prioritySieve[highestPriorityInQueue] == 0)
		highestPriorityInQueue--;

	pair<int, int> curJob;
	int jobId, priority;

	while(1)
	{
		curJob = jobQueue.front();
		jobQueue.pop();

		jobId = curJob.first;
		priority = curJob.second;
		
		if(priority == highestPriorityInQueue)
		{
			// Print
			printTime += TIME_TO_PRINT;
			if(jobId == myJobId)
				return printTime;

			prioritySieve[highestPriorityInQueue]--;
			while(prioritySieve[highestPriorityInQueue] == 0)
				highestPriorityInQueue--;
		}
		else
			jobQueue.push(curJob);
	}
}
