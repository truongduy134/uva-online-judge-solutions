#include <stdio.h>

long long int computeCombination(int n, int k);

int main()
{
	int n, k;

	while(1)
	{
		scanf("%d %d", &n, &k);
		if(n == 0 && k == 0)
			break;

		printf("%d things taken %d at a time is %lld exactly.\n", n, k, computeCombination(n, k));
 
	}
	return 0;
}

long long int computeCombination(int n, int k)
{
	long long int combination, denom, numer;

	if(2 * k > n)
		k = n - k;

	combination = 1;
	numer = n - k + 1;
	denom = 2;

	while(numer <= n)
	{
		combination *= numer;
		while(denom <= k && combination % denom == 0)
		{
			combination /= denom;
			denom++;
		}		
		numer++;
	}

	return combination;	
}
