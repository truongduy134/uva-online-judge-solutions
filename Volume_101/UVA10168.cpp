#include <cstdio>
#include <vector>

using namespace std;

const int UPPERBOUND = 10000000;
const int MAX_PRIME_DECOMPOSE = 4;

void generatePrimeSieveAndList(vector<bool> & primeSieve, vector<int> & primeList, int upperBound);
bool decomposeIntoSumOfFourPrimes(int num, int primeDecompose[], const vector<int> & primeList, const vector<bool> & primeSieve);

/* Method to speed up:
 *	Goldbach's conjecture: Every even integer greater than 2 can be written as the sum of
 *			two primes.
 *
 *	or equivalently, every integer greater than 5 can be written as the sume of three primes.
 *
 * If N <= 7, N cannot be decomposed into the sum of 4 primes.
 *
 * If N >= 8, one way to decompose N is as follows:
 *	+ If N is even, let N - 4 = A + B (A, B are primes. Such decomposition exists by Goldbach conjecture). Then N = A + B + 2 + 2 (which is the sum of 4 primes).
 *	+ If N is odd (then N >= 9), let N - 5 = A + B (where A, B are primes). Then N = A + B + 2 + 3 (which is the sum of 4 primes).
 */

int main(void)
{
	vector<bool> primeSieve;
	vector<int> primeList;

	generatePrimeSieveAndList(primeSieve, primeList, UPPERBOUND);

	int num;
	int primeDecompose[MAX_PRIME_DECOMPOSE];
	while(scanf("%d", &num) > 0)
	{
		bool canDecompose = decomposeIntoSumOfFourPrimes(num, primeDecompose, primeList, primeSieve);

		if(canDecompose)
		{
			printf("%d", primeDecompose[0]);
			for(int i = 1; i < MAX_PRIME_DECOMPOSE; i++)
				printf(" %d", primeDecompose[i]);
			printf("\n");
		}
		else
			printf("Impossible.\n");
	}

	return 0;
}

void generatePrimeSieveAndList(vector<bool> & primeSieve, vector<int> & primeList, int upperBound)
{
	primeSieve.assign(upperBound + 1, true);
	primeList.clear();

	primeSieve[0] = primeSieve[1] = false;

	for(int n = 2; n <= upperBound; n++)
		if(primeSieve[n])
		{
			primeList.push_back(n);

			for(int nextN = n + n; nextN <= upperBound; nextN += n)
				primeSieve[nextN] = false;
		}
}

/* 
 * Assumption: primeList is ordered in the increasing number of primes. 
 */
bool decomposeIntoSumOfFourPrimes(int num, int primeDecompose[], const vector<int> & primeList, const vector<bool> & primeSieve)
{
	if(num < 8)
		return false;

	primeDecompose[0] = 2;

	if(num & 1)
		primeDecompose[1] = 3;
	else
		primeDecompose[1] = 2;

	num -= (primeDecompose[1] + primeDecompose[0]);

	for(int i = 0; i < (int) primeList.size(); i++)
		if(primeSieve[num - primeList[i]])
		{
			primeDecompose[2] = primeList[i];
			primeDecompose[3] = num - primeList[i];
			break;
		}

	return true;
}
