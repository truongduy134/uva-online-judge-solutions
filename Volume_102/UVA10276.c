#include <stdio.h>
#include <math.h>

#define MAX_NUM_PEG 50

/* Methodology: Use greedy approach */

int getMaxNumBallsCanPlaced(int numPeg);
int isSquare(int n);

int main(void)
{
	int T, numPeg;

	scanf("%d", &T);
	while(T)
	{
		scanf("%d", &numPeg);

		printf("%d\n", getMaxNumBallsCanPlaced(numPeg));
		T--;
	}
	return 0;
}

int getMaxNumBallsCanPlaced(int numPeg)
{
	int topPeg[MAX_NUM_PEG], ball, numPegUsed, peg, placed;

	numPegUsed = 0;
	ball = 1;

	while(1)
	{
		placed = 0;
		for(peg = 0; peg < numPegUsed; peg++)
			if(isSquare(ball + topPeg[peg]))
			{
				placed = 1;
				topPeg[peg] = ball;
			}

		if(!placed)
		{
			/* Use a new peg */
			if(numPegUsed < numPeg)
			{
				topPeg[numPegUsed] = ball;
				numPegUsed++;
			}
			else
				return ball - 1;
		}

		ball++;
	}
}

int isSquare(int n)
{
	int root = (int) floor(sqrt(n));

	if(root * root == n)
		return 1;
	return 0;
}
