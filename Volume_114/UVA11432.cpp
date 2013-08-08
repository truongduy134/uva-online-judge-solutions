#include <cstdio>
//#include <iostream>

using namespace std;

#define MAX_VALUE 33

unsigned long long memoTable[MAX_VALUE + 1][MAX_VALUE + 1][2][2];
unsigned long long memoResult[MAX_VALUE + 1][MAX_VALUE + 1];

unsigned long long countNumSchedule(int numEachJob, int numConsecutive, int numJobOne, int numJobTwo,
                     int thisJobId, int firstDayJobId)
{
    if(numJobOne == numEachJob && numJobTwo == numEachJob)
    {
        if(thisJobId != firstDayJobId)
            return 0;
        return 1;
    }
    if(memoTable[numJobOne][numJobTwo][thisJobId][firstDayJobId] != (unsigned long long) (-1))
        return memoTable[numJobOne][numJobTwo][thisJobId][firstDayJobId];

    long long numWay = 0;
    int maxConsecutive;

    if(thisJobId == 0)
    {
        maxConsecutive = numEachJob - numJobOne;
        if(numJobTwo != numEachJob)
        {
            if(numConsecutive < maxConsecutive)
                maxConsecutive = numConsecutive;
        }
    }
    else
    {
        maxConsecutive = numEachJob - numJobTwo;
        if(numJobOne != numEachJob)
        {
            if(numConsecutive < maxConsecutive)
                maxConsecutive = numConsecutive;
        }
    }

    for(int i = 1; i <= maxConsecutive; i++)
    {
        if(thisJobId == 0)
            numWay += countNumSchedule(numEachJob, numConsecutive, numJobOne + i, numJobTwo, (thisJobId + 1) % 2, firstDayJobId);
        else
            numWay += countNumSchedule(numEachJob, numConsecutive, numJobOne, numJobTwo + i, (thisJobId + 1) % 2, firstDayJobId);
    }
    memoTable[numJobOne][numJobTwo][thisJobId][firstDayJobId] = numWay;

    return numWay;
}
int main(void)
{
    int caseId, D, G;

   // freopen("in.txt", "r", stdin);
   // freopen("out.txt", "w", stdout);

    caseId = 1;

    for(int i = 0; i <= MAX_VALUE; i++)
        for(int j = 0; j <= MAX_VALUE; j++)
            if(i == 0 || j == 0)
                memoResult[i][j] = 0;
            else
            {
                memoResult[i][j] = -1;
            }


    while(1)
    {
        scanf("%d %d", &D, &G);
        if(D < 0 && G < 0)
            break;

        if(memoResult[D][G] == (unsigned long long) (-1))
        {
            for(int i1 = 0; i1 <= D; i1++)
                for(int i2 = 0; i2 <= D; i2++)
                    for(int i3 = 0; i3 < 2; i3++)
                        for(int i4 = 0; i4 < 2; i4++)
                            memoTable[i1][i2][i3][i4] = (unsigned long long) (-1);

            memoResult[D][G] = countNumSchedule(D, G, 0, 0, 0, 0) + countNumSchedule(D, G, 0, 0, 1, 1);
        }
        //cout << "Case " << caseId << ": " << memoResult[D][G] << endl;
       printf("Case %d: %llu\n", caseId, memoResult[D][G]);
        caseId++;
    }

    return 0;
}
