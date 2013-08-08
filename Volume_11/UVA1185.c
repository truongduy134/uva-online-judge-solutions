#include <stdio.h>
#include <math.h>

int calculateNumDigitOfFactorial(int n);

int main(void)
{
	int T, n;

	scanf("%d", &T);
	while(T)
	{
		scanf("%d", &n);

		printf("%d\n", calculateNumDigitOfFactorial(n));
		T--;
	}
	return 0;
}

/*
 * Logarithm formula: The number of digits of a natural number N >= 1 is given by this formula:
 *			floor( log10 ( N ) + 1 )
 *
 * Therefore, the number of digits of N! (N >= 1) is:
 *			floor( log10 ( N! ) + 1) 
 *		     =  floor( log10(1) + log10(2) + ... + log10(N) + 1)
 *
 * Alternative approach: Using Stirling approximation, we have
 *		ln (N!) = n * ln(n) - n + 1/2 * ln ( 2 * PI * n ) + 1 / (12 * n)
 *
 * Also, PI = 2 * PI / 2 = 2 * acos(0) and log10 (N) = ln N / ln 10
 */
int calculateNumDigitOfFactorial(int n)
{
	if(n <= 3)
		return 1;

	double stirlingApprox = n * log(n) - n + 0.5 * log(2 * 2 * acos(0) * n) + 1 / (12.0 * n);

	return (int) floor(stirlingApprox / log(10.0) + 1);
}

