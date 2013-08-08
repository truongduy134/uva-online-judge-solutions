#include <cstdio>
#include <vector>
using namespace std;

#define MAX_N 1000000

int sumDigit(int n)
{
    int sum = 0;

    while(n)
    {
        sum += n % 10;
        n /= 10;
    }

    return sum;
}

int main(void)
{
    vector<bool> selfNumSieve(MAX_N + 1, true);
    int nextN;

  //  freopen("out.txt", "w", stdout);

    for(int n = 1; n <= MAX_N; n++)
    {
        nextN = n + sumDigit(n);
        if(nextN <= MAX_N)
            selfNumSieve[nextN] = false;
    }

    for(int n = 1; n <= MAX_N; n++)
        if(selfNumSieve[n])
            printf("%d\n", n);

    return 0;
}
