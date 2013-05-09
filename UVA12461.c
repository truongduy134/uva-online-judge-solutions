#include <stdio.h>

/*
 * Let A(n) be the event the n-th person finds his seat occupied when the 1st person chooses a seat randomly and there are n people for n >= 2.
 *
 * Base case: We can verify that Pr(A(2)) = Pr(A(3)) = 1/2
 *
 * We will prove Pr(A(n)) = 1/2 for n >= 2 by induction
 *
 * Assume Pr(A(k)) = 1/2 for all 2 <= k < n.
 *
 * Note that if the first person chooses the 1st seat, then the n-th person will sit at his own seat.
 * So Pr(A(n)) = sum ( Pr (the first person choose the i-th seat and the n-th person finds his seat occupied) (for i = 2, ... n)
 *	       = sum ( 1/n * (Pr (the i-th person chooses the j-th seat and the n-th person finds his seat occupied) (for i = 2, ... n)
 *	       = 1/n * (sum ( A(k) ) + 1 ) for k = 2, ... , n - 1 (When the 1st person choose the n-th seat with probability 1/n, surely the n-th person finds his seat occupied)
 *	       = 1/n * ( (n - 2) * 1/2 + 1) = 1/2  
 */
int main(void)
{
	int n;

	while(1)
	{
		scanf("%d", &n);
		if(n == 0)
			break;
		printf("1/2\n");
	}
	return 0;
}


