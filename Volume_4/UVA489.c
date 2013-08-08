/*******************************************************************************
 * Author: Nguyen Truong Duy
 ********************************************************************************/

#include <stdio.h>
#include <ctype.h>

const int NUM_LETTER = 26;
const int MAX_LEN_STR = 1000;
const int MAX_NUM_WRONG = 6;	/* The hanged man figure takes 7 stroke to complete */
const int PRESENT = 1;
const int NO_PRESENT = 0;
const int ALREADY_GUESSED = 2;
const int WIN = 1;
const int LOSE = 0;
const int DRAW = 2;

int simulateHangedManGame(char answer[], char guess[]);

int main(void)
{
	int caseId, result;
	char answer[MAX_LEN_STR + 1], guess[MAX_LEN_STR + 1];
	
	while(1)
	{
		scanf("%d", &caseId);
		if(caseId < 0)
			break;

		scanf("%s %s", answer, guess);

		result = simulateHangedManGame(answer, guess);

		printf("Round %d\n", caseId);
		if(result == WIN)
			printf("You win.\n");
		else
		{
			if(result == LOSE)
				printf("You lose.\n");
			else
				printf("You chickened out.\n");
		}
	}
	return 0;
}

int simulateHangedManGame(char answer[], char guess[])
{
	int letterState[NUM_LETTER], i, numCorrectToWin, numWrong, numCorrect, letterInd;

	for(i = 0; i < NUM_LETTER; i++)
		letterState[i] = NO_PRESENT;
	for(i = 0; answer[i] != '\0'; i++)
		letterState[(int) answer[i] - 'a'] = PRESENT;

	numCorrectToWin = 0;
	for(i = 0; i < NUM_LETTER; i++)
		if(letterState[i] == PRESENT)
			numCorrectToWin++;

	numWrong = 0;
	numCorrect = 0;
	for(i = 0; guess[i] != '\0'; i++)
	{
		letterInd = (int) guess[i] - 'a';
		if(letterState[letterInd] == ALREADY_GUESSED)
			continue;

		if(letterState[letterInd] == PRESENT)
			numCorrect++;
		else
			numWrong++;
		letterState[letterInd] = ALREADY_GUESSED;

		if(numCorrect >= numCorrectToWin)
			return WIN;
		if(numWrong > MAX_NUM_WRONG)
			return LOSE;
	}

	return DRAW;
}
