#include <cstdio>
#include <algorithm>

using namespace std;

#define MAX_DIFF 200
#define DESTINATION 1422
#define MAX_SIZE 500000

bool canDriveToAndFro(int arr[], int mSize);

int main(void)
{
    int mSize, location[MAX_SIZE + 1], i;

    //freopen("in.txt", "r", stdin);
    while(1)
    {
        scanf("%d", &mSize);
        if(mSize == 0)
            break;

        for(i = 0; i < mSize; i++)
            scanf("%d", &location[i]);

        sort(location, location + mSize);

        if(canDriveToAndFro(location, mSize))
            printf("POSSIBLE\n");
        else
            printf("IMPOSSIBLE\n");
    }
    return 0;
}

bool canDriveToAndFro(int location[], int mSize)
{
    for(int i = 0; i < mSize - 1; i++)
    {
        if(location[i + 1] - location[i] > MAX_DIFF)
            return false;
    }

    if(DESTINATION - location[mSize - 1] > MAX_DIFF)
            return false;

    if(location[mSize - 1] != DESTINATION &&
       (DESTINATION - location[mSize - 1]) * 2 > MAX_DIFF)
            return false;

    return true;
}
