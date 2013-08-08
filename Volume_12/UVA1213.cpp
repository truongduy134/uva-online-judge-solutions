/*******************************************************************************
 * Author: Nguyen Truong Duy
 ********************************************************************************/

/* Methodology:
 *	+ Let L be the sorted list of primes less than 1120.
 *	  L can be generated using Sieve of Eratosthenes algorithm
 *
 *	+ We use dynamic programming to solve this problem
 *	+ Let f(n, k, i) = the number of ways to decompose n into the sum of k
 *		different primes when the largest prime we may use is L[i]
 *	+ Then we have the following recurrence:
 *		f(n, k, i) = f(n, k, i - 1)	// Do not use this prime L[i]
 *			   + f(n - L[i], k - 1, i - 1)	// Use this prime L[i]
 *	+ Base cases: 
 *		f(0, 0, i) = 1 for all i = 0 ... size(L) - 1
 *		f(n, k, i) = 0 if n < 0 or k < 1 or i < 0
 *
 *	+ Time complexity: O(n * k * size(L))
 *	+ IMPORTANT NOTE: If we use 3-D memoization table, it is likely to get
 *		runtime error verdict on UVA judge due to memory problem. Therefore,
 *		we must implement this DP using bottom-up (iterative) approach
 *		and use two 2-D arrays of size n x k instead of the 3-D array.
 */

#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAX_VAL_N = 1120;
const int MAX_PART = 14;

void generatePrime(int upperBound, vector<int> & primeList);
void preCountNumPrimeDecompose(int memoTable[MAX_VAL_N + 1][MAX_PART + 1], const vector<int> & primeList);

int main(void)
{
	vector<int> primeList;

	generatePrime(MAX_VAL_N, primeList);
	
	int memoTable[MAX_VAL_N + 1][MAX_PART + 1];
	preCountNumPrimeDecompose(memoTable, primeList);

	int n, k;
	while(1)
	{
		scanf("%d %d", &n, &k);
		if(n == 0 && k == 0)
			break;

		printf("%d\n", memoTable[n][k]);
	}

	return 0;
}

void generatePrime(int upperBound, vector<int> & primeList)
{
	primeList.clear();
	vector<bool> isPrime(upperBound + 1, true);

	for(int n = 2; n <= upperBound; n++)
		if(isPrime[n])
		{
			primeList.push_back(n);
			for(int multipleN = n + n; multipleN <= upperBound; multipleN += n)
				isPrime[multipleN] = false;
		}
}

void preCountNumPrimeDecompose(int memoTable[MAX_VAL_N + 1][MAX_PART + 1], const vector<int> & primeList)
{
	int tempMemoTable[MAX_VAL_N + 1][MAX_PART + 1];
	int numPrime = (int) primeList.size();

	memset(memoTable, 0, (MAX_VAL_N + 1) * (MAX_PART + 1) * sizeof(int));
	memset(tempMemoTable, 0, (MAX_VAL_N + 1) * (MAX_PART + 1) * sizeof(int));
	memoTable[0][0] = 1;
	tempMemoTable[0][0] = 1;

	bool considerMemo = false;
	for(int primeInd = 0; primeInd < numPrime; primeInd++)
	{
		for(int k = 1; k <= MAX_PART; k++)
			for(int n = 2; n <= MAX_VAL_N; n++)
			{
				if(considerMemo)
					memoTable[n][k] = tempMemoTable[n][k];
				else
					tempMemoTable[n][k] = memoTable[n][k];
	
				if(n >= primeList[primeInd])
				{
					if(considerMemo)
						memoTable[n][k] += tempMemoTable[n - primeList[primeInd]][k - 1];
					else
						tempMemoTable[n][k] += memoTable[n - primeList[primeInd]][k - 1];
				}
			}	
		considerMemo = !considerMemo;
	}

	if(considerMemo)
	{
		// Copy content from tempMemoTable to memoTable
		for(int n = 0; n <= MAX_VAL_N; n++)
			for(int k = 0; k <= MAX_PART; k++)
				memoTable[n][k] = tempMemoTable[n][k];
	}
}
