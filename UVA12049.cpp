#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

#define MAX_SIZE 10000

int findIntersectionSizeOfMultisets(int setOne[], int sizeOne, int setTwo[], int sizeTwo);

int main(void)
{
    int T, sizeOne, sizeTwo, setOne[MAX_SIZE], setTwo[MAX_SIZE], intersectSize;

    scanf("%d", &T);
    while(T)
    {
        scanf("%d %d", &sizeOne, &sizeTwo);

        for(int i = 0; i < sizeOne; i++)
            scanf("%d", &setOne[i]);
        for(int i = 0; i < sizeTwo; i++)
            scanf("%d", &setTwo[i]);

        intersectSize = findIntersectionSizeOfMultisets(setOne, sizeOne, setTwo, sizeTwo);

        printf("%d\n", sizeOne + sizeTwo - (intersectSize << 1));

        T--;
    }
    return 0;
}

int findIntersectionSizeOfMultisets(int setOne[], int sizeOne, int setTwo[], int sizeTwo)
{
    sort(setOne, setOne + sizeOne);
    sort(setTwo, setTwo + sizeTwo);

    int indOne = 0, indTwo = 0, numCommon = 0;

    while(indOne < sizeOne && indTwo < sizeTwo)
    {
        if(setOne[indOne] == setTwo[indTwo])
        {
            numCommon++;
            indOne++;
            indTwo++;
        }
        else
        {
            if(setOne[indOne] < setTwo[indTwo])
                indOne++;
            else
                indTwo++;
        }
    }

    return numCommon;
}
