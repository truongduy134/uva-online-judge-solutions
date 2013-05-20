/*******************************************************
 * Author: Nguyen Truong Duy
 *******************************************************/

/* Methodology:
 *	+ Use backtracking
 */

#include <cstdio>
#include <list>
#include <vector>
#include <iterator>

using namespace std;

const int MAX_NUM = 32;

void printAllPrimeRing(int n, int bitmask, list<int> & primeRing, const vector<bool> & isPrimeSieve);
void generatePrimeSieve(vector<bool> & isPrimeSieve, int upperBound);

int main(void)
{
	int n, caseId, bitmask;
	list<int> primeRing;
	vector<bool> isPrimeSieve;

	generatePrimeSieve(isPrimeSieve, MAX_NUM);

	caseId = 1;
	while(scanf("%d", &n) > 0)
	{
		if(caseId > 1)
			printf("\n");

		primeRing.clear();
		primeRing.push_back(1);
		
		printf("Case %d:\n", caseId);
		bitmask = 1;
		printAllPrimeRing(n, bitmask, primeRing, isPrimeSieve); 

		caseId++;
	}
	return 0;
}

void generatePrimeSieve(vector<bool> & isPrimeSieve, int upperBound)
{
	isPrimeSieve.assign(upperBound, true);

	isPrimeSieve[0] = isPrimeSieve[1] = false;

	for(int n = 2; n < upperBound; n++)
		if(isPrimeSieve[n])
		{
			for(int multipleN = n + n; multipleN < upperBound; multipleN += n)
				isPrimeSieve[multipleN] = false;
		}
}

void printAllPrimeRing(int n, int bitmask, list<int> & primeRing, const vector<bool> & isPrimeSieve)
{
	
	if(bitmask == ((1 << n) - 1))
	{
		// Check if the sum of the beginning and ending of a list is a prime
		list<int>::iterator itBegin = primeRing.begin();
		list<int>::reverse_iterator itEnd = primeRing.rbegin();
		if(!isPrimeSieve[(*itBegin) + (*itEnd)])
			return;

		// Print the current prime ring
		bool first = true;
		for(list<int>::iterator it = primeRing.begin(); it != primeRing.end(); it++)
		{
			if(it != primeRing.begin())
				printf(" ");
			printf("%d", *it);
		}
		printf("\n");
		return;
	}

	
	list<int>::iterator itEnd = primeRing.end();
	itEnd--;
	int endList = *itEnd;
	for(int pos = 0; pos < n; pos++)
		if((bitmask & (1 << pos)) == 0)
		{
			// Not chosen yet
			int nextN = pos + 1;
			if(isPrimeSieve[nextN + endList])
			{
				primeRing.push_back(nextN);
				printAllPrimeRing(n, bitmask | (1 << pos), primeRing, isPrimeSieve);
				// Restore the state
				primeRing.pop_back();
			}
		}
}
