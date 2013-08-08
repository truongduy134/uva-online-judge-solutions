#include <stdio.h>

/* The original problem is equivalent to the following problem:
 *	+ Given a natural number M and n rows
 *	+ The i-th row contains k(i) integers.
 *	+ Let us denote a(i, j) be the j-th integer on the i-th row.
 *	+ We are to compute:
 *		(a(1, 1) * ... * a(1, k(1)) + a(2, 1) * ... a(2, k(2)) + ... + a(n, 1) * ...
 *						a(n, k(n)) ) % M 
 */
int main(void)
{
	int T, mod, numRow, numCol, rowProductMod, sumMod, row, col, num;

	scanf("%d", &T);

	while(T)
	{
		scanf("%d %d", &mod, &numRow);

		sumMod = 0;
		
		for(row = 0; row < numRow; row++)
		{
			rowProductMod = 1;
			
			scanf("%d", &numCol);
			for(col = 0; col < numCol; col++)
			{
				scanf("%d", &num);
				rowProductMod = (rowProductMod * num % mod) % mod;
			}

			sumMod = (sumMod + rowProductMod) % mod;
		}

		printf("%d\n", sumMod);
		T--;
	}
	return 0;
}
