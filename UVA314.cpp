#include <queue>
#include <cstdio>

using namespace std;

enum Direction {
	NORTH = 0, SOUTH = 1, WEST = 2, EAST = 3
};

#define MAX_SIZE 50
#define NUM_DIRECT 4

int xDirect[NUM_DIRECT] = {0, 0, -1, 1};
int yDirect[NUM_DIRECT] = {-1, 1, 0, 0};

int main(void)
{
	int numR, numC, startR, startC, endR, endC, grid[MAX_SIZE][MAX_SIZE], directId;
	char direction[MAX_SIZE];

	while(1)
	{
		scanf("%d %d", &numR, &numC);
		
		if(!(numR || numC))
			break;

		for(int i = 0; i < numR; i++)
			for(int j = 0; j < numC; j++)
				scanf("%d", &grid[i][j]);

		scanf("%d %d %d %d %s", &startR, &startC, &endR, &endC, direction);
		
		
	}
	return 0;
}
