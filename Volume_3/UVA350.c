/*******************************************************************************
 * Author: Nguyen Truong Duy
 ********************************************************************************/

/* Methodology:
 *	+ This problem asks us to find the length of the cycle in pseudo-random
 *		number generation.
 *	+ We can use Floyd's cycle finding algorithm.
 *	+ Time complexity: O(U + L) where U is the start of the cycle and L
 *		is the length of the cycle.
 */

#include <stdio.h>

int getPseudoRandom(int Z, int L, int I, int M);
int findCycleLength(int Z, int I, int L, int M);

int main(void)
{
	int Z, L, I, M, caseId;

	caseId = 1;
	while(1)
	{
		scanf("%d %d %d %d", &Z, &I, &M, &L);
		if(Z == 0 && I == 0 && M == 0 && L == 0)
			break;

		printf("Case %d: %d\n", caseId, findCycleLength(Z, I, L, M));
		caseId++;
	}
	return 0;
}

/* Compute (Z x L + I) mod M */
int getPseudoRandom(int Z, int L, int I, int M)
{
	return (((Z * L) % M) + I % M) % M;
}

int findCycleLength(int Z, int I, int L, int M)
{
	int slow = L;
	int fast = L;

	do
	{
		slow = getPseudoRandom(Z, slow, I, M);
		fast = getPseudoRandom(Z, fast, I, M);
		fast = getPseudoRandom(Z, fast, I, M);
	} while(slow != fast);

	/* Calculate the start of a cycle */
	fast = L;
	while(fast != slow)
	{
		slow = getPseudoRandom(Z, slow, I, M);
		fast = getPseudoRandom(Z, fast, I, M);
	}

	/* Calculate the length of the cycle */
	fast = getPseudoRandom(Z, slow, I, M);
	int cycleLength = 1;
	while(fast != slow)
	{
		cycleLength++;
		fast = getPseudoRandom(Z, fast, I, M);
	}

	return cycleLength;
}
