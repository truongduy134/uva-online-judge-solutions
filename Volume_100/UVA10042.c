/*
 * UVA Problem ID: 10042 (Smith numbers)
 *
 * Definition: A Smith number is a COMPOSITE number such that the sum of its digits
 *             is equal to the sum of the digits in its prime factorization.
 *
 * Input:
 *      + The first line is the number of test cases T.
 *      + Each test case consists of one line containing a single positive integer N < 10^9.
 *
 * Output:
 *      + For each input N, print the smallest Smith number which is larger than N.
 *
 * Assumption: Assume that such a number exists.
 */
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 32000

long int primeArr[MAX_SIZE];
long int primeArrSize = 0;

void findPrimeList();
int isSmithNumber(long int);
long int getDigitSum(long int);
long int getDigitSumFactorization(long int, long int *);

int main()
{
    long int numTest, num, nextNum;

    findPrimeList();

    scanf("%ld", &numTest);
    while(numTest > 0)
    {
        scanf("%ld", &num);

        /* It is guaranteed this loop is terminiated after a finite amount of time since it is
           assumed such a Smith number exists */
        nextNum = num + 1;
        while(1)
        {
            if(isSmithNumber(nextNum))
            {
                printf("%ld\n", nextNum);
                break;
            }
            nextNum++;
        }

        numTest--;
    }
    return 0;
}

/* Find prime numbers less than MAX_SIZE */
void findPrimeList()
{
    /* After executing the function, primeSieve[i] = 0 means i is a prime;
       primeSieve[i] = 1 means i is a composite! */
    long int primeSieve[MAX_SIZE] = {0}, num, multiple;

    primeSieve[0] = primeSieve[1] = 1;

    for(num = 2; num < MAX_SIZE; num++)
        if(primeSieve[num] == 0)
        {
            /* num is a prime! */
            primeArr[primeArrSize++] = num;

            for(multiple = num; multiple < MAX_SIZE; multiple += num)
                primeSieve[multiple] = 1;
        }
}

/* Return 1 if N is a Smith number. Return 0 otherwise */
int isSmithNumber(long int N)
{
    long int isPrime, digitSum, digitSumFactor;

    digitSumFactor = getDigitSumFactorization(N, &isPrime);
    if(isPrime)
        return 0;       /* A Smith number must be composite */

    digitSum = getDigitSum(N);
    return digitSum == digitSumFactor;
}

/* Return the sum of the digits in the prime factorization of a composite number N.
   If N is a prime, the return value is 0 and isPrime is set to 1 */
long int getDigitSumFactorization(long int N, long int *isPrime)
{
    long int index = 0, sumFactor = 0, copyN = N;
    *isPrime = 0;

    if(N <= 1)
        return 0;

    for(index = 0; index < primeArrSize && primeArr[index] * primeArr[index] <= N; index++)
    {
        while(copyN % primeArr[index] == 0)
        {
            sumFactor += getDigitSum(primeArr[index]);
            copyN /= primeArr[index];
        }
    }

    if(copyN == N)
        /* N is a prime! */
        *isPrime = 1;
    else
        if(copyN > 1)
            sumFactor += getDigitSum(copyN);

    return sumFactor;
}

long int getDigitSum(long int N)
{
    long int digitSum = 0;

    while(N)
    {
        digitSum += N % 10;
        N /= 10;
    }

    return digitSum;
}
