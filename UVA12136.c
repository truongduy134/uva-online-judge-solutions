#include <stdio.h>

const int NUM_MINUTE_IN_HOUR = 60;

typedef struct
{
	int startTimeMinute, endTimeMinute;	
} TimePeriod;

void initTimePeriod(TimePeriod *obj, int startHour, int startMin, int endHour, int endMin)
{
	obj->startTimeMinute = startHour * NUM_MINUTE_IN_HOUR + startMin;
	obj->endTimeMinute = endHour * NUM_MINUTE_IN_HOUR + endMin;
}

int areOverlapping(TimePeriod *one, TimePeriod *two)
{
	if(one->endTimeMinute < two->startTimeMinute)
		return 0;
	if(one->startTimeMinute > two->endTimeMinute)
		return 0;

	return 1;
}
int main(void)
{
	int T, caseId, startHr, startMin, endHr, endMin;
	TimePeriod wifeTime, meetingTime;

	scanf("%d", &T);
	caseId = 1;
	while(caseId <= T)
	{
		scanf("%d:%d %d:%d", &startHr, &startMin, &endHr, &endMin);
		initTimePeriod(&wifeTime, startHr, startMin, endHr, endMin);

		scanf("%d:%d %d:%d", &startHr, &startMin, &endHr, &endMin);
		initTimePeriod(&meetingTime, startHr, startMin, endHr, endMin);

		if(areOverlapping(&wifeTime, &meetingTime))
			printf("Case %d: Mrs Meeting\n", caseId);
		else
			printf("Case %d: Hits Meeting\n", caseId);

		caseId++;
	}
	return 0;
}
