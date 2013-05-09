#include <stdio.h>

#define MAX_SIZE 100000

int getMaxDiffBetwenSeniorAndJunior(int markArr[], int accumulateMin[], int numStudent);
void computeAccumulateMin(int markArr[], int accumulateMin[], int numStudent);

int main(void)
{
	int markArr[MAX_SIZE], accumulateMin[MAX_SIZE], T, numStudent, i;

	scanf("%d", &T);
	while(T)
	{
		scanf("%d", &numStudent);

		for(i = 0; i < numStudent; i++)
			scanf("%d", &markArr[i]);

		computeAccumulateMin(markArr, accumulateMin, numStudent);

		printf("%d\n", getMaxDiffBetwenSeniorAndJunior(markArr, accumulateMin, numStudent));
		T--;
	}
	return 0;
}

/* accumulateMin[i] = min { markArr[i], ..., markArr[numStudent - 1] } */
void computeAccumulateMin(int markArr[], int accumulateMin[], int numStudent)
{
	int i;

	accumulateMin[numStudent - 1] = markArr[numStudent - 1];
	for(i = numStudent - 2; i >= 0; i--)
	{
		accumulateMin[i] = markArr[i];
		if(markArr[i] > accumulateMin[i + 1])
			accumulateMin[i] = accumulateMin[i + 1];
	}
		
}

int getMaxDiffBetwenSeniorAndJunior(int markArr[], int accumulateMin[], int numStudent)
{
	int i, maxDiff, diff;

	maxDiff = markArr[0] - accumulateMin[1];

	for(i = 1; i < numStudent - 1; i++)
	{
		diff = markArr[i] - accumulateMin[i + 1];
		if(diff > maxDiff)
			maxDiff = diff;
	}

	return maxDiff;
		
}
