#include <stdio.h>
#include <math.h>

int computeDigitOfCombination(int n, int k);

int main(void)
{
	int n, k;

	while(scanf("%d %d", &n, &k) > 0)
	{
		printf("%d\n", computeDigitOfCombination(n, k));
	}
	return 0;
}

int computeDigitOfCombination(int n, int k)
{
	if(k >= n || k == 0)
		return 1;
	
	if(n - k < k)
		k = n - k;

	double result, numer = (double) n, denom = (double) k,
               lowerBound = (double) n - k;

	result = 0;
	while(numer > lowerBound && numer > 1)
	{
		result += log10(numer);
		numer--;
	}

	while(denom > 1)
	{
		result -= log10(denom);
		denom--;
	}

	return (int) (floor(result + 1));
}
