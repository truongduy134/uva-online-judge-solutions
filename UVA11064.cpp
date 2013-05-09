#include <cstdio>
#include <vector>

using namespace std;

const int UPPERBOUND = 46341;

void generatePrimeList(vector<int> & primeList, int upperBound);
int computeResult(int n, const vector<int> & primeList);

int main(void)
{
	vector<int> primeList;

	generatePrimeList(primeList, UPPERBOUND);

	int n;
	while(scanf("%d", &n) > 0)
	{
		printf("%d\n", computeResult(n, primeList));
	}
	return 0;
}

/* Find the number of m such that
 *	1 <= m <= n and gcd(m, n) != 1 and gcd(m, n) != m
 *
 * Methodology: The result is n - numDivisor(n) - eulerTotientFunction(n) + 1
 */
int computeResult(int n, const vector<int> & primeList)
{
	int numDivisor = 1, eulerTotient = n, cpyN = n, power;

	for(int ind = 0; ind < (int) primeList.size(); ind++)
	{
		if(primeList[ind] > cpyN / primeList[ind])
			break;

		power = 0;
		while(n % primeList[ind] == 0)
		{
			power++;
			n /= primeList[ind];
		}

		if(power > 0)
		{
			numDivisor *= (power + 1);
			eulerTotient = (eulerTotient / primeList[ind]) * (primeList[ind] - 1);
		}
	}

	if(n > 1)
	{
		numDivisor *= 2;
		eulerTotient = (eulerTotient / n) * (n - 1);
	}

	return cpyN - numDivisor - eulerTotient + 1;
}

void generatePrimeList(vector<int> & primeList, int upperBound)
{
	vector<bool> primeSieve(upperBound + 1, true);

	for(int n = 2; n <= upperBound; n++)
		if(primeSieve[n] == true)
		{
			primeList.push_back(n);

			for(int multipleN = n + n; multipleN <= upperBound; multipleN += n)
				primeSieve[multipleN] = false;
		}
}
