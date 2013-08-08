#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 10000
#define END_INPUT "E-N-D"

void getLongestWord(char str[], char longestWord[], int *stop);

int main(void)
{
	char line[MAX_LEN + 2], longestWord[MAX_LEN + 2], i;
	int stop;

	strcpy(longestWord, "");
	while(1)
	{
		fgets(line, MAX_LEN + 2, stdin);

		getLongestWord(line, longestWord, &stop);

		if(stop)
			break;			
	}

	for(i = 0; longestWord[i] != '\0'; i++)
		longestWord[i] = tolower(longestWord[i]);
	printf("%s\n", longestWord);
	return 0;
}

void getLongestWord(char str[], char longestWord[], int *stop)
{
	int start, end, maxLen = strlen(longestWord);

	*stop = 0;

	for(start = 0; str[start] != '\0';)
	{
		if(isalpha(str[start]) || str[start] == '-')
		{
			for(end = start + 1; str[end] != '\0'; end++)
				if(!(isalpha(str[end]) || str[end] == '-'))
					break;

			if(end - start > maxLen)
			{
				maxLen = end - start;
				strncpy(longestWord, str + start, maxLen);
			}

			if(strncmp(END_INPUT, str + start, end - start) == 0)
			{
				*stop = 1;
				break;
			}

			start = end + 1;
		}
		else
			start++;
	}
}
