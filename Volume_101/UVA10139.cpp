/*******************************************************
 * Author: Nguyen Truong Duy
 *******************************************************/

/* Methodology:
 *	+ Let the prime factorization of k = p1^a1 * p2^a2 * ... * p(n)^a(n)
 *	+ k divides n! if and only if
 *		p(i)^a(i) | n!	for all i = 1 ... n
 *	+ To check p(i)^a(i) | n! or not, we find the largest power of p(i) dividing n!. This can be done by the following formula
 *		 n / p(i) + n / p(i)^2 + n / p(i)^3 + ...
 *	+ So if the prime factorization of n = p(i)^b(i) * ...
 *	  and b(i) >= a(i), then p(i)^a(i) | n!
 */

#include <cstdio>
#include <vector>

using namespace std;

const int UPPERBOUND = 46341;	// UPPERBOUND > sqrt(2^31)

void generatePrimeList(vector<int> & primeList, int upperBound);
bool doesDivideFactorial(int n, int k, const vector<int> & primeList);
int getLargestDividingPrimePower(int n, int p);

int main(void)
{
	int n, k;
	vector<int> primeList;

	generatePrimeList(primeList, UPPERBOUND);

	while(scanf("%d %d", &n, &k) > 0)
	{
		if(doesDivideFactorial(n, k, primeList))
			printf("%d divides %d!\n", k, n);
		else
			printf("%d does not divide %d!\n", k, n);
	}
	return 0;
}

void generatePrimeList(vector<int> & primeList, int upperBound)
{
	primeList.clear();
	vector<bool> primeSieve(upperBound + 1, true);

	primeSieve[0] = primeSieve[1] = false;

	for(int n = 2; n <= upperBound; n++)
		if(primeSieve[n])
		{
			primeList.push_back(n);

			for(int multipleN = n + n; multipleN <= upperBound; multipleN += n)
				primeSieve[multipleN] = false;
		}
}

// Return true if k divides n!
bool doesDivideFactorial(int n, int k, const vector<int> & primeList)
{
	if(k == 0)
		return false;

	int p, copyK = k, powerK, powerN;

	for(int i = 0; i < (int) primeList.size(); i++)
	{
		p = primeList[i];
		if(p > (copyK / p))
			break;

		if(k % p == 0)
		{
			powerK = 0;
			while(k % p == 0)
			{
				powerK++;
				k /= p;
			}
			powerN = getLargestDividingPrimePower(n, p);
			if(powerN < powerK)
				return false;
		}
	}

	if(k > 1)
	{
		// This is the last prime factor of the original k
		if(getLargestDividingPrimePower(n, k) < 1)
			return false;
	}
	return true;	
}

// Return the largest power of a prime p that divides n! 
int getLargestDividingPrimePower(int n, int p)
{
	int power = 0;

	while(n)
	{
		power += n / p;
		n /= p;
	}

	return power;
}

