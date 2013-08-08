/*******************************************************************************
 * Author: Nguyen Truong Duy
 ********************************************************************************/

/* Methodology:
 *	+ We can derive the following formula:
 *		1^3 + 2^3 + ... + n^3 = ( n * (n + 1) / 2) ^ 2
 *	+ So we have an O(1) solution.
 *
 * Note: since n <= 10^5, we should use long long int (64-bit integer type)
 */

#include <stdio.h>

long long int computeCubeSum(int n);
long long int computeSquare(long long int n);

int main(void)
{
	int N;

	while(scanf("%d", &N) > 0)
	{
		printf("%lld\n", computeCubeSum(N));
	}

	return 0;	
}

/* Return 1^3 + 2^3 + ... + n^3 */
long long int computeCubeSum(int n)
{
	long long int cpyN = n;

	return computeSquare( (cpyN * (cpyN + 1)) >> 1); 
}

long long int computeSquare(long long int n)
{
	return n * n;
}
