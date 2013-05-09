#include <iostream>
#include <vector>
#include <utility>
//#include <cstdio>

using namespace std;

class Date
{
    friend istream & operator>>(istream & inStream, Date &obj);
    friend ostream & operator<<(ostream & outStream, const Date &obj);
private:
    int _day, _month, _year;
public:
    Date();
    ~Date();
    Date(int day, int month, int year);
    Date(const Date & date);
    bool isLeapYear() const;
    Date getNextDate() const;
    int getDay() const;
    int getMonth() const;
    int getYear() const;
    void setDay(int day);
    void setMonth(int month);
    void setYear(int year);
    bool operator==(const Date &date) const;
};

int Date::getDay() const
{
    return _day;
}

int Date::getMonth() const
{
    return _month;
}

int Date::getYear() const
{
    return _year;
}

void Date::setDay(int day)
{
    _day = day;
}

void Date::setMonth(int month)
{
    _month = month;
}

void Date::setYear(int year)
{
    _year = year;
}

Date::Date(): _day(0), _month(0), _year(0)
{
}

Date::~Date()
{
}

Date::Date(int day, int month, int year): _day(day), _month(month), _year(year)
{
}

Date::Date(const Date &date): _day(date.getDay()), _month(date.getMonth()), _year(date.getYear())
{
}

bool Date::operator==(const Date &date) const
{
    if(_day == date.getDay() && _month == date.getMonth() && _year == date.getYear())
        return true;
    return false;
}

bool Date::isLeapYear() const
{
    if(_year % 400 == 0)
        return true;
    if(_year % 100 == 0)
        return false;
    if(_year % 4)
        return false;

    return true;
}

Date Date::getNextDate() const
{
    const int DAY_IN_MONTH[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    int day = _day, month = _month, year = _year;

    day++;
    if(month == 2 && isLeapYear())
    {
        if(day > 29)
        {
            day = 1;
            month++;
        }
    }
    else
    {
        if(day > DAY_IN_MONTH[month])
        {
            day = 1;
            month++;
        }
    }

    if(month > 12)
    {
        month = 1;
        year++;
    }

    return Date(day, month, year);
}

istream & operator>>(istream & inStream, Date &obj)
{
    inStream >> obj._day >> obj._month >> obj._year;

    return inStream;
}

ostream & operator<<(ostream & outStream, const Date &obj)
{
    outStream << obj._day << "/" << obj._month << "/" << obj._year << endl;

    return outStream;
}

int main(void)
{
    int numMeasure, KW;
    Date date;

   // freopen("in.txt", "r", stdin);
   // freopen("out.txt", "w", stdout);

    while(true)
    {
        cin >> numMeasure;

        if(numMeasure == 0)
            break;

        vector<pair<Date, int> > measureVector(numMeasure);

        for(int index = 0; index < numMeasure; index++)
        {
            cin >> date >> KW;
            measureVector[index] = make_pair(date, KW);
        }

        int numExact = 0, totalKW = 0;
        for(int index = 0; index < numMeasure - 1; index++)
        {
            Date nextDay = measureVector[index].first.getNextDate();
            if(nextDay == measureVector[index + 1].first)
            {
                numExact++;
                totalKW += measureVector[index + 1].second - measureVector[index].second;

            }
        }

        cout << numExact << " " << totalKW << endl;
    }

    return 0;
}
