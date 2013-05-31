/*******************************************************************************
 * Author: Nguyen Truong Duy
 ********************************************************************************/

/* Methodology:
 *	+ The comb can be divided into layers
 *	+ The first layer contains 1 only
 *	  The second layer contains 2 - 7. (6 numbers)
 *	  The third layer contains 8 - 19. (12 numbers) and so on.
 *
 *	+ Layer k (except the first layer k = 0) contains 6 * k numbers
 *	  The starting number of layer k (k >= 1) is 6 * (k - 1)
 * 	+ Consider a layer [m ... m + 6k - 1] (k >= 1)
 *	  Then m has Maja coordinate (k - 1, 1)
 *	+ There are 4 important points: m + k - 1, m + 3k + 1, m + 4k - 1, m + 6k - 1 
 *	+ m + k - 1 has coordinate (0, k)
 *	  m + 4k - 1 has coordinate (0, -k)
 *	  m + 6k - 1 has coordinate (k, 0)
 *	  m + 3k - 1 has coordinate (-k, 0)
 *
 *	+ From m to m + 3k - 1,
 *		- x decreases from k - 1 to -k (1 unit at a time)
 *		  x remains at -k once it reaches -k.
 *	+ From m + 3k - 1 to m + 6k - 1
 *		- x increases from -k to k (1 unit at a time)
 *		  x remains at k once it reaches k.
 *	+ From m + 6k - 1 down to m + 4k - 1,
 *		- y decreases from 0 to -k (1 unit at a time)
 *		  y remains at -k once it reaches -k.
 *	+ From m + 4k - 1 down to m + k - 1,
 *		- y increases -k to k (1 unit at a time)
 *		  y remains at k once it reaches k.
 *	+ From m + k - 1 down to m,
 *		- y decreases from k to 1 (1 unit at a time)
 *	
 *	+ So we can have a solution with O(n) pre-processing and O(1) per query  
 */

#include <stdio.h>

typedef struct {
	int x, y;
} MajaCoord;

const int MAX_NUM_VAL = 100000;

void preComputeMapWiliToMajaCoord(MajaCoord mapWilliToMaja[]);

int main(void)
{
	MajaCoord mapWilliToMaja[MAX_NUM_VAL + 1];

	preComputeMapWiliToMajaCoord(mapWilliToMaja);

	int willi;
	while(scanf("%d", &willi) > 0)
	{
		printf("%d %d\n", mapWilliToMaja[willi].x, mapWilliToMaja[willi].y);
	}

	return 0;
}

void preComputeMapWiliToMajaCoord(MajaCoord mapWilliToMaja[])
{
	mapWilliToMaja[1].x = 0;
	mapWilliToMaja[1].y = 0;

	int start = 2, layer = 1, numProcess, i, x, y, end;
	while(start <= MAX_NUM_VAL)
	{
		/* Process each layer */
		/* Pass 1 */
		end = start + 3 * layer - 1;
		x = layer;
		for(i = start; i <= end; i++)
		{
			if(x > -layer)
				x--;
			if(i <= MAX_NUM_VAL)
				mapWilliToMaja[i].x = x;
		}

		/* Pass 2 */
		end = start + 6 * layer - 1;
		x = -layer - 1;
		for(i = start + 3 * layer - 1; i <= end; i++)
		{
			if(x < layer)
				x++;
			if(i <= MAX_NUM_VAL)
				mapWilliToMaja[i].x = x;
		}

		/* Pass 3 */
		end = start + 4 * layer - 1;
		y = 1;
		for(i = start + 6 * layer - 1; i >= end; i--)
		{
			if(y > -layer)
				y--;
			if(i <= MAX_NUM_VAL)
				mapWilliToMaja[i].y = y;
		}

		/* Pass 4 */
		end = start + layer - 1;
		y = -layer - 1;
		for(i = start + 4 * layer - 1; i >= end; i--)
		{
			if(y < layer)
				y++;
			if(i <= MAX_NUM_VAL)
				mapWilliToMaja[i].y = y;
		}

		/* Pass 5 */
		end = start;
		y = layer + 1;
		for(i = start + layer - 1; i >= end; i--)
		{
			if(y > 1)
				y--;
			if(i <= MAX_NUM_VAL)
				mapWilliToMaja[i].y = y;
		}

		/* Go to the next layer */
		start += 6 * layer;
		layer++;
	}
}
