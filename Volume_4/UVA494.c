/*******************************************************************************
 * Author: Nguyen Truong Duy
 ********************************************************************************/

#include <stdio.h>
#include <ctype.h>

const int MAX_LEN_LINE = 100000;

int countNumWord(char str[]);

int main(void)
{
	char line[MAX_LEN_LINE + 1];

	while(gets(line) != NULL)
	{
		printf("%d\n", countNumWord(line));
	}

	return 0;
}

int countNumWord(char str[])
{
	int numWord = 0, ind, endWordInd;

	for(ind = 0; str[ind] != '\0';)
	{
		if(isalpha(str[ind]))
		{
			/* This is the start of a word */
			numWord++;
			
			/* Find the end of this current word */
			endWordInd = ind;
			while(isalpha(str[endWordInd + 1]))
				endWordInd++;
			ind = endWordInd + 1;
		}
		else
			ind++;
	}

	return numWord;
}
