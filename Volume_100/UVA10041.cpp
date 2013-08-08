#include <cstdio>
#include <algorithm>

using namespace std;

#define MAX_NUM 505
#define ABS(X) (X >= 0 ? X : -(X))

int main(void)
{
    int numPeople, streetNoArr[MAX_NUM], T, sumDist, chosenNoInd;

  //  freopen("in.txt", "r", stdin);

    scanf("%d", &T);
    while(T)
    {
        sumDist = 0;

        scanf("%d", &numPeople);
        for(int i = 0; i < numPeople; i++)
            scanf("%d", &streetNoArr[i]);

        sort(streetNoArr, streetNoArr + numPeople);

        chosenNoInd = numPeople >> 1;

        for(int i = 0; i < numPeople; i++)
        {
            sumDist += ABS(streetNoArr[i] - streetNoArr[chosenNoInd]);
        }

        printf("%d\n", sumDist);

        T--;
    }
    return 0;
}
