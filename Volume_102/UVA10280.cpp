/***************************************************************
 * Author: Nguyen Truong Duy
 ***************************************************************/

#include <cstdio>
#include <vector>

using namespace std;

/* Methodology:
 *	+ Denote Euler(n) to be the Euler Totient Function valued at n which is
 *		the number of m >= 1 and m <= n such that gcd(m, n) = 1.
 *	+ This problem is equivalent to computing
 *		2 * (Euler(2) + ... + Euler(N)) + Euler(1)
 *	      = 2 * (Euler(1) + ... + Euler(N)) - Euler(1)
 *
 *	+ Formula for computing Euler(n):
 *		Euler(n) = n * PRODUCT( (p - 1) / p) over distinct primes p that divide n		
 */

// Note that 224^2 > 50000. We just need to find all primes up to sqrt(50000)
const int UPPERBOUND_PRIME = 224; 
const int UPPERBOUND_TOTIENT = 50000;

int computeEulerTotient(int n, const vector<int> & primeList);
void accumulateEulerTotient(int eulerTotient[]);
void generatePrimeList(vector<int> & primeList, int upperBound);

int main(void)
{
	int sumEulerTotient[UPPERBOUND_TOTIENT + 1];

	accumulateEulerTotient(sumEulerTotient);

	int N;
	while(1)
	{
		scanf("%d", &N);
		if(N == 0)
			break;

		if(N == 1)
			printf("%d\n", sumEulerTotient[N]);
		else
			printf("%d\n", (sumEulerTotient[N] << 1) - sumEulerTotient[1]);
	}
}

void accumulateEulerTotient(int sumEulerTotient[])
{
	vector<int> primeList;

	generatePrimeList(primeList, UPPERBOUND_PRIME);

	sumEulerTotient[0] = -1;	// Undefined
	for(int n = 1; n <= UPPERBOUND_TOTIENT; n++)
		sumEulerTotient[n] = computeEulerTotient(n, primeList);

	for(int n = 2; n <= UPPERBOUND_TOTIENT; n++)
		sumEulerTotient[n] += sumEulerTotient[n - 1];
}

void generatePrimeList(vector<int> & primeList, int upperBound)
{
	primeList.clear();
	vector<bool> isPrime(upperBound + 1, true);
	
	isPrime[0] = isPrime[1] = false;

	for(int n = 2; n <= upperBound; n++)
		if(isPrime[n])
		{
			primeList.push_back(n);

			for(int multipleN = n + n; multipleN <= upperBound; multipleN += n)
				isPrime[multipleN] = false;
		}
}

int computeEulerTotient(int n, const vector<int> & primeList)
{
	int cpyN = n, euler = n;

	for(int i = 0; i < (int) primeList.size() && primeList[i] * primeList[i] <= cpyN; i++)
	{
		if(n % primeList[i] == 0)
		{
			euler = (euler / primeList[i]) * (primeList[i] - 1);

			while(n % primeList[i] == 0)
				n /= primeList[i];	
		}
	}

	if(n > 1)
	{
		// This is the last prime factor
		euler = (euler / n) * (n - 1);
	}

	return euler;
}
