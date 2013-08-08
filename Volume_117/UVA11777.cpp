/*******************************************************
 * Author: Nguyen Truong Duy
 *******************************************************/

#include <cstdio>
#include <algorithm>

using namespace std;

const int NUM_MARK = 7;
const int NUM_KIND_CA = 5;
const double CEIL_F = 60;
const double CEIL_D = 70;
const double CEIL_C = 80;
const double CEIL_B = 90;

char getCourseGrade(double markArr[]);

int main(void)
{
        double markArr[NUM_MARK];
        int T, caseId;

        scanf("%d", &T);
        caseId = 1;
        while(caseId <= T)
        {
            for(int i = 0; i < NUM_MARK; i++)
                scanf("%lf", &markArr[i]);

            printf("Case %d: %c\n", caseId, getCourseGrade(markArr));
            caseId++;
        }
        return 0;
}

char getCourseGrade(double markArr[])
{
    sort(markArr + NUM_MARK - 3, markArr + NUM_MARK);

    double averageTest = (markArr[NUM_MARK - 1] + markArr[NUM_MARK - 2]) * 0.5;

    double totalMark = 0;
    for(int i = 0; i < NUM_KIND_CA - 1; i++)
        totalMark += markArr[i];
    totalMark += averageTest;

    if(totalMark < CEIL_F)
        return 'F';
    if(totalMark < CEIL_D)
        return 'D';
    if(totalMark < CEIL_C)
        return 'C';
    if(totalMark < CEIL_B)
        return 'B';
    return 'A';
}
