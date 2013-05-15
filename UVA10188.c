/******************************************************************
 * Author: Nguyen Truong Duy
 ******************************************************************/
#include <stdio.h>
#include <string.h>
#include <ctype.h>

/* AC = accepted, PE = presentation error, WA = wrong answer */
enum JudgeResult {
	AC, PE, WA
};

#define MAX_LEN_LINE 130
#define MAX_NUM_LINE 100

void getNumeralStr(char str[], char numeralStr[]);
enum JudgeResult judgeSubmission(char judgeOutput[], int numJudgeLine, 
                                 char teamOutput[], int numTeamLine);

int main(void)
{
	int numJudgeLine, numTeamLine, caseId, i;
	char judgeOutput[MAX_NUM_LINE * MAX_LEN_LINE], teamOutput[MAX_LEN_LINE * MAX_NUM_LINE],
	     line[MAX_LEN_LINE];

	caseId = 1;
	while(1)
	{
		scanf("%d", &numJudgeLine);
		if(numJudgeLine == 0)
			break;
		gets(line);
		
		judgeOutput[0] = '\0';
		teamOutput[0] = '\0';

		for(i = 0; i < numJudgeLine; i++)
		{
			gets(line);
			if(i > 0)
				strcat(judgeOutput, "\n");
			strcat(judgeOutput, line); 
		}

		scanf("%d", &numTeamLine);
		gets(line);
		for(i = 0; i < numTeamLine; i++)
		{
			gets(line);
			if(i > 0)
				strcat(teamOutput, "\n");
			strcat(teamOutput, line);
		}

		printf("Run #%d: ", caseId);
		switch(judgeSubmission(judgeOutput, numJudgeLine, teamOutput, numTeamLine))
		{
			case AC:
				printf("Accepted\n");
				break;
			case PE:
				printf("Presentation Error\n");
				break;
			default:
				printf("Wrong Answer\n");
		}
		caseId++;
	}
	return 0;
}

enum JudgeResult judgeSubmission(char judgeOutput[], int numJudgeLine, 
                                 char teamOutput[], int numTeamLine)
{
	char numeralJudgeStr[MAX_NUM_LINE * MAX_LEN_LINE], numeralTeamStr[MAX_NUM_LINE * MAX_LEN_LINE];

	if(numJudgeLine == numTeamLine && strcmp(judgeOutput, teamOutput) == 0)
		return AC;

	getNumeralStr(judgeOutput, numeralJudgeStr);
	getNumeralStr(teamOutput, numeralTeamStr);

	if(strcmp(numeralJudgeStr, numeralTeamStr) == 0)
		return PE;
	return WA;
}

void getNumeralStr(char str[], char numeralStr[])
{
	int i, len;

	for(i = 0, len = 0; str[i] != '\0'; i++)
		if(isdigit(str[i]))
		{
			numeralStr[len] = str[i];
			len++;
		}

	numeralStr[len] = '\0';
}
