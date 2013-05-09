#include <stdio.h>

#define UPPER_BOUND 32000

int getPrime(int primeSieve[], int upperBound);
int getNumDivisor(int n, int primeSieve[], int numPrime);

int main(void)
{
    int primeSieve[UPPER_BOUND], numPrime, T, L, U,
        resultNum, maxNumDivisor, n, numDivisor;

    numPrime = getPrime(primeSieve, UPPER_BOUND);

    scanf("%d", &T);
    while(T)
    {
        scanf("%d %d", &L, &U);

        resultNum = 1;
        maxNumDivisor = 1;

        for(n = L; n <= U; n++)
        {
            numDivisor = getNumDivisor(n, primeSieve, numPrime);
            if(numDivisor > maxNumDivisor)
            {
                resultNum = n;
                maxNumDivisor = numDivisor;
            }
        }
        printf("Between %d and %d, %d has a maximum of %d divisors.\n", L, U, resultNum,
                maxNumDivisor);

        T--;
    }

    return 0;
}

int getPrime(int primeSieve[], int upperBound)
{
    int numPrimeSoFar = 0, notPrimeSieve[UPPER_BOUND] = {0}, n, multipleN;

    for(n = 2; n < UPPER_BOUND; n++)
        if(!notPrimeSieve[n])
        {
            primeSieve[numPrimeSoFar] = n;
            numPrimeSoFar++;

            for(multipleN = n + n; multipleN < UPPER_BOUND; multipleN += n)
                notPrimeSieve[multipleN] = 1;
        }

    return numPrimeSoFar;
}

int getNumDivisor(int n, int primeSieve[], int numPrime)
{
    /* It is guaranteed primeSieve contains all primes less than or equal to sqrt(n) */
    int numDivisor = 1, ind, numFactor, oldN = n;

    for(ind = 0; ind < numPrime && primeSieve[ind] * primeSieve[ind] <= oldN; ind++)
    {
        numFactor = 0;
        while(n % primeSieve[ind] == 0)
        {
            numFactor++;
            n /= primeSieve[ind];
        }

        if(numFactor)
            numDivisor *= (numFactor + 1);
    }

    if(n > 1)
        numDivisor *= 2;

    return numDivisor;

}

