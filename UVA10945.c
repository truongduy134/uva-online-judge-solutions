#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define END_INPUT_STR "DONE"
#define MAX_LEN 800000

int isPalindrome(char str[]);
void removeCaseAndPunctuation(char line[], char formattedLine[]);

int main(void)
{
	char line[MAX_LEN + 1];
	
	while(1)
	{
		gets(line);
		if(strcmp(line, END_INPUT_STR) == 0)
			break;

		if(isPalindrome(line))
			printf("You won't be eaten!\n");
		else
			printf("Uh oh..\n");
	}

	return 0;	
}

int isPalindrome(char line[])
{
	char formattedLine[MAX_LEN + 1];
	int len, left, right;

	removeCaseAndPunctuation(line, formattedLine);

	len = strlen(formattedLine);
	left = 0;
	right = len - 1;
	while(left < right)
	{
		if(formattedLine[left] != formattedLine[right])
			return 0;
		left++;
		right--;
	}

	return 1;
}

void removeCaseAndPunctuation(char line[], char formattedLine[])
{
	int indLine, indFormatted;

	for(indLine = 0, indFormatted = 0; line[indLine] != '\0'; indLine++)
		if(isalpha(line[indLine]))
		{
			formattedLine[indFormatted] = tolower(line[indLine]);
			indFormatted++;
		}

	formattedLine[indFormatted] = '\0';
}
