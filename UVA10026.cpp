#include <cstdio>
#include <algorithm>

using namespace std;

class Job
{
private:
	// Attributes
	int _jobId, _daysToComplete, _delayCostPerDay;

public:
	// Constructor
	Job() : _jobId(0), _daysToComplete(0), _delayCostPerDay(0) {}
	Job(int jobId, int daysToComplete, int delayCostPerDay) : _jobId(jobId), _daysToComplete(daysToComplete), _delayCostPerDay(delayCostPerDay) {}
	Job(const Job & another) : _jobId(another._jobId), _daysToComplete(another._daysToComplete), _delayCostPerDay(another._delayCostPerDay) {}
	~Job() {}

	Job & operator= (const Job & another);
	int getJobId() const { return _jobId; }

friend bool compareJobForSorting(const Job & jobOne, const Job & jobTwo);
};

Job & Job::operator= (const Job & another)
{
	if(this == &another)
		return *this;

	_jobId = another._jobId;
	_daysToComplete = another._daysToComplete;
	_delayCostPerDay = another._delayCostPerDay;

	return *this;
}

// jobOne < jobTwo if doing jobOne first incurs less cost than doing jobTwo first.
// If the two costs are the same, jobOne < jobTwo if its id is less than jobTwo's id.
bool compareJobForSorting(const Job & jobOne, const Job & jobTwo)
{
	int costDoOne = jobOne._daysToComplete * jobTwo._delayCostPerDay, 
	    costDoTwo = jobTwo._daysToComplete * jobOne._delayCostPerDay;

	if(costDoOne < costDoTwo)
		return true;
	if(costDoOne > costDoTwo)
		return false;

	return jobOne._jobId < jobTwo._jobId;
}

#define MAX_NUM_JOB 1000
int main(void)
{
	int T, numJob, daysToComplete, delayCostPerDay;
	Job jobArr[MAX_NUM_JOB];

	scanf("%d", &T);

	while(T)
	{
		scanf("%d", &numJob);

		for(int jobId = 1; jobId <= numJob; jobId++)
		{
			scanf("%d %d", &daysToComplete, &delayCostPerDay);

			jobArr[jobId - 1] = Job(jobId, daysToComplete, delayCostPerDay);
		}

		sort(jobArr, jobArr + numJob, compareJobForSorting);

		printf("%d", jobArr[0].getJobId());
		for(int ind = 1; ind < numJob; ind++)
			printf(" %d", jobArr[ind].getJobId());
		printf("\n");

		if(T != 1)
			printf("\n");
		T--;
	}
	return 0;
}

