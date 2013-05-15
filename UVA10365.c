/***********************************
 * Author: Nguyen Truong Duy
 ***********************************/

#include <stdio.h>

/* Methodology:
 * 	+ The problem can be rephrased as:
 *		Find integers a <= b <= c such that
 *			abc = N
 *			2(ab + bc + ca) is minimum.
 *	+ Use brute force approach.
 *	+ Time complexity: O(N ^ (2 / 3) )
 */

int findMinSurfaceArea(int V);
int computeSurfaceArea(int a, int b, int c);

int main(void)
{
	int T, numBlock;

	scanf("%d", &T);

	while(T)
	{
		scanf("%d", &numBlock);
		printf("%d\n", findMinSurfaceArea(numBlock));
		T--;
	}
	return 0;
}

int findMinSurfaceArea(int V)
{
	int minSurfaceArea = V * V * V, a, b, c, temp, area;

	for(a = 1; a * a * a <= V; a++)
		for(b = a; a * b * b <= V; b++)
		{
			temp = a * b;
			if(V % temp == 0)
			{
				c = V / temp;
				area = computeSurfaceArea(a, b, c);

				if(area < minSurfaceArea)
					minSurfaceArea = area;
			}
		}

	return area;
}

int computeSurfaceArea(int a, int b, int c)
{
	return (a * b + b * c + a * c) << 1;
}
