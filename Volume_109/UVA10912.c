/*******************************************************************************
 * Author: Nguyen Truong Duy
 ********************************************************************************/

/* Methodology:
 *	+ We use dynamic programming to solve this problem.
 *	
 *	+ Let f(l, i, s) = the number of strings which are strictly alphabetically increasing ordered
 *		of length l, and the largest letter we can use has id equals to i ('a' has id 0, 'z' has  
 *		id 25), that has the sum of letters equal to s.
 * 	+ Recurrence relation:
 *		f(l, i, s) = sum( f(l - 1, j - 1, s - (j + 1)) ) where j = 0, ..., i
 *	  That is, we choose the last letter to be of id j (j = 0, ... i) and recurse with the string
 *		of length l - 1 and weight s - (j + 1) (The letter with id j has weight j + 1)
 *
 *	+ Base cases:
 *		f(0, i, 0) = 1
 *		f(0, i, s) = 0 if s > 0
 *		f(l, i, s) = 0 if l > 0 and i < 0
 *		f(l, i, s) = 0 if l < 0 or s < 0
 *
 *	+ Note that since the strings we consider are strictly alphabetically increasing ordered and
 *		the string of length L has the maximum weight of 26 * L. Therefore, we have:
 *		f(l, i, s) = 0 if l > 26 or s > l * 26
 *
 *	+ Time complexity: O(L * S * 26 * 26) where L <= 26 and S <= 26 * 26
 */

#include <stdio.h>
#include <string.h>

#define NUM_ALPHABET 26

int countNumPreimageHash(int length, int maxAlphaId, int weightSum, 
			 int memoTable[NUM_ALPHABET + 1][NUM_ALPHABET][NUM_ALPHABET * NUM_ALPHABET + 1]);

int main(void)
{
	int memoTable[NUM_ALPHABET + 1][NUM_ALPHABET][NUM_ALPHABET * NUM_ALPHABET + 1];

	memset(memoTable, -1, sizeof(memoTable));

	int length, weightSum, caseId;

	caseId = 1;
	while(1)
	{
		scanf("%d %d", &length, &weightSum);
		if(length == 0 && weightSum == 0)
			break;

		printf("Case %d: %d\n", caseId, countNumPreimageHash(length, NUM_ALPHABET - 1, weightSum, memoTable));
		caseId++;
	}
	return 0;	
}

int countNumPreimageHash(int length, int maxAlphaId, int weightSum, 
			 int memoTable[NUM_ALPHABET + 1][NUM_ALPHABET][NUM_ALPHABET * NUM_ALPHABET + 1])
{
	if(length > NUM_ALPHABET || weightSum > length * NUM_ALPHABET)
		return 0;
	if(length == 0)
	{
		if(weightSum == 0)
			return 1;
		return 0;
	}
	if(length < 0 || weightSum <= 0 || maxAlphaId < 0)
		return 0; 
	
	if(memoTable[length][maxAlphaId][weightSum] >= 0)
		return memoTable[length][maxAlphaId][weightSum];

	int id, alphaWeight, numPreimage = 0;
	for(id = 0; id <= maxAlphaId; id++)
	{
		alphaWeight = id + 1;
		if(alphaWeight > weightSum)
			break;

		numPreimage += countNumPreimageHash(length - 1, id - 1, weightSum - alphaWeight, memoTable);
	}

	memoTable[length][maxAlphaId][weightSum] = numPreimage;
	return numPreimage;
}
