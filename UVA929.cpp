#include <cstdio>
#include <queue>
#include <vector>
#include <utility>

using namespace std;

#define MAX_SIZE 1000
#define NUM_DIRECT 4
#define INFINITY 100000000
int xDirect[NUM_DIRECT] = {0, 0, 1, -1};
int yDirect[NUM_DIRECT] = {1, -1, 0, 0};

bool isValid(int r, int c, int numR, int numC)
{
	if(r < 0 || c < 0 || r >= numR || c >= numC)
		return false;
	return true;
}

int computeShortestPath(int grid[][MAX_SIZE], int numR, int numC, int startR, int startC, int endR, int endC)
{
	int shortestDist[numR][numC];
	for(int i = 0; i < numR; i++)
		for(int j = 0; j < numC; j++)
			shortestDist[i][j] = INFINITY;

	priority_queue<pair<int, pair<int, int> >, vector<pair<int, pair<int, int> > >, greater<pair<int, pair<int, int> > > > PQueue;

	shortestDist[startR][startC] = grid[startR][startC];
	PQueue.push(make_pair(grid[startR][startC], make_pair(startR, startC)));

	pair<int, pair<int, int> > curState;
	int dist, curR, curC, nextR, nextC;

	while(!PQueue.empty())
	{
		curState = PQueue.top();
		PQueue.pop();

		dist = curState.first;
		curR = curState.second.first;
		curC = curState.second.second;

		if(dist == shortestDist[curR][curC])
		{
			if(curR == endR && curC == endC)
				return dist;

			for(int i = 0; i < NUM_DIRECT; i++)
			{
				nextR = curR + yDirect[i];
				nextC = curC + xDirect[i];
				if(isValid(nextR, nextC, numR, numC))
				{
					if(dist + grid[nextR][nextC] < shortestDist[nextR][nextC])
					{
						shortestDist[nextR][nextC] = dist + grid[nextR][nextC];
						PQueue.push(make_pair(shortestDist[nextR][nextC], make_pair(nextR, nextC)));
					}
				}
			}
		}				
	}

	return 0;	// Dummy
}

int main(void)
{
	int T, numR, numC, grid[MAX_SIZE][MAX_SIZE];

	scanf("%d", &T);
	while(T)
	{
		scanf("%d %d", &numR, &numC);

		for(int i = 0; i < numR; i++)
			for(int j = 0; j < numC; j++)
				scanf("%d", &grid[i][j]);

		printf("%d\n", computeShortestPath(grid, numR, numC, 0, 0, numR - 1, numC - 1));
		T--;
	}
	return 0;
}
