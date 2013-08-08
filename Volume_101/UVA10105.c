#include <stdio.h>

#define MAX_NUM 12

void computeFactorial(int factorial[], int n);
int computeCoeffMultinomial(int n, int k, int expo[], int factorial[]);

int main(void)
{
	int factorial[MAX_NUM + 1], n, k, expo[MAX_NUM], i;

	computeFactorial(factorial, MAX_NUM + 1);

	while(scanf("%d %d", &n, &k) > 0)
	{
		for(i = 0; i < k; i++)
			scanf("%d", &expo[i]);

		printf("%d\n", computeCoeffMultinomial(n, k, expo, factorial));
	}
	return 0;
}

void computeFactorial(int factorial[], int n)
{
	int i;

	factorial[0] = 1;
	for(i = 1; i <= n; i++)
		factorial[i] = i * factorial[i - 1];
}

int computeCoeffMultinomial(int n, int k, int expo[], int factorial[])
{
	int result = factorial[n], i;

	for(i = 0; i < k; i++)
		result /= factorial[expo[i]];

	return result;
}
