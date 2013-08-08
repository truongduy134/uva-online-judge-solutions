#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

#define MAX_SIZE 10000
#define MAX_NUM_COURSE 101

int main(void)
{
    int nCourse, nType, courseArr[MAX_NUM_COURSE], sieveMinRequire[MAX_NUM_COURSE],
        sieveType[MAX_NUM_COURSE], nCoursePerType, course;
    vector<int> mapCourseToType[MAX_SIZE];
    bool pass;

 //  freopen("in.txt", "r", stdin);

    while(1)
    {
        for(int i = 0; i < MAX_SIZE; i++)
            mapCourseToType[i].clear();
        memset(sieveType, 0, MAX_NUM_COURSE * sizeof(int));
        memset(sieveMinRequire, 0, MAX_NUM_COURSE * sizeof(int));

        scanf("%d", &nCourse);
        if(nCourse == 0)
            break;
        scanf("%d", &nType);

        for(int i = 0; i < nCourse; i++)
            scanf("%d", &courseArr[i]);

        for(int i = 0; i < nType; i++)
        {
            scanf("%d", &nCoursePerType);
            scanf("%d", &sieveMinRequire[i]);

            for(int j = 0; j < nCoursePerType; j++)
            {
                scanf("%d", &course);
                mapCourseToType[course].push_back(i);
            }
        }

        for(int i = 0; i < nCourse; i++)
            for(int j = 0; j < (int) mapCourseToType[courseArr[i]].size(); j++)
                sieveType[mapCourseToType[courseArr[i]][j]]++;

        pass = true;
        for(int i = 0; i < nType; i++)
            if(sieveType[i] < sieveMinRequire[i])
            {
                pass = false;
                break;
            }

        if(pass)
            printf("yes\n");
        else
            printf("no\n");
    }

    return 0;
}
