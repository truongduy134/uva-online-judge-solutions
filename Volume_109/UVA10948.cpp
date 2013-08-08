#include <cstdio>
#include <vector>
#include <utility>

using namespace std;

#define MAX_VAL 1000000

void generatePrimeListAndSieve(vector<bool> & primeSieve, vector<int> & primeList, int upperBound);
pair<int, int> decomposeIntoSumTwoPrimes(int N, const vector<bool> & primeSieve, const vector<int> & primeList);

int main(void)
{
	vector<bool> primeSieve;
	vector<int> orderedPrimeList;
	int N;
	pair<int, int> result;

	generatePrimeListAndSieve(primeSieve, orderedPrimeList, MAX_VAL);

	while(1)
	{
		scanf("%d", &N);
		if(!N)
			break;

		result = decomposeIntoSumTwoPrimes(N, primeSieve, orderedPrimeList);

		printf("%d:\n", N);
		if(result.first == 0)
			printf("NO WAY!\n");
		else
			printf("%d+%d\n", result.first, result.second);
	}

	return 0;
}

void generatePrimeListAndSieve(vector<bool> & primeSieve, vector<int> & primeList, int upperBound)
{
	primeList.clear();
	primeSieve.assign(upperBound + 1, true);

	primeSieve[0] = primeSieve[1] = false;

	for(int n = 2; n <= upperBound; n++)
		if(primeSieve[n])
		{
			primeList.push_back(n);

			for(int multipleN = n + n; multipleN <= upperBound; multipleN += n)
				primeSieve[multipleN] = false;
		}
}

// Assumption: primeList is an ordered list of prime less than or equal to N
pair<int, int> decomposeIntoSumTwoPrimes(int N, const vector<bool> & primeSieve, const vector<int> & primeList)
{
	if(N <= 1)
		return pair<int, int> (0, 0);

	if(N & 1)
	{
		// If N is odd
		if(primeSieve[N - 2])
			return pair<int, int> (2, N - 2);
		else
			return pair<int, int> (0, 0);
	}

	int left = 0, right = (int) primeList.size() - 1, sum;

	while(left <= right)
	{
		sum = primeList[left] + primeList[right];
	
		if(sum == N)
			return pair<int, int>(primeList[left], primeList[right]);
		if(sum > N)
			right--;
		else
			left++;
	}

	return pair<int, int> (0, 0);	
}
