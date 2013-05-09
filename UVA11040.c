#include <stdio.h>

#define MAX_SIZE 9

int main(void)
{
	int grid[MAX_SIZE][MAX_SIZE], T, r, c;

	scanf("%d", &T);

	while(T)
	{
		for(r = 0; r < MAX_SIZE; r += 2)
			for(c = 0; c <= r; c += 2)
				scanf("%d", &grid[r][c]);

		for(r = 2; r < MAX_SIZE; r += 2)
			for(c = 1; c <= r; c += 2)
				grid[r][c] = (grid[r - 2][c - 1] - grid[r][c - 1] - grid[r][c + 1]) >> 1;

		for(r = 1; r < MAX_SIZE; r += 2)
			for(c = 0; c <= r; c++)
				grid[r][c] = grid[r + 1][c] + grid[r + 1][c + 1];

		for(r = 0; r < MAX_SIZE; r++)
		{
			printf("%d", grid[r][0]);

			for(c = 1; c <= r; c++)
				printf(" %d", grid[r][c]);

			printf("\n");
		}
		T--;
	}	
	return 0;
}
