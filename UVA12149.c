#include <stdio.h>

int countNumSubsquare(int subsquareSide, int squareSide);

int main(void)
{
	int squareSide, numSubsquare, side;

	while(1)
	{
		scanf("%d", &squareSide);
		if(squareSide == 0)
			break;

		numSubsquare = 0;
		for(side = 1; side <= squareSide; side++)
			numSubsquare += countNumSubsquare(side, squareSide);

		printf("%d\n", numSubsquare);
	}

	return 0;
}

/* Count the number of sub-squares of size m x m inside the n x n square */
int countNumSubsquare(int subsquareSide, int squareSide)
{
	if(subsquareSide > squareSide)
		return 0;

	return (squareSide - subsquareSide + 1) * (squareSide - subsquareSide + 1);
}
