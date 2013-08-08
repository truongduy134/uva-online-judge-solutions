#include <stdio.h>

const int MAX_SIZE = 1 << 15;

void generatePrimeListAndSieve(int primeSieve[], int primeList[], int *numPrime);
int countNumPairPrime(int num, int primeSieve[], int primeList[], int numPrime);

int main(void)
{
	int primeSieve[MAX_SIZE], primeList[MAX_SIZE], num, numPrime;

	generatePrimeListAndSieve(primeSieve, primeList, &numPrime);

	while(1)
	{
		scanf("%d", &num);
		if(num == 0)
			break;

		printf("%d\n", countNumPairPrime(num, primeSieve, primeList, numPrime));
	}
	return 0;
}

void generatePrimeListAndSieve(int primeSieve[], int primeList[], int *numPrime)
{
	int n, multipleN;

	primeSieve[0] = primeSieve[1] = 0;
	for(n = 2; n < MAX_SIZE; n++)
		primeSieve[n] = 1;

	*numPrime = 0;
	for(n = 2; n < MAX_SIZE; n++)
		if(primeSieve[n])
		{
			primeList[*numPrime] = n;
			(*numPrime)++;
			for(multipleN = n + n; multipleN < MAX_SIZE; multipleN += n)
				primeSieve[multipleN] = 0;	
		}
}

int countNumPairPrime(int num, int primeSieve[], int primeList[], int numPrime)
{
	int ind, count = 0;

	for(ind = 0; (primeList[ind] << 1) <= num && ind < numPrime; ind++)
		if(primeSieve[num - primeList[ind]])
			count++;

	return count;
}
