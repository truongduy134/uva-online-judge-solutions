#include <cstdio>

using namespace std;

#define MAX_LEN 800001

int computeGcd(int m, int n)
{
    int r;

    while(n)
    {
        r = m % n;
        m = n;
        n = r;
    }

    return m;
}

int main(void)
{
    int m, n, index, leftM, leftN, rightM, rightN, midM, midN, gcd;
    char direction[MAX_LEN];

  //  freopen("in.txt", "r", stdin);
  //  freopen("out.txt", "w", stdout);

    while(1)
    {
        scanf("%d %d", &m, &n);
        if(m == 1 && n == 1)
            break;

        index = 0;
        leftM = 0;
        leftN = 1;
        rightM = 1;
        rightN = 0;

        while(1)
        {
            midM = leftM + rightM;
            midN = leftN + rightN;
       /*     gcd = computeGcd(midM, midN);
            if(gcd > 1)
            {
                midM /= gcd;
                midN /= gcd;
            } */

            if(midM == m && midN == n)
                break;

            if((m * 1.0 / n) < (midM * 1.0 / midN))
            {
                // Turn left
                rightM = midM;
                rightN = midN;
                direction[index] = 'L';
            }
            else
            {
                leftM = midM;
                leftN = midN;
                direction[index] = 'R';
            }

            index++;
        }

        direction[index] = '\0';
        printf("%s\n", direction);
    }
    return 0;
}
