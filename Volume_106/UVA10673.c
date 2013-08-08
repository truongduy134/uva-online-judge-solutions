#include <stdio.h>

/* Problem: Find p and q such that
 *		x = p * floor(x / k) + q * ceil(x / k)	(x, k > 0)
 *
 * Methodology:
 *	+ Let q = x % k.
 *	+ If x >= k
 *		+ p = (x - q) / floor(x / k) - q
 *	+ Otherwise, p = 0
 */

int main(void)
{
	int x, k, T, p, q;

	scanf("%d", &T);

	while(T)
	{
		scanf("%d %d", &x, &k);

		q = x % k;
		if(x >= k)
			p = (x - q) / (x / k) - q;
		else
			p = 0;
		printf("%d %d\n", p, q);

		T--;
	}

	return 0;
}
