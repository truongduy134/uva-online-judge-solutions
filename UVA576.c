#include <stdio.h>
#include <string.h>

#define NUM_LINE 3
#define END_OF_INPUT "e/o/i"
#define MAX_LEN_LINE 300

const int numSyllablePerLine[NUM_LINE] = {5, 7, 5};

int checkHaiku(char haiku[]);
int countNumSyllable(char haikuLine[]);
int isVowel(char c);

int main(void)
{
	char haiku[MAX_LEN_LINE + 1], lineWrong;

	while(1)
	{
		gets(haiku);
		if(strcmp(haiku, END_OF_INPUT) == 0)
			break;

		lineWrong = checkHaiku(haiku);

		if(lineWrong)
			printf("%d\n", lineWrong);
		else
			printf("Y\n");
	}

	return 0;
}

int checkHaiku(char haiku[])
{
	char *token, delim[] = "/";
	int line = 0, numSyllable;

	token = strtok(haiku, delim);

	if(token == NULL)
		return 1;

	do
	{
		numSyllable = countNumSyllable(token);
		if(numSyllable != numSyllablePerLine[line])
			return line + 1;

		line++;
		token = strtok(NULL, delim);	
	} while(token != NULL);

	return 0;
}

int countNumSyllable(char haikuLine[])
{
	int numSyllable = 0, ind = 0;

	while(haikuLine[ind] != '\0')
	{
		if(isVowel(haikuLine[ind]))
		{
			numSyllable++;
			ind++;
			while(haikuLine[ind] != '\0' && isVowel(haikuLine[ind]))
			{
				ind++;
			}
		}
		else
			ind++;
	}

	return numSyllable;
}

int isVowel(char c)
{
	if(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'y')
		return 1;
	return 0;
}
