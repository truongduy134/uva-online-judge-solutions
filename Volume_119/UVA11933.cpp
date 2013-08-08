#include <cstdio>

using namespace std;

int main(void)
{
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);

    int n;

    while(1)
    {
        scanf("%d", &n);

        if(n == 0)
            break;

        int a = 0, indexBit = 0, numOneSoFar = 0, copyN = n;
        while(n)
        {
            if(n & 1)
            {
                // Find one bit 1
                numOneSoFar++;
                if(numOneSoFar & 1)
                    a = a | (1 << indexBit);
            }
            indexBit++;
            n = n >> 1;
        }

        printf("%d %d\n", a, copyN - a);

    }
    return 0;
}
