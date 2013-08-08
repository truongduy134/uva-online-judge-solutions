#include <stdio.h>
#include <string.h>

/* Methodology:
 *	+ The number of perfect squares existing between 1 and A is
 *			sqrt(A)
 *	+ Note that we have to output the most significant digit of the result only.
 *	+ Let A be an n-digit number.
 *	+ Hence, if n = 2k, the result is
 *			sqrt(a1a2) * 10^(k - 1)
 *		where a1, a2 are the first two digits of A.
 *	+ If n = 2k + 1, the result is
 *			sqrt(a1) * 10^k
 */

#define MAX_LEN 2000

void getNumberOfPerfectSquareLeadingDigit(char numStr[], char sqrtStr[]);

int main(void)
{
	char numStr[MAX_LEN + 1], sqrtStr[MAX_LEN + 1];

	while(1)
	{
		scanf("%s", numStr);
		if(numStr[0] == '0')
			break;

		getNumberOfPerfectSquareLeadingDigit(numStr, sqrtStr);

		printf("%s\n", sqrtStr);
	}

	return 0;
}

/* Assumption: numStr has length >= 1 */
void getNumberOfPerfectSquareLeadingDigit(char numStr[], char sqrtStr[])
{
	int length = (int) strlen(numStr);

	int numToSqrt, numTrailingZero;
	char leadingDigit;
	int ind;

	if(length & 1)
	{
		numToSqrt = (int) numStr[0] - '0';
		numTrailingZero = (length - 1) >> 1;
	}
	else
	{
		numToSqrt = (numStr[0] - '0') * 10 + (numStr[1] - '0');
		numTrailingZero = (length >> 1) - 1;
	}

	
	for(leadingDigit = 1; leadingDigit * leadingDigit <= numToSqrt; leadingDigit++)
	{
	}
	leadingDigit--;
	leadingDigit += '0';

	sqrtStr[0] = leadingDigit;
	
	for(ind = 1; ind <= numTrailingZero; ind++)
		sqrtStr[ind] = '0';
	sqrtStr[ind] = '\0';
}
