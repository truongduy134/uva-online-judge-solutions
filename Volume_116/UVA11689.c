#include <stdio.h>

int main(void)
{
    int T, numEmptyOwn, numEmptyFound, numToBuyNew, numDrinkTotal, numEmpty,
           numNewExchange;

    scanf("%d", &T);
    while(T)
    {
        scanf("%d %d %d", &numEmptyOwn, &numEmptyFound, &numToBuyNew);

        numDrinkTotal = 0;
        numEmpty = numEmptyOwn + numEmptyFound;

        while(numEmpty >= numToBuyNew)
        {
            numNewExchange = numEmpty / numToBuyNew;
            numEmpty = numEmpty % numToBuyNew;

            /* Drink */
            numDrinkTotal += numNewExchange;

            /* Those that has previously exchanged becomes empty */
            numEmpty += numNewExchange;
        }

        printf("%d\n", numDrinkTotal);
        T--;
    }

    return 0;
}
