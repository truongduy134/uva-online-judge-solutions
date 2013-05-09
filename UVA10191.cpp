#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
#define NUM_MINUTE_IN_HOUR 60

class TimePoint {
private:
    int _hour, _minute;
public:
    TimePoint() : _hour(0), _minute(0) {}
    TimePoint(int hour, int minute) : _hour(hour), _minute(minute) {}
    TimePoint(const TimePoint & another) : _hour(another._hour), _minute(another._minute) {}
    ~TimePoint() {}

    int convertToMinute() const;
    void getTimePointFromMinute(int minute);
    int getTimeDiffInMinute(const TimePoint &another) const;
    bool operator< (const TimePoint & another) const;
    TimePoint & operator= (const TimePoint & another);
    int getHour() const {return _hour;}
    int getMinute() const {return _minute;}
};

inline int TimePoint::convertToMinute() const
{
    return _hour * NUM_MINUTE_IN_HOUR + _minute;
}

void TimePoint::getTimePointFromMinute(int minute)
{
    _hour = minute / NUM_MINUTE_IN_HOUR;
    _minute = minute % NUM_MINUTE_IN_HOUR;
}

TimePoint & TimePoint::operator= (const TimePoint & another)
{
    _hour = another._hour;
    _minute = another._minute;

    return *this;
}

int TimePoint::getTimeDiffInMinute(const TimePoint &another) const
{
    int diff = convertToMinute() - another.convertToMinute();
    if(diff < 0)
        diff = -diff;
    return diff;
}

inline bool TimePoint::operator< (const TimePoint & another) const
{
    return convertToMinute() < another.convertToMinute();
}

class TimePeriod {
private:
    TimePoint _startP, _endP;

public:
    TimePeriod() : _startP(TimePoint()), _endP(TimePoint()) {}
    TimePeriod(const TimePoint & startP, const TimePoint & endP);
    TimePeriod(const TimePeriod & another) : _startP(another._startP), _endP(another._endP) {}
    ~TimePeriod() {}

    bool operator< (const TimePeriod & another) const;
    int getDistanceInMinute(const TimePeriod & another) const;
    const TimePoint & getStartP() const {return _startP;}
    const TimePoint & getEndP() const {return _endP;}
};

TimePeriod::TimePeriod(const TimePoint & startP, const TimePoint & endP)
{
    if(startP < endP)
    {
        _startP = startP;
        _endP = endP;
    }
    else
    {
        _startP = endP;
        _endP = startP;
    }
}

bool TimePeriod::operator< (const TimePeriod & another) const
{
    if(_startP < another._startP)
        return true;

    if(another._startP < _startP)
        return false;

    return _endP < another._endP;
}

inline int TimePeriod::getDistanceInMinute(const TimePeriod & another) const
{
    return _endP.getTimeDiffInMinute(another._startP);
}

#define MAX_LEN 500
int main(void)
{
    int caseId, numEvent, hour, minute, diff;
    vector<TimePeriod> events;
    char desc[MAX_LEN + 1];
    int maxInd, maxMinute;

    TimePoint endP(18, 0);
    TimePoint startP(10, 0);
    TimePeriod endPeriod(endP, endP);
    TimePeriod startPeriod(startP, startP);

    //freopen("in.txt", "r", stdin);

    caseId = 1;
    while(scanf("%d", &numEvent) > 0)
    {
        gets(desc);

        events.clear();
        events.push_back(startPeriod);

        for(int i = 0; i < numEvent; i++)
        {
            scanf("%d:%d", &hour, &minute);
            TimePoint mStart(hour, minute);
            scanf("%d:%d", &hour, &minute);
            TimePoint mEnd(hour, minute);
            events.push_back(TimePeriod(mStart, mEnd));

            gets(desc);
        }

        events.push_back(endPeriod);
        numEvent += 2;

        sort(events.begin(), events.end());

        maxInd = 0;
        maxMinute = 0;
        for(int i = 0; i < numEvent - 1; i++)
        {
            diff = events[i].getDistanceInMinute(events[i + 1]);
            if(diff > maxMinute)
            {
                maxMinute = diff;
                maxInd = i;
            }
        }

        TimePoint result;
        result.getTimePointFromMinute(maxMinute);
        printf("Day #%d: the longest nap starts at %d:%02d and will last for ", caseId,
               events[maxInd].getEndP().getHour(), events[maxInd].getEndP().getMinute());
        if(result.getHour() != 0)
            printf("%d hours and ", result.getHour());
        printf("%d minutes.\n", result.getMinute());

        caseId++;
    }
    return 0;
}
