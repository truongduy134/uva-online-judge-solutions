#include <stdio.h>

#define MAX_WEEK 13

int satisfyCapacity(int capacity[], int lenArr, int numPeople);

int main()
{
    int numPeople, budget, numHotel, numWeek, priceHotel, capacity[MAX_WEEK], index, minCost, totalPrice;


    while(scanf("%d %d %d %d", &numPeople, &budget, &numHotel, &numWeek) == 4)
    {
        minCost = budget + 1;
        while(numHotel > 0)
        {
            /* Read price and capacity of the hotel */
            scanf("%d", &priceHotel);
            for(index = 0; index < numWeek; index++)
                scanf("%d", &capacity[index]);

            if(satisfyCapacity(capacity, numWeek, numPeople))
            {
                totalPrice = numPeople * priceHotel;
                if(totalPrice < minCost)
                    minCost = totalPrice;
            }
            numHotel--;
        }

        if(minCost > budget)
            printf("stay home\n");
        else
            printf("%d\n", minCost);
    }
    return 0;
}

int satisfyCapacity(int capacity[], int lenArr, int numPeople)
{
    int index;

    for(index = 0; index < lenArr; index++)
        if(capacity[index] >= numPeople)
            return 1;

    return 0;
}
