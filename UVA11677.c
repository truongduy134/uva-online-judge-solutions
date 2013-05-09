#include <stdio.h>

const int NUM_MINUTE_PER_HOUR  = 60;
const int NUM_MINUTE_PER_DAY = 60 * 24;

typedef struct
{
    int hour, minute;
} HourMinute;

int getMinute(HourMinute * obj);
int getMinuteDiff(HourMinute * startTime, HourMinute * endTime);

int main(void)
{
    HourMinute startTime, endTime;

    while(1)
    {
        scanf("%d %d %d %d", &startTime.hour, &startTime.minute, &endTime.hour, &endTime.minute);

        if(startTime.hour == 0 && startTime.minute == 0 && endTime.hour == 0 && endTime.minute == 0)
            break;

        printf("%d\n", getMinuteDiff(&startTime, &endTime));
    }
    return 0;
}

int getMinute(HourMinute * obj)
{
    return NUM_MINUTE_PER_HOUR * obj->hour + obj->minute;
}

int getMinuteDiff(HourMinute * startTime, HourMinute * endTime)
{
    if(startTime == NULL || endTime == NULL)
        return -1;

    int startMinute = getMinute(startTime);
    int endMinute = getMinute(endTime);

    int diff = endMinute - startMinute;
    if(diff < 0)
        /* So endTime and startTime are on two different days */
        diff += NUM_MINUTE_PER_DAY;

    return diff;
}

