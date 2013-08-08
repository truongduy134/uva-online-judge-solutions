#include <cstdio>
#include <cmath>
#include <iostream>
using namespace std;

int main(void)
{
  //  freopen("out.txt", "w", stdout);

    for(long long m = 1; m <= 2000; m++)
    {
        long long n = m * 1000000;

        for(long long x = 1;; x++)
        {
            long long power4 = x * x;
            power4 *= power4;
            if(power4 > n)
                break;

            if(n % x)
                continue;
            long long u1 = n / x;
            for(long long y = x; y * y * y <= u1 && 3 * y < m - x; y++)
            {
                if(u1 % y)
                    continue;

                long long sumZT = m - x - y;
                long long productZT = u1 / y;
                long long delta = sumZT * sumZT - 4 * productZT;
                long long root = (long long) floor(sqrt(delta));

                if(root * root == delta)
                {
                    long long z = sumZT - root;
                    if(z & 1)
                        continue;
                    z = z >> 1;
                    long long t = sumZT - z;
                    if(y <= z && z <= t)
                        printf("%.2f %.2f %.2f %.2f\n", x / 100.0, y / 100.0, z / 100.0, t / 100.0);
                }
            }
        }
    }
    return 0;
}
