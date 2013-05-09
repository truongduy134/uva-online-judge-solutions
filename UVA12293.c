/* It can be proved that:
 *	+ Bob wins when N = 2^k - 1 for k >= 2
 *	+ Alice wins otherwise
 */

#include <stdio.h>

#define MAX_BIT 31
#define ALICE 0
#define BOB 1

int main(void)
{
	int n, k, result, temp;

	while(1)
	{
		scanf("%d", &n);
		if(n == 0)
			break;

		result = ALICE;
		for(k = 2; k <= MAX_BIT; k++)
		{
			temp = (1 << k) - 1;
			if(n == temp)
			{
				result = BOB;
				break;
			}
			else
			{
				if(n < temp)
					break;
			}
		}

		if(result == BOB)
			printf("Bob\n");
		else
			printf("Alice\n");
	}

	return 0;
}
