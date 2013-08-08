/*******************************************************
 * Author: Nguyen Truong Duy
 *******************************************************/

/* Methodology:
 *  + Use an array of n + 1 bits (or boolean variables) (where n + 1 <= 10^6).
 *  + For each time interval [a, b],
 *      - Set bit a to be 1
 *      - For bit i (i is from a + 1 to min(n, b)), first check if bit i is already set.
 *        If so, we have detected a collision. Otherwise, set bit i to be 1.
 *  + Time complexity: O(n) (note that each bit is set at most twice, and is queried at most twice)
 */

#include <cstdio>
#include <bitset>

using namespace std;

const int MAX_SIZE = 1000001;

bool checkCollisionAndMarkInterval(bitset<MAX_SIZE> & bitMap, int mStart, int mEnd);
bool checkCollisionAndMarkRepeatedInterval(bitset<MAX_SIZE> & bitMap, int mStart, int mEnd, int period);

int main(void)
{
    bitset<MAX_SIZE> bitMap;
    int numNormal, numRepeated, mStart, mEnd, period;

    while(1)
    {
        scanf("%d %d", &numNormal, &numRepeated);
        if(numNormal == 0 && numRepeated == 0)
            break;

        bitMap.reset();

        bool noConflict = true;
        // Read and check normal interval
        for(int i = 0; i < numNormal; i++)
        {
            scanf("%d %d", &mStart, &mEnd);

            if(noConflict)
                noConflict = checkCollisionAndMarkInterval(bitMap, mStart, mEnd);
        }
        for(int i = 0; i < numRepeated; i++)
        {
            scanf("%d %d %d", &mStart, &mEnd, &period);

            if(noConflict)
                noConflict = checkCollisionAndMarkRepeatedInterval(bitMap, mStart, mEnd, period);
        }

        if(noConflict)
            printf("NO CONFLICT\n");
        else
            printf("CONFLICT\n");
    }
    return 0;
}

// Assumption: [mStart, mEnd] is a valid interval (i.e. mStart <= mEnd)
//           and mStart <= mEnd < MAX_SIZE
bool checkCollisionAndMarkInterval(bitset<MAX_SIZE> & bitMap, int mStart, int mEnd)
{
    if(mStart > mEnd)
        return true;
    if(mEnd >= MAX_SIZE)
        mEnd = MAX_SIZE - 1;

    for(int i = mStart + 1; i <= mEnd; i++)
        if(bitMap[i])
        {
            // Collision
            return false;
        }
        else
            bitMap[i] = 1;

    return true;
}

bool checkCollisionAndMarkRepeatedInterval(bitset<MAX_SIZE> & bitMap, int mStart, int mEnd, int period)
{
    if(mStart > mEnd)
        return true;

    while(mStart < MAX_SIZE)
    {
        if(mEnd >= MAX_SIZE)
            mEnd = MAX_SIZE - 1;

        bool noConflict = checkCollisionAndMarkInterval(bitMap, mStart, mEnd);
        if(!noConflict)
            return false;

        mStart += period;
        mEnd += period;
    }

    return true;
}
