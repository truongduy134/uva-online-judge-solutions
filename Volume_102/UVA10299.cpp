#include <cstdio>
#include <vector>

using namespace std;

const int UPPERBOUND = 31623;

int computeEulerTotientFunction(int N, const vector<int> & primeList);
void computePrimeList(vector<int> & primeList, const int upperBound);

int main(void)
{
	vector<int> primeList;

	computePrimeList(primeList, UPPERBOUND);

	int N;

	while(1)
	{
		scanf("%d", &N);
		if(!N)
			break;

		printf("%d\n", computeEulerTotientFunction(N, primeList));
	}

	return 0;
}

void computePrimeList(vector<int> & primeList, const int upperBound)
{
	primeList.clear();

	vector<bool> primeSieve(upperBound + 1, true);

	for(int n = 2; n <= upperBound; n++)
		if(primeSieve[n])
		{
			primeList.push_back(n);

			for(int multipleN = n + n; multipleN <= upperBound; multipleN += n)
				primeSieve[multipleN] = false;
		}
}

int computeEulerTotientFunction(int N, const vector<int> & primeList)
{
	// For this specific problem, eulerTotient(1) = 0
	if(N < 2)
		return 0;

	int cpyN = N, totient = N;

	for(int ind = 0; ind < (int) primeList.size(); ind++)
		if(primeList[ind] * primeList[ind] > N)
			break;
		else
		{
			if(N % primeList[ind] == 0)
			{
				totient = (totient / primeList[ind]) * (primeList[ind] - 1);

				while(cpyN % primeList[ind] == 0)
					cpyN /= primeList[ind];
			}
		}

	if(cpyN > 1)
	{
		// This is the last prime factor of N
		totient = (totient / cpyN) * (cpyN - 1);
	}

	return totient;
}
