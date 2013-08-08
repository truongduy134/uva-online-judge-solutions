/************************************************************************
 * Author: Nguyen Truong Duy
 ************************************************************************/

#include <cstdio>
#include <vector>

using namespace std;

/* Methodology:
 *	+ Generate first all primes less than 10^6 (using sieve of eratosthenes algorithm).
 *	+ Then use brute force approach to factorize the input number using the list
 *		of primes generated above.
 */

const int UPPERBOUND = 1000000;

void factorize(long long N, vector<long long> & factorization, const vector<long long> & primeList);
void generatePrimeList(vector<long long> & primeList, int upperBound);

int main(void)
{
	vector<long long> primeList, factorization;
	long long N;

	generatePrimeList(primeList, UPPERBOUND);

	while(1)
	{
		scanf("%lld", &N);
		if(N < 0)
			break;

		factorize(N, factorization, primeList);

		for(int i = 0; i < (int) factorization.size(); i++)
			printf("    %lld\n", factorization[i]);
		printf("\n");
	}
	return 0;
}

void generatePrimeList(vector<long long> & primeList, int upperBound)
{
	vector<bool> isPrime(upperBound, true);

	isPrime[0] = isPrime[1] = false;

	for(int n = 2; n < upperBound; n++)
		if(isPrime[n])
		{
			primeList.push_back(n);
			
			for(int multipleN = n + n; multipleN < upperBound; multipleN += n)
				isPrime[multipleN] = false;
		}
}

// Assumption: N has at most 1 prime factor larger than 10^6.
//		and primeList contains all primes less than 10^6.
void factorize(long long N, vector<long long> & factorization, const vector<long long> & primeList)
{
	long long cpyN = N;

	factorization.clear();
	for(int i = 0; i < (int) primeList.size(); i++)
	{
		if(primeList[i] * primeList[i] > cpyN)
			break;

		while(N % primeList[i] == 0)
		{
			N /= primeList[i];
			factorization.push_back(primeList[i]);
		}
	}

	if(N > 1)
		factorization.push_back(N);
}
