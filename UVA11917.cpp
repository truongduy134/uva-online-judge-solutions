#include <cstdio>
#include <map>
#include <string>

using namespace std;

#define MAX_LEN 30
#define NUM_DAY_LATE_ALLOWED 5
int main(void)
{
    char subject[MAX_LEN + 1];
    map<string, int> mapSubjectToDay;
    int duration, T, caseId, numSubject, numDayFin;
    map<string, int>::const_iterator it;

    scanf("%d", &T);
    caseId = 1;

    while(caseId <= T)
    {
        mapSubjectToDay.clear();

        scanf("%d", &numSubject);
        for(int i = 0; i < numSubject; i++)
        {
            scanf("%s %d", subject, &duration);
            mapSubjectToDay[subject] = duration;
        }

        scanf("%d %s", &duration, subject);
        it = mapSubjectToDay.find(subject);

        printf("Case %d: ", caseId);
        if(it == mapSubjectToDay.end())
            printf("Do your own homework!\n");
        else
        {
            numDayFin = it->second;
            if(numDayFin <= duration)
                printf("Yesss\n");
            else
            {
                if(numDayFin <= duration + NUM_DAY_LATE_ALLOWED)
                    printf("Late\n");
                else
                    printf("Do your own homework!\n");
            }
        }
        caseId++;
    }
    return 0;
}
