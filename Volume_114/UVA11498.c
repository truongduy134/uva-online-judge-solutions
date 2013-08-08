#include <stdio.h>

enum REGION {
    NE, NO, SE, SO, DIVISA
};

typedef struct {
    int xCoord, yCoord;
} Location;

enum REGION determineRegion(const Location * queryPoint, const Location * divisionPoint);

int main(void)
{
    Location divisionPoint, queryPoint;
    int numQuery, query;

    while(1)
    {
        scanf("%d", &numQuery);
        if(numQuery == 0)
            break;

        scanf("%d %d", &divisionPoint.xCoord, &divisionPoint.yCoord);
        for(query = 0; query < numQuery; query++)
        {
            scanf("%d %d", &queryPoint.xCoord, &queryPoint.yCoord);

            switch(determineRegion(&queryPoint, &divisionPoint))
            {
                case NE:
                    printf("NE\n");
                    break;
                case NO:
                    printf("NO\n");
                    break;
                case SE:
                    printf("SE\n");
                    break;
                case SO:
                    printf("SO\n");
                    break;
                default:
                    printf("divisa\n");
            }
        }
    }

    return 0;
}

enum REGION determineRegion(const Location * queryPoint, const Location * divisionPoint)
{
    if(queryPoint->xCoord == divisionPoint->xCoord ||
       queryPoint->yCoord == divisionPoint->yCoord)
        return DIVISA;

    if(queryPoint->xCoord > divisionPoint->xCoord)
    {
        /* NE or SE */
        if(queryPoint->yCoord > divisionPoint->yCoord)
            return NE;
        return SE;
    }

    /* NO or SO */
    if(queryPoint->yCoord > divisionPoint->yCoord)
        return NO;
    return SO;
};
