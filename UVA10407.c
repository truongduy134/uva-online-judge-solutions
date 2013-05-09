#include <stdio.h>

/* We want to find the largest integer N such that
 *      a(i) % N are the same (for i = 1, 2, ..., n).
 *
 * It can be proved that
 *      N = gcd(|a(j) - a(1)|) for j = 2, ..., n
 */

#define MAX_SIZE 2000

int gcdOfArr(int arr[], int mSize);
int gcd(int a, int b);

int main(void)
{
    int arr[MAX_SIZE], diffArr[MAX_SIZE], num, mSize, i;

    while(1)
    {
        mSize = 0;
        scanf("%d", &num);
        if(num == 0)
            break;

        do
        {
            arr[mSize] = num;
            mSize++;
            scanf("%d", &num);
        } while(num != 0);

        for(i = 1; i < mSize; i++)
        {
            diffArr[i - 1] = arr[i] - arr[0];
            if(diffArr[i - 1] < 0)
                diffArr[i - 1] = -diffArr[i - 1];
        }

        printf("%d\n", gcdOfArr(diffArr, mSize - 1));
    }
    return 0;
}

int gcdOfArr(int arr[], int mSize)
{
    if(mSize == 1)
        return arr[0];

    int i, gcdNum;

    gcdNum = gcd(arr[0], arr[1]);

    for(i = 2; i < mSize; i++)
        gcdNum = gcd(gcdNum , arr[i]);

    return gcdNum;
}

int gcd(int a, int b)
{
    if(a == 0)
        return b;
    if(b == 0)
        return a;

    int temp;

    while(b)
    {
        temp = a % b;
        a = b;
        b = temp;
    }

    return a;
}
