#include <stdio.h>

#define MAX_SIZE 200

int getPowerSequence(int n, int base, int powerSequence[]);

int main(void)
{
	int n, base, powerSequence[MAX_SIZE], lenSeq, i;

	while(scanf("%d %d", &n, &base) > 0)
	{
		lenSeq = getPowerSequence(n, base, powerSequence);
	
		if(lenSeq < 0)
			printf("Boring!\n");
		else
		{
			printf("%d", powerSequence[0]);
			for(i = 1; i < lenSeq; i++)
				printf(" %d", powerSequence[i]);
			printf("\n");
		}
	}
	return 0;
}

int getPowerSequence(int n, int base, int powerSequence[])
{
	if(n < 2 || base < 2)
		return -1;

	int len;
	powerSequence[0] = n;

	len = 1;
	while(n % base == 0)
	{
		n /= base;
		powerSequence[len] = n;
		len++;
	}

	if(n != 1)
		return -1;
	return len;
}
