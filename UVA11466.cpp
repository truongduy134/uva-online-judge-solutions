/*******************************************************************************
 * Author: Nguyen Truong Duy
 ********************************************************************************/

/* Methodology:
 *	+ Generate the list L all primes less than 10^7 using Sieve of Eratosthenes algorithm.
 *	+ For each number N, find its prime factors in L.
 *	  Note that since N has at most 14 digits, N has at most 1 prime factor not in L.
 *
 * Important Note:
 *	+ If N is prime or a power of a single prime, by problem statement, N does not have the largest prime factor.
 *	+ N can be negative! 
 */

#include <cstdio>
#include <vector>

using namespace std;

const int UPPERBOUND = 10000000;

void generatePrimeList(vector<long long> & primeList, int upperBound);
long long findLargestProperPrimeFactor(long long N, const vector<long long> & primeList);

int main(void)
{
	vector<long long> primeList;

	generatePrimeList(primeList, UPPERBOUND);

	long long N;
	while(1)
	{
		scanf("%lld", &N);
		if(!N)
			break;

		printf("%lld\n", findLargestProperPrimeFactor(N, primeList));
	}
	return 0;
}

void generatePrimeList(vector<long long> & primeList, int upperBound)
{
	primeList.clear();
	vector<bool> primeSieve(upperBound, true);

	for(int n = 2; n < upperBound; n++)
		if(primeSieve[n])
		{
			primeList.push_back(n);

			for(int multipleN = n + n; multipleN < upperBound; multipleN += n)
				primeSieve[multipleN] = false;
		}
}

long long findLargestProperPrimeFactor(long long N, const vector<long long> & primeList)
{
	if(N < 0)
		N = -N;

	long long cpyN, prime, maxFactor = 0;

	int numDiffFactor = 0;

	if(N < 2)
		return -1;

	cpyN = N;
	for(int ind = 0; ind < (int) primeList.size(); ind++)
	{
		prime = primeList[ind];
		if(prime * prime > N)
			break;

		if(cpyN % prime == 0)
		{
			numDiffFactor++;

			if(maxFactor < prime)
				maxFactor = prime;
		
			while(cpyN % prime == 0)
				cpyN /= prime;
		}
	}

	if(cpyN == N)
		// N is a prime
		return -1;

	if(cpyN > maxFactor)
	{
		numDiffFactor++;
		maxFactor = cpyN;
	}

	if(numDiffFactor < 2)
		// N is a power of a single prime
		return -1;

	return maxFactor;
}
