/*******************************************************************************
 * Author: Nguyen Truong Duy
 *******************************************************************************/

/* Methodology:
 *	+ Let D = N - floor(N / 10)
 * 	+ Then 10D = 10N - 10 floor(N / 10)
 *	+ Note that 10 floor(N / 10) = N - a (where a = 0, ..., 9)
 *	+ Hence we have an O(1) solution to find N given D.
 *  	  The set of possible values of N is
 *		{N = (10D - a) / 9 | a = 0 ... 9 and 10D - a is divisible by 9}	
 *
 * Since D can be as large as 10^18, 10D can be as large as 10^19. We should use
 *	UNSIGNED 64-bit integers
 * 
 * Observation to reduce the number of iterations from 10 to at most 2:
 *	+ We must have 10D - a (where a = 0, ... 9) is divisible by 9
 *	+ If D % 9 = 0, then a = 0 or 9
 *	+ If D % 9 = x > 0, then a can only be x
 *	+ Hence, if D % 9 = 0, N = 10 * (D / 9) or N = 10 * (D / 9) - 1
 *		 if D % 9 = a, N = (10 * D - a) / 9 = D + (D - a) / 9
 */

#include <stdio.h>

const int MAX_NUM_SOL = 10;

int main(void)
{
	unsigned long long int diff, mod;
	unsigned long long int possibleVal[MAX_NUM_SOL];
	int numSol, i;

	while(1)
	{
		scanf("%llu", &diff);
		if(!diff)
			break;

		numSol = 0;
		mod = diff % 9;

		if(mod == 0)
		{
			possibleVal[numSol] = 10 * (diff  / 9) - 1;
			numSol++;
		}
		possibleVal[numSol] = diff + (diff - mod) / 9;
		numSol++;

		for(i = 0; i < numSol; i++)
		{
			if(i > 0)
				printf(" ");
			printf("%llu", possibleVal[i]);
		}
		printf("\n");
	}
	return 0;
}
