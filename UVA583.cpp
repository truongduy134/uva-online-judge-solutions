#include <cstdio>
#include <vector>

using namespace std;

#define UPPER_BOUND 47000

void getPrimeFactorList(int N, vector<int> & primeFactorList, const vector<int> & primeList);
void generatePrimeList(vector<int> & primeList, int upperBound);

int main(void)
{
	vector<int> primeList;
	vector<int> primeFactorList;
	int N;

	generatePrimeList(primeList, UPPER_BOUND);

	while(1)
	{
		scanf("%d", &N);
		if(N == 0)
			break;

		printf("%d = ", N);
		if(N < 0)
		{
			N = -N;
			printf("-1 x ");
		}

		getPrimeFactorList(N, primeFactorList, primeList);
		
		if(!primeFactorList.empty())
		{
			printf("%d", primeFactorList[0]);
			for(int i = 1; i < (int) primeFactorList.size(); i++)
				printf(" x %d", primeFactorList[i]);
		}
		printf("\n");		
	}	
	return 0;
}

// Using Sieve of Eratosthenes Algorithm
void generatePrimeList(vector<int> & primeList, int upperBound)
{
	vector<bool> primeSieve(upperBound + 1, true);

	primeSieve[0] = primeSieve[1] = false;

	int n, multipleN;

	for(n = 2; n <= upperBound; n++)
		if(primeSieve[n])
		{
			primeList.push_back(n);

			for(multipleN = n + n; multipleN <= upperBound; multipleN += n)
				primeSieve[multipleN] = false;
		}
}

void getPrimeFactorList(int N, vector<int> & primeFactorList, const vector<int> & primeList)
{
	primeFactorList.clear();

	for(int ind = 0; ind < (int) primeList.size() && N > 1; ind++)
		while(N % primeList[ind] == 0)
		{
			primeFactorList.push_back(primeList[ind]);
			N /= primeList[ind];
		}

	if(N > 1)
		primeFactorList.push_back(N);
}
