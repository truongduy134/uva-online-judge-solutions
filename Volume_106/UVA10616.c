/*******************************************************
 * Author: Nguyen Truong Duy
 *******************************************************/

/* Methodology:
 *	+ Use dynamic programming (or memoization)
 *
 *	+ Let us define 
 *		f(k, m, d, r) = the number of ways to choose m numbers from the set of k + 1 numbers
 *			(a[0], ..., a[k]) such that the sum of m chosen numbers, S, satisfying S    
 *			mod d = r
 *	+ Then we have the following recurrence:
 *		f(k, m, d, r) = f(k - 1, m, d, r)	// Not choose a[k] into the set
 *			      + f(k - 1, m, d, (r - a[k] mod d) mod d)	// Choose a[k]
 *	
 *	+ We follow the follwing convention of mod for negative numbers:
 *		If a < 0 and d | a, then a mod d = 0
 *		If a < 0 and a is not divisible by d, a mod d = d + (-a mod d)
 *
 *	+ Base case:
 *		f(k, m, d, r) = 0 if k + 1 < m	(because we cannot choose enough m numbers)
 *		f(k, 0, d, 0) = 1
 *		f(k, 0, d, r) = 0 if r != 0
 *
 *	+ Time complexity: O(n * m * d) where n is the size of the orignal set	
 */

#include <stdio.h>
#include <string.h>

const int MAX_SET_SIZE = 200;
const int MAX_CHOOSE_SIZE = 10;
const int MAX_MOD = 20;

long long int countNumSet(int arr[], int lastInd, int numChoose, int remainder, int modNum,
                          long long int memoTable[][MAX_CHOOSE_SIZE + 1][MAX_MOD]);
int getRemainder(int n, int mod);

int main(void)
{
    	int setSize, numQuery, numChoose, mod, caseId, queryId, arr[MAX_SET_SIZE], i;
    	long long int memoTable[MAX_SET_SIZE][MAX_CHOOSE_SIZE + 1][MAX_MOD];

    	caseId = 1;
    	while(1)
    	{
        	scanf("%d %d", &setSize, &numQuery);
        	if(!(setSize || numQuery))
            		break;

        	for(i = 0; i < setSize; i++)
            		scanf("%d", &arr[i]);

		printf("SET %d:\n", caseId);
        	for(queryId = 1; queryId <= numQuery; queryId++)
        	{
            		scanf("%d %d", &mod, &numChoose);

			memset(memoTable, -1, MAX_SET_SIZE * (MAX_CHOOSE_SIZE + 1) * MAX_MOD * sizeof(long long int));

            		printf("QUERY %d: %lld\n", queryId, countNumSet(arr, setSize - 1, numChoose, 0, mod, memoTable));
        	}

        	caseId++;
    	}
    	return 0;
}

long long int countNumSet(int arr[], int lastInd, int numChoose, int remainder, int modNum,
                          long long int memoTable[][MAX_CHOOSE_SIZE + 1][MAX_MOD])
{
    	int r, nextR;

    	if(numChoose == 0)
    	{
        	if(remainder == 0)
            		return 1;
        	return 0;
    	}

    	/* Base cases */
    	if(lastInd + 1 < numChoose)
        	return 0;       /* Cannot choose numChoose numbers */

	if(memoTable[lastInd][numChoose][remainder] >= 0)
		return memoTable[lastInd][numChoose][remainder];

    	long long int numSet = 0;

    	/* Not taking this element */
    	numSet += countNumSet(arr, lastInd - 1, numChoose, remainder, modNum, memoTable);

    	/* Choose this element */
    	r = getRemainder(arr[lastInd], modNum);

    	nextR = remainder - r;
    	if(nextR < 0)
        	nextR = modNum + nextR;
    	numSet += countNumSet(arr, lastInd - 1, numChoose - 1, nextR, modNum, memoTable);

    	memoTable[lastInd][numChoose][remainder] = numSet;
    	return numSet;
}

int getRemainder(int n, int mod)
{
	int r = n % mod;
	if(r < 0)
		r = mod + r;
	return r;
}
