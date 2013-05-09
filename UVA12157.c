#include <stdio.h>

const char MILE_PLAN[] = "Mile";
const char JUICE_PLAN[] = "Juice";
const int MILE_RATE = 10;
const int MILE_UNIT_TIME = 30;
const int JUICE_RATE = 15;
const int JUICE_UNIT_TIME = 60;
const int MILE_TYPE = 0;
const int JUICE_TYPE = 1;
const int MAX_NUM_CALL = 20;

int getCallCharge(int duration, int packageType);

int main(void)
{
	int numCall, durations[MAX_NUM_CALL], T, caseId, i, mileCost, juiceCost;

	scanf("%d", &T);
	caseId = 1;

	while(caseId <= T)
	{
		scanf("%d", &numCall);
		for(i = 0; i < numCall; i++)
			scanf("%d", &durations[i]);

		mileCost = 0;
		juiceCost = 0;
		for(i = 0; i < numCall; i++)
		{
			mileCost += getCallCharge(durations[i], MILE_TYPE);
			juiceCost += getCallCharge(durations[i], JUICE_TYPE);
		}

		printf("Case %d: ", caseId);
		if(mileCost < juiceCost)
			printf("%s %d\n", MILE_PLAN, mileCost);
		else
		{
			if(mileCost > juiceCost)
				printf("%s %d\n", JUICE_PLAN, juiceCost);
			else
				printf("%s %s %d\n", MILE_PLAN, JUICE_PLAN, juiceCost);
		}
		caseId++;
	}
	return 0;
}

int getCallCharge(int duration, int packageType)
{
	int rate, unitTime, numUnit;

	if(packageType == MILE_TYPE)
	{
		rate = MILE_RATE;
		unitTime = MILE_UNIT_TIME;
	}
	else
	{
		rate = JUICE_RATE;
		unitTime = JUICE_UNIT_TIME;
	}

	numUnit = duration / unitTime + 1;

	return rate * numUnit;
}
