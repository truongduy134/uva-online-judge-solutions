#include <stdio.h>

#define MAX_NUM_HOLE 1005

struct Point_s
{
    double xCoord, yCoord;
};

typedef struct Point_s Point;

double calculateSquareDist(Point A, Point B)
{
    return (A.xCoord - B.xCoord) * (A.xCoord - B.xCoord) +
           (A.yCoord - B.yCoord) * (A.yCoord - B.yCoord);
}

int canEscape(Point gopherPoint, Point dogPoint, Point holePoint)
{
    double squareGopherDist = calculateSquareDist(gopherPoint, holePoint);
    double squareDogDist = calculateSquareDist(dogPoint, holePoint);

    if(4 * squareGopherDist > squareDogDist)
        return 0;
    return 1;
}

int main(void)
{
    int numHole, chosenInd, i;
    Point dogPoint, gopherPoint, holePointArr[MAX_NUM_HOLE];

    while(scanf("%d", &numHole) > 0)
    {
        scanf("%lf %lf %lf %lf", &gopherPoint.xCoord, &gopherPoint.yCoord, &dogPoint.xCoord, &dogPoint.yCoord);
        for(i = 0; i < numHole; i++)
            scanf("%lf %lf", &holePointArr[i].xCoord, &holePointArr[i].yCoord);

        chosenInd = -1;
        for(i = 0; i < numHole; i++)
            if(canEscape(gopherPoint, dogPoint, holePointArr[i]))
            {
                chosenInd = i;
                break;
            }

        if(chosenInd < 0)
            printf("The gopher cannot escape.\n");
        else
            printf("The gopher can escape through the hole at (%.3lf,%.3lf).\n",
                   holePointArr[chosenInd].xCoord, holePointArr[chosenInd].yCoord);
    }

    return 0;
}
