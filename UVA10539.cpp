/************************************************************************
 * Author: Nguyen Truong Duy
 ************************************************************************/

/* Methodology:
 *	+ Almost prime numbers are non-prime numbers that are powers of a single prime number.
 *	+ Note that the input range is between 1 and 10^12.
 *
 *	+ To tackle this problem, first we find the list L of all primes numbers <= 10^6 
 *		using Sieve of Eratosthenes algorithm.
 *	+ For an input range [a, b], we iterate through all primes p in L, and calculate
 *		the number of its powers p^k (k >= 2) that fall in [a, b].		
 */
#include <cstdio>
#include <vector>

using namespace std;

const int UPPERBOUND = 1000000;

void generatePrimeList(vector<long long> & primeList, int upperBound);
long long countAlmostPrimes(long long lowerBound, long long upperBound, const vector<long long> & primeList);

int main(void)
{
	vector<long long> primeList;
	int T;

	generatePrimeList(primeList, UPPERBOUND);

	long long lowerBound, upperBound;

	scanf("%d", &T);
	while(T)
	{
		scanf("%lld %lld", &lowerBound, &upperBound);

		printf("%lld\n", countAlmostPrimes(lowerBound, upperBound, primeList));

		T--;
	}
	return 0;
}

void generatePrimeList(vector<long long> & primeList, int upperBound)
{
	primeList.clear();
	vector<bool> isPrime(upperBound + 1, true);

	isPrime[0] = isPrime[1] = false;

	for(int n = 2; n < upperBound; n++)
		if(isPrime[n])
		{
			primeList.push_back(n);

			for(int multipleN = n + n; multipleN <= upperBound; multipleN += n)
				isPrime[multipleN] = false;
		}
}

long long countAlmostPrimes(long long lowerBound, long long upperBound, const vector<long long> & primeList)
{
	long long count = 0, power;

	for(int i = 0; i < (int) primeList.size() && (power = primeList[i] * primeList[i]) <= upperBound; i++)
	{
		while(power <= upperBound)
		{
			if(power >= lowerBound)
				count++;
			power *= primeList[i];
		}
	}

	return count;
} 
