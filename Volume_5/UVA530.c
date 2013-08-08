/*******************************************************************************
 * Author: Nguyen Truong Duy
 ********************************************************************************/

/* Methodology
 *	+ Since nCk = nC(n - k), we can assume k <= n - k.
 *	  If in the input, n - k < k, we can let k = n - k
 *	+ Special cases:
 *		- If k > n, return 0
 *		- If k = 0, return 1
 *		- If n = 0, return 1
 *
 *	+ Now, nCk = (n * (n - 1) * ... * (n - k + 1)) / (2 * 3 * 4 * ... * k)
 *	+ To be safe, we should use 64-bit integer to hold the intermediate result.
 *	+ The follwing procedure will pass the test cases with the above assumption:
 *		- Initialize result = 1, numer = n and denom = 2
 *		- While numer > n - k do:
 *			Let result = result * numer
 *			While denom <= k and result % denom == 0:
 *				result = result / denom
 *				denom++
 *			numer--
 */

#include <stdio.h>

int ComputeNChooseK(int n, int k);

int main(void)
{
	int n, k;

	while(1)
	{
		scanf("%d %d", &n, &k);
		if(n == 0 && k == 0)
			break;

		printf("%d\n", ComputeNChooseK(n, k));
	}
	return 0;
}

int ComputeNChooseK(int n, int k)
{
	if(k > n)
		return 0;

	if(n - k < k)
		k = n - k;	
	if(k == 0)
		return 1;
	if(n == 0)
		return 1;
	
	unsigned long long int result = 1;
	int numer = n, denom = 2;
	
	while(numer > (n - k))
	{
		result *= (unsigned long long int) numer;
		numer--;
		while((denom <= k) && (result % denom == 0))
		{
			result /= denom;
			denom++;
		}
	}

	return (int) result;	
}
