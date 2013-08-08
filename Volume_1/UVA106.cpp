#include <iostream>
#include <cmath>
#include <set>
#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

bool isCoPrime(unsigned int a, unsigned int b);
unsigned int gcd(unsigned int a, unsigned int b);

/* Euclid's formula: Every primitive Pythagorean triple (a, b, c) (a < b < c)
 *      arises from a unique pair of coprimes m and n (n < m) and m - n is odd
 *      such that
 *          a = m^2 - n^2
 *          b = 2*m*n
 *          c = m^2 + n^2   (possibly after exchanging a and b)
 */
int main()
{
    unsigned int N;

    while(scanf("%ud", &N) > 0)
    {
        unsigned int numPrimitive = 0;
        unsigned int m, n, a, b, c;
        unsigned int root = (unsigned int) floor(sqrt(N));
        vector<bool> sieveNotInTriple(N + 1);

        fill(sieveNotInTriple.begin(), sieveNotInTriple.end(), true);
        sieveNotInTriple[0] = false;

        for(n = 1; n <= root; n++)
            for(m = n + 1; m <= root; m++)
                if(isCoPrime(m, n) && (m - n) % 2 != 0)
                {
                    a = m * m - n * n;
                    b = 2 * m * n;
                    c = m * m + n * n;
                    if(a <= N && b <= N && c <= N) {
                        numPrimitive++;

                        unsigned int copyA = a, copyB = b, copyC = c;
                        while(copyA <= N && copyB <= N && copyC <= N)
                        {
                            sieveNotInTriple[copyA] = false;
                            sieveNotInTriple[copyB] = false;
                            sieveNotInTriple[copyC] = false;
                            copyA += a;
                            copyB += b;
                            copyC += c;
                        }
                    }
                }

        cout << numPrimitive << " " << count(sieveNotInTriple.begin(), sieveNotInTriple.end(), true) << endl;
    }



    return 0;
}

bool isCoPrime(unsigned int a, unsigned int b)
{
    if(gcd(a, b) == 1)
        return true;
    return false;
}

unsigned int gcd(unsigned int a, unsigned int b)
{
    unsigned int r;

    while(b)
    {
        r = a % b;
        a = b;
        b = r;
    }

    return a;
}
