#include <cstdio>

using namespace std;

#define MAX_NUM_POINT 1000

typedef struct {
    int _dist, _weight;
} PickupPoint;

int simulateAndComputeDistCover(PickupPoint pickupArr[], int numPoint, int maxWeight);

int main(void)
{
    PickupPoint pickupArr[MAX_NUM_POINT];
    int numPoint, T, maxWeight;

    scanf("%d", &T);
    while(T)
    {
        scanf("%d %d", &maxWeight, &numPoint);

        for(int i = 0; i < numPoint; i++)
            scanf("%d %d", &pickupArr[i]._dist, &pickupArr[i]._weight);

        printf("%d\n", simulateAndComputeDistCover(pickupArr, numPoint, maxWeight));

        T--;
    }
    return 0;
}

int simulateAndComputeDistCover(PickupPoint pickupArr[], int numPoint, int maxWeight)
{
    int numDist = 0, curWeight = 0;

    // Go to the first location
    numDist = pickupArr[0]._dist;

    for(int i = 0; i < numPoint; i++)
    {
        // Take the garbage at this point
        if(curWeight + pickupArr[i]._weight <= maxWeight)
        {
            curWeight = curWeight + pickupArr[i]._weight;
        }
        else
        {
            // Overload. Go back to the dump, empty content and back to this point
            numDist += (pickupArr[i]._dist << 1);
            curWeight = pickupArr[i]._weight;
        }

        // If it is full. Go back to the dump, empty content and back to this point
        if(curWeight == maxWeight)
        {
            numDist += pickupArr[i]._dist;
            if(i != numPoint - 1)
                // Go back to this pickup
                numDist += pickupArr[i]._dist;
            else
                break;
            curWeight = 0;
        }

        // Go to the next pickup
        if(i != numPoint - 1)
            numDist += (pickupArr[i + 1]._dist - pickupArr[i]._dist);
        else
            // Return
            numDist += pickupArr[i]._dist;
    }

    return numDist;
}
