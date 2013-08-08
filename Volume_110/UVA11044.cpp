#include <cstdio>

using namespace std;

int main(void)
{
    int T, n, m, numAtR, numAtC;

    scanf("%d", &T);
    while(T)
    {
        scanf("%d %d", &n, &m);

        n -= 2;
        if(n < 0)
            n = 0;
        m -= 2;
        if(m < 0)
            m = 0;

        numAtR = n / 3;
        if(n % 3)
            numAtR++;

        numAtC = m / 3;
        if(m % 3)
            numAtC++;

        printf("%d\n", numAtR * numAtC);
        T--;
    }

    return 0;
}
