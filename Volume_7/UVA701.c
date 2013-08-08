/*******************************************************************************
 * Author: Nguyen Truong Duy
 ********************************************************************************/

/* Methodology
 *	+ Given an integer N, the problem asks us to find an integer E such that
 *		2^E = N * 10^x + B
 *	  where x > H(2^E) / 2 and B < 10^x, H(m) denotes the number of digits in m
 *
 *	+ Note that such an E ALWAYS EXISTS.
 *
 *	+ Since 0 <= B < 10^x, we have
 *		N * 10^x <= 2^E < (N + 1) * 10^x
 *	+ Taking logrithm base 2 (denoted as log2) at both sides, we have
 *		x * log2(10) + log2(N) <= E < x * log2(10) + log2(N + 1)
 *	+ Because E is an integer, we have:
 *		ceil(x * log2(10) + log2(N)) <= E < floor(x * log2(10) + log2(N + 1))
 *	+ Denote F(x) = ceil(x * log2(10) + log2(N)) and
 *		 G(x) = floor(x * log2(10) + log2(N + 1))
 *	+ Then we iterate from x = 1 onwards to find minimum x0 such that
 *		 - F(x0) <= G(x0)
 *		 - 2 * x0 > H(2^E) where H(m) denotes the number of digits in m
 *		   Explicitly, H(2^E) = E * floor(log10(2)) + 1
 *	  Then E = F(x0) is the value we are looking for.
 */

#include <math.h>
#include <stdio.h>

int getPowTwo(unsigned int num);

int main(void)
{
	unsigned int num;

	while(scanf("%u", &num) > 0)
	{
		printf("%d\n", getPowTwo(num));
	}
	return 0;
}

int getPowTwo(unsigned int num)
{
	double logTwoTen = log10(2.0);
	int x = 1;

	double lower, upper;
	int numDigit;
	while(1)
	{
		lower = ceil(x * 1.0 / logTwoTen + log10(num * 1.0) / logTwoTen);
		upper = floor(x * 1.0 / logTwoTen + log10((num + 1) * 1.0) / logTwoTen);

		if(lower <= upper)
		{
			numDigit = (int) floor(lower * logTwoTen) + 1;
			if(x * 2 > numDigit)
				return (int) lower;
		}

		x++;	 
	}
}
