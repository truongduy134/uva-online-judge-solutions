#include <cstdio>

using namespace std;

#define MAX 2000

int main()
{
   // freopen("in.txt", "r", stdin);
   // freopen("out.txt", "w", stdout);

    int arr[MAX], sizeArr, index, numZero, numNonZero, caseId = 0;

    while(1)
    {
        caseId++;

        scanf("%d", &sizeArr);
        if(!sizeArr)
            break;

        numNonZero = 0;
        for(index = 0; index < sizeArr; index++)
            scanf("%d", &arr[index]);

        for(index = 0; index < sizeArr; index++)
            if(arr[index])
                numNonZero++;
        numZero = sizeArr - numNonZero;
        printf("Case %d: %d\n", caseId, numNonZero - numZero);
    }
}
