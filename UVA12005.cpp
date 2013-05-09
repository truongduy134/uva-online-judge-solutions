#include <cstdio>
#include <vector>

using namespace std;

/* Methodology:
 *		c = ab - (a + b) / 2 + 1   (*)
 *	<=>	4c - 3 = (2a - 1)(2b - 1)
 * Hence, the number of solutions of (*) equals to the number of divisors of 4c - 3
 */

const int UPPERBOUND = 20000000;

void generatePrimeList(vector<int> & primeList, vector<bool> & primeSieve, int upperBound);
unsigned long long int findNumSolution(unsigned long long int c, const vector<int> &primeList, const vector<bool> & primeSieve);
unsigned long long int findNumDivisor(unsigned long long int n, const vector<int> & primeList, const vector<bool> & primeSieve);

int main(void)
{
	vector<int> primeList;
	vector<bool> primeSieve;

	generatePrimeList(primeList, primeSieve, UPPERBOUND);

	unsigned long long int c;
	while(1)
	{
		scanf("%llu", &c);
		if(c == 0)
			break;

		printf("%llu %llu\n", c, findNumSolution(c, primeList, primeSieve));
	}

	return 0;
}

void generatePrimeList(vector<int> & primeList, vector<bool> & primeSieve, int upperBound)
{
	primeSieve.assign(upperBound, true);
	primeSieve[0] = false;
	primeSieve[1] = false;

	primeList.clear();

	for(int n = 2; n < upperBound; n++)
		if(primeSieve[n])
		{
			primeList.push_back(n);

			for(int multiple = n + n; multiple < upperBound; multiple += n)
				primeSieve[multiple] = false;
		}
}

unsigned long long int findNumSolution(unsigned long long int c, const vector<int> &primeList, const vector<bool> & primeSieve)
{
	if(c == 1)
		return 2;
	return findNumDivisor((c << 2) - 3, primeList, primeSieve);
}

unsigned long long int findNumDivisor(unsigned long long int n, const vector<int> & primeList, const vector<bool> & primeSieve)
{
	int numPrime = (int) primeList.size();
	unsigned long long int factor, numDivisor = 1, cpyN = n, square;

	for(int ind = 0; ind < numPrime; ind++)
	{
		if(n < UPPERBOUND && primeSieve[n] == true)
			break;
		square = ((unsigned long long int) primeList[ind]) * primeList[ind];
		if(square > cpyN)
			break;

		factor = 0;
		while(n % primeList[ind] == 0)
		{
			n /= primeList[ind];
			factor++;
		}

		if(factor > 0)
			numDivisor *= (factor + 1);
	}

	if(n > 1)
		// This is the last prime divisor of n
		numDivisor *= 2;

	return numDivisor;
}
