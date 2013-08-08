#include <stdio.h>
#include <string.h>

#define UPPER_BOUND 1000000

int reverseNum(int num);
void preparePrimeSieve(int primeSieve[], int upperbound);

int main(void)
{
	int primeSieve[UPPER_BOUND], n, reverseN;

	preparePrimeSieve(primeSieve, UPPER_BOUND);

	while(scanf("%d", &n) > 0)
	{
		if(primeSieve[n])
		{
			reverseN = reverseNum(n);
			if(reverseN != n && primeSieve[reverseN])
				printf("%d is emirp.\n", n);
			else
				printf("%d is prime.\n", n);
		}
		else
			printf("%d is not prime.\n", n);
	}
	return 0;
}

int reverseNum(int num)
{
	int reverse = 0;

	while(num)
	{
		reverse = reverse * 10 + num % 10;
		num /= 10;
	}

	return reverse;
}

void preparePrimeSieve(int primeSieve[], int upperbound)
{
	int n, multipleN;

	memset(primeSieve, 1, upperbound * sizeof(int));
	
	primeSieve[0] = 0;
	primeSieve[1] = 0;

	for(n = 2; n < upperbound; n++)
		if(primeSieve[n])
		{
			multipleN = n + n;
			while(multipleN < upperbound)
			{
				primeSieve[multipleN] = 0;
				multipleN += n;
			}
		}
}
