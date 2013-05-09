/*
 * UVA Problem ID: 10179 (Irreducable Basic Fractions)
 *
 * Definition: A fraction m / n is basic if 0 <= m < n and it is irreducable if gcd(m, n) = 1
 *
 * Input:
 *  + The input consists of multiple test cases.
 *  + For each test case, there is a line containing a number N < 10^9.
 *  + The input terminiates when N = 0.
 *
 * Output:
 *  + For each input N, output the number of irreducible basic fractions with denominator N.
 *
 * Methodology:
 *  The number of irreducible basic fractions with denominator N is T(N) where T(N) is the
 *      Euler's Totient function evaluated at N.
 */
#include <stdio.h>

#define MAX_SIZE 32000

long int primeList[MAX_SIZE];
long int primeListSize = 0;

void generatePrimeList();
long int computeTotientFunction(long int);

int main()
{
    long int N;

    generatePrimeList();

    while(1)
    {
        scanf("%ld", &N);

        if(N == 0)
            break;

        printf("%ld\n", computeTotientFunction(N));
    }
    return 0;
}

/* Assumption: 0 <= N < 10^9
 *
 * Methodology:
 *  + Let T(N) be the Euler's totient function evaluated at N
 *  + T(N) = N * product(1 - 1 / d) where numbers d are distinct prime factors of N.
 *         = N * product[(d - 1) / d]
 */
long int computeTotientFunction(long int N)
{
    long int index, copyN = N, numer = 1, denom = 1;

    if(N == 0)
        return 0;
    if(N == 1)
        return 1;

    for(index = 0; index < primeListSize && primeList[index] * primeList[index] <= N; index++)
    {
        if(copyN % primeList[index] == 0)
        {
            numer *= primeList[index] - 1;
            denom *= primeList[index];
        }

        while(copyN % primeList[index] == 0)
            copyN /= primeList[index];
    }

    if(copyN == N)/* N is a prime! */
        return N - 1;

    if(copyN > 1)
    {
        /* The remaining copyN is a prime too! */
        numer *= copyN - 1;
        denom *= copyN;
    }

    return (N / denom) * numer;
}

/* Methodology: Use The Sieve of Eratosthenes Algorithm */
void generatePrimeList()
{
    long int primeSieve[MAX_SIZE] = {0}, num, multiple;

    primeSieve[0] = primeSieve[1] = 1;

    for(num = 2; num < MAX_SIZE; num++)
        if(primeSieve[num] == 0)
        {
            /* num is a prime! */
            primeList[primeListSize++] = num;

            for(multiple = num << 1; multiple < MAX_SIZE; multiple += num)
                primeSieve[multiple] = 1;
        }
}
