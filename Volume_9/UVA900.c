#include <stdio.h>

/* Methodology:
 *	f(n) = the number of patterns for a wall of length n
 *	Then f(n) = f(n - 1) + f(n - 2)
 *	     f(1) = 1, f(2) = 2
 */

#define MAX_LENGTH 50

int main(void)
{
	unsigned long int numPatternArr[MAX_LENGTH + 1];
	int n;

	numPatternArr[0] = 0;
	numPatternArr[1] = 1;
	numPatternArr[2] = 2;

	for(n = 3; n <= MAX_LENGTH; n++)
		numPatternArr[n] = numPatternArr[n - 1] + numPatternArr[n - 2];

	while(1)
	{
		scanf("%d", &n);
		if(n == 0)
			break;

		printf("%lu\n", numPatternArr[n]);
	}

	return 0;	
}
