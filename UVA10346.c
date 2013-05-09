#include <stdio.h>

int main(void)
{
	unsigned long long int n, k, total, numSmoked;

	while(scanf("%llu %llu", &n, &k) > 0)
	{
		total = n;
		numSmoked = n;

		while(numSmoked >= k)
		{
			total += numSmoked / k;
			numSmoked = numSmoked / k + numSmoked % k;
		}

		printf("%llu\n", total);
	}
	return 0;
}
