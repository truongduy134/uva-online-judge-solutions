#include <stdio.h>

#define MAX_SIZE 100

int findMax(int arr[], int len);
int main()
{
    int numTest, curCase, numStudent, speedArr[MAX_SIZE], index;

    scanf("%d", &numTest);
    curCase = 1;

    while(curCase <= numTest)
    {
        scanf("%d", &numStudent);

        for(index = 0; index < numStudent; index++)
            scanf("%d", &speedArr[index]);

        printf("Case %d: %d\n", curCase, findMax(speedArr, numStudent));
        curCase++;
    }
    return 0;
}

int findMax(int arr[], int len)
{
    int index;

    int max = arr[0];
    for(index = 1; index < len; index++)
        if(arr[index] > max)
            max = arr[index];

    return max;
}
