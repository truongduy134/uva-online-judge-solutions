#include <stdio.h>
#include <string.h>

#define MAX_SIZE 100
#define MAX_LEN 20

#define ROCK 'r'
#define PAPER 'p'
#define SCISSOR 's'

int determineMatchResult(int idOne, char choiceOne[], int idTwo, char choiceTwo[]);

int main(void)
{
	int numPeople, numRound,  numWinGames[MAX_SIZE], numNotDrawnGames[MAX_SIZE], idOne, idTwo, numTotalGames, i, idWin, isFirst;
	char choiceOne[MAX_LEN + 1], choiceTwo[MAX_LEN + 1];

	isFirst = 1;
	while(1)
	{
		scanf("%d", &numPeople);
		if(numPeople == 0)
			break;
		scanf("%d", &numRound);

		memset(numWinGames, 0, MAX_SIZE * sizeof(int));
		memset(numNotDrawnGames, 0, MAX_SIZE * sizeof(int));

		numTotalGames = (numRound * numPeople * (numPeople - 1)) >> 1;

		for(i = 0; i < numTotalGames; i++)
		{
			scanf("%d %s %d %s", &idOne, choiceOne, &idTwo, choiceTwo);
			idOne--;
			idTwo--;

			idWin = determineMatchResult(idOne, choiceOne, idTwo, choiceTwo);
			
			if(idWin >= 0)
			{
				numWinGames[idWin]++;
				numNotDrawnGames[idOne]++;
				numNotDrawnGames[idTwo]++;

			}
		}

		if(isFirst)
			isFirst = 0;
		else
			printf("\n");
		for(i = 0; i < numPeople; i++)
		{
			if(numNotDrawnGames[i] == 0)
				printf("-\n");
			else
				printf("%.3lf\n", numWinGames[i] * 1.0 / numNotDrawnGames[i]);
		}
	}
	return 0;
}

int determineMatchResult(int idOne, char choiceOne[], int idTwo, char choiceTwo[])
{
	if(choiceOne[0] == choiceTwo[0])
		return -1;	/* Draw */
	if(choiceOne[0] == PAPER && choiceTwo[0] == ROCK)
		return idOne;
	if(choiceOne[0] == ROCK && choiceTwo[0] == SCISSOR)
		return idOne;
	if(choiceOne[0] == SCISSOR && choiceTwo[0] == PAPER)
		return idOne;

	return idTwo;
}
