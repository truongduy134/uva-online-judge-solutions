#include <stdio.h>
#include <string.h>

#define MAX_LEN 101

int findLongestCommonSubseq(char strOne[], char strTwo[], int indOne, int indTwo, int memoTable[][MAX_LEN]);
int max(int a, int b);

int main(void)
{
	int caseId, lenOne, lenTwo;
	char seqOne[MAX_LEN + 1], seqTwo[MAX_LEN + 1];
	int memoTable[MAX_LEN][MAX_LEN];

	caseId = 1;
	while(1)
	{
		fgets(seqOne, MAX_LEN + 1, stdin);
		if(seqOne[0] == '#')
			break;
		fgets(seqTwo, MAX_LEN + 1, stdin);
		
		lenOne = (int) strlen(seqOne);
		if(seqOne[lenOne - 1] == '\n')
		{
			seqOne[lenOne - 1] = '\0';
			lenOne--;
		}
		lenTwo = (int) strlen(seqTwo);
		if(seqTwo[lenTwo - 1] == '\n')
		{
			seqTwo[lenTwo - 1] = '\0';
			lenTwo--;
		}

		memset(memoTable, -1, MAX_LEN * MAX_LEN * sizeof(int));

		printf("Case #%d: you can visit at most %d cities.\n", caseId,
				findLongestCommonSubseq(seqOne, seqTwo, lenOne - 1, lenTwo - 1, memoTable));

		caseId++;
 
	}
	return 0;
}

int findLongestCommonSubseq(char strOne[], char strTwo[], int indOne, int indTwo, int memoTable[][MAX_LEN])
{
	if(indOne < 0 || indTwo < 0)
		return 0;

	if(memoTable[indOne][indTwo] >= 0)
		return memoTable[indOne][indTwo];

	int maxLength = 0;

	if(strOne[indOne] == strTwo[indTwo])
		maxLength = 1;
	else
		maxLength = 0;

	maxLength += findLongestCommonSubseq(strOne, strTwo, indOne - 1, indTwo - 1, memoTable);

	maxLength = max(maxLength, findLongestCommonSubseq(strOne, strTwo, indOne, indTwo - 1, memoTable));
	maxLength = max(maxLength, findLongestCommonSubseq(strOne, strTwo, indOne - 1, indTwo, memoTable));

	memoTable[indOne][indTwo] = maxLength;

	return maxLength;
}

int max(int a, int b)
{
	if(a < b)
		return b;

	return a;
}
