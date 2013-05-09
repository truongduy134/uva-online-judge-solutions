#include <stdio.h>
#include <string.h>

#define MAX_SIZE 71
#define NOT_PROCESSED -1

int getNumMarkDistribution(int numSubject, int totalMark, int minToPass, int memoTable[][MAX_SIZE][MAX_SIZE]);

int main(void)
{
	int memoTable[MAX_SIZE][MAX_SIZE][MAX_SIZE], numCase,
		numSubject, totalMark, minToPass;

	memset(memoTable, NOT_PROCESSED, MAX_SIZE * MAX_SIZE * MAX_SIZE * sizeof(int));

	scanf("%d", &numCase);
	while(numCase)
	{
		scanf("%d %d %d", &numSubject, &totalMark, &minToPass);

		printf("%d\n", getNumMarkDistribution(numSubject, totalMark, minToPass, memoTable));

		numCase--;
	}
	return 0;
}

int getNumMarkDistribution(int numSubject, int totalMark, int minToPass, int memoTable[][MAX_SIZE][MAX_SIZE])
{
	if(totalMark < 0)
		return 0;

	if(numSubject == 0)
	{
		if(totalMark == 0)
			return 1;
		return 0;
	}

	if(memoTable[numSubject][totalMark][minToPass] != NOT_PROCESSED)
		return memoTable[numSubject][totalMark][minToPass];

	int numWay = 0, mark;
	for(mark = minToPass; mark <= totalMark; mark++)
		numWay += getNumMarkDistribution(numSubject - 1, totalMark - mark, minToPass, memoTable);

	memoTable[numSubject][totalMark][minToPass] = numWay;

	return numWay;
}
