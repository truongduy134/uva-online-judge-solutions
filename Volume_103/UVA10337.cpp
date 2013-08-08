#include <cstdio>

using namespace std;

#define MAX_ZONE 2000
#define MAX_HEIGHT 10
#define CLIMB_FUEL 60
#define HOLDING_FUEL 30
#define SINKING_FUEL 20
#define INFINITY 100000000

int findMinFuelDP(int windStrength[][MAX_ZONE], int memoTable[][MAX_ZONE], int numZone, int curZone, int curHeight)
{
    if(curHeight < 0 || curHeight >= MAX_HEIGHT || curZone > numZone)
        return INFINITY;
    if(curZone == numZone && curHeight != 0)
        return INFINITY;
    if(curZone == numZone && curHeight == 0)
        return 0;           // Destination

    if(memoTable[curHeight][curZone] >= 0)
        return memoTable[curHeight][curZone];


    int minFuel = INFINITY, numFuel;
    // Try climbing
    numFuel = CLIMB_FUEL - windStrength[curHeight][curZone] + findMinFuelDP(windStrength, memoTable, numZone, curZone + 1, curHeight + 1);
    if(numFuel < minFuel)
        minFuel = numFuel;
    // Try holding altitude
    numFuel = HOLDING_FUEL - windStrength[curHeight][curZone] + findMinFuelDP(windStrength, memoTable, numZone, curZone + 1, curHeight);
    if(numFuel < minFuel)
        minFuel = numFuel;
    // Try sinking
    numFuel = SINKING_FUEL - windStrength[curHeight][curZone] + findMinFuelDP(windStrength, memoTable, numZone, curZone + 1, curHeight - 1);
    if(numFuel < minFuel)
        minFuel = numFuel;

    memoTable[curHeight][curZone] = minFuel;

    return minFuel;
}
int main(void)
{
    int T, distance, numZone, windStrength[MAX_HEIGHT][MAX_ZONE], memoTable[MAX_HEIGHT][MAX_ZONE], minFuel;

    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);

    scanf("%d", &T);


    while(T)
    {
        scanf("%d", &distance);
        numZone = distance / 100;

        for(int i = MAX_HEIGHT - 1; i >= 0; i--)
            for(int j = 0; j < numZone; j++)
                scanf("%d", &windStrength[i][j]);

        // Initialize the memo-table
        for(int i = 0; i < MAX_HEIGHT; i++)
            for(int j = 0; j < numZone; j++)
                memoTable[i][j] = -1;

        minFuel = findMinFuelDP(windStrength, memoTable, numZone, 0, 0);

        printf("%d\n\n", minFuel);
        T--;
    }
    return 0;

}
