#include <cstdio>
#include <algorithm>

using namespace std;

#define MAX_PARTY 200
#define NUM_DAY 4000

int main(void)
{
    int T, N, P, hartal[MAX_PARTY], lostWorkDay[NUM_DAY], startD, numLostDay;

  //  freopen("in.txt", "r", stdin);

    scanf("%d", &T);
    while(T)
    {
        scanf("%d", &N);
        fill(lostWorkDay, lostWorkDay + N + 1, 0);

        scanf("%d", &P);
        for(int i = 0; i < P; i++)
            scanf("%d", &hartal[i]);

        for(int i = 0; i < P; i++)
        {
            startD = hartal[i];

            do
            {
                if(startD % 7 != 0 && startD % 7 != 6)
                    lostWorkDay[startD] = 1;
                startD += hartal[i];
            } while(startD <= N);
        }

        numLostDay = 0;
        for(int i = 1; i <= N; i++)
            numLostDay += lostWorkDay[i];

        printf("%d\n", numLostDay);
        T--;
    }
    return 0;
}
