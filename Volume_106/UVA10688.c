/*******************************************************************************
 * Author: Nguyen Truong Duy
 ********************************************************************************/

/* Methodology:
 *	+ Key observation: 
 *		- Suppose we want to find a sweet apple among n apples with weight offset k. 
 *		- After trying the i-th apple, we find that it is sour.
 *		  So the problem now becomes finding a sweet apple among
 *			i + 1, i + 2, ..., n with weight offset k.
 *		- This is equivalent to finding a sweet apple among n - i apples with weight
 *		  offset k + i.
 *
 *	+ Let f(n, k) = the minimum sum of apple weights the giant must eat to find a sweet apple
 *		among n apples with weight offset k (i.e. The i-th apple weights i + k)
 *		in all cases assuming such a sweet apple exists
 *	+ Recurrence relation:
 *		Let us eat the i-th apple.
 *		* If the i-th apple is SWEET, then stop. So the amount we eat is w(i)
 *		  (weight of the i-th apple)
 *		* If the i-th apple is BITTER, then a sweet apple may be among apples i + 1, ..., n
 *		  By the key observation, the minimum amount to eat to find the sweet apple among
 *		  i + 1, ..., n is f(n - i, k + i).
 *		  Also, in each of these (n - i) cases (because the sweet apple can be either i + 1
 *		  i + 2, ..., n), we must eat the i-th apple first.
 *		  So totally we eat w(i) * (n - i) + f(n - i, k + i)
 *		* If the i-th apple is SOUR, then the sweet apple may be among apples 1, ..., i - 1
 *	          The minimum amount to eat to find the sweet apple among 1, ..., i - 1 is
 *			f(i - 1, k)
 *		  So totally we eat w(i) * (i - 1) + f(i - 1, k).
 *		* Hence, in total, we eat 
 *			F(i) = w(i) + w(i) * (n - i) + f(n - i, k + i) 
 *				    + w(i) * (i - 1) + f(i - 1, k)
 *		  in all cases to find the sweet apple if we start our strategy by eating the
 *		  i-th apple.
 *		So f(n, k) = min F(i) for i = 1, ..., n.
 *
 *	+ Base case:
 *		f(0, k) = INFINITY
 *		f(1, k) = 0 (because we are guaranteed there is always a sweet apple)
 *	
 *	+ Time complexity: O(n * (n + k) * n)
 */

#include <stdio.h>
#include <string.h>

const int MAX_NUM_APPLE = 500;
const int MAX_NUM_WEIGHT = 500;
const int INFINITY = 1000000000;

int findMinSumWeight(int numApple, int weightOffset, int memo[][MAX_NUM_WEIGHT + 1]);

int main(void)
{
	int numApple, offset, T, caseId, memo[MAX_NUM_APPLE + 1][MAX_NUM_WEIGHT + 1];

	scanf("%d", &T);
	caseId = 1;
	
	memset(memo, -1, (MAX_NUM_APPLE + 1) * (MAX_NUM_WEIGHT + 1) * sizeof(int));
	while(caseId <= T)
	{
		scanf("%d %d", &numApple, &offset);
		
		printf("Case %d: %d\n", caseId, findMinSumWeight(numApple, offset, memo));
		caseId++;
	}
	return 0;
}

int findMinSumWeight(int numApple, int weightOffset, int memo[][MAX_NUM_WEIGHT + 1])
{
	if(numApple == 1)
		/* This is the sweet apple. No need to try */
		return 0;
	if(memo[numApple][weightOffset] > 0)
		return memo[numApple][weightOffset];

	int minSumWeight = INFINITY, sumWeight, appleId, appleWeight;

	for(appleId = 1; appleId <= numApple; appleId++)
	{
		appleWeight = appleId + weightOffset;

		sumWeight = 0;
		/* Case 1: This apple is sweet */
		sumWeight += appleWeight;

		/* Case 2: This apple is bitter.
		 * Note that the last apple cannot be bitter.
		 * Otherwise there is no sweet apple
		 */
		if(appleId < numApple)
			sumWeight += appleWeight * (numApple - appleId) +
				findMinSumWeight(numApple - appleId, weightOffset + appleId, memo);
		
		/* Case 3: This apple is sour.
 		 * Note that the first apple cannot be sour.
		 * Otherwise there is no sweet apple */
		if(appleId > 1)
			sumWeight += appleWeight * (appleId - 1) +
				findMinSumWeight(appleId - 1, weightOffset, memo);

		if(minSumWeight > sumWeight)
			minSumWeight = sumWeight;
	}

	memo[numApple][weightOffset] = minSumWeight;
	return minSumWeight;
}
