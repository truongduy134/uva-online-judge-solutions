#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define NUM_DIGIT 10
#define MAX_LEN_LINE 80
#define CHECK_SUM 11

int parseISBN(char line[], int ISBN[]);
int isCorrectISBN(int ISBN[]);

/* Note that:
 *	+ In the input string, there might be spaces in the middle. But you should not remove them.
 *	+ There may be an empty line.
 */
int main(void)
{
	char line[MAX_LEN_LINE + 1];
	int ISBN[NUM_DIGIT];

	while(gets(line) != NULL)
	{
		if(parseISBN(line, ISBN) && isCorrectISBN(ISBN))
			printf("%s is correct.\n", line);
		else
			printf("%s is incorrect.\n", line);
	}

	return 0;
}

int parseISBN(char line[], int ISBN[])
{
	int i, numDigitRead, newLen;
	int start = 0, end = (int) strlen(line) - 1;

	while(line[start] == ' ' && line[start] != '\0')
		start++;
	while(line[end] == ' ' && end >= 0)
		end--;

	if(start > end)
		line[0] = '\0';
	else
	{
		newLen = end - start + 1;
		for(i = 0; i < newLen; i++)
			line[i] = line[start + i];
		line[newLen] = '\0';	
	}

	for(i = 0, numDigitRead = 0; line[i] != '\0'; i++)
	{
		if(isdigit(line[i]) || line[i] == 'X')
		{
			if(numDigitRead >= NUM_DIGIT)
				return 0;

			if(line[i] == 'X' && numDigitRead != NUM_DIGIT - 1)
				return 0;

			if(line[i] == 'X')
				ISBN[numDigitRead] = 10;
			else
				ISBN[numDigitRead] = (int) line[i] - '0';
			numDigitRead++;
		}
		else
		{
			if(line[i] != '-')
				return 0;
		}
	}

	if(numDigitRead != NUM_DIGIT)
		return 0;
	return 1;
}

int isCorrectISBN(int ISBN[])
{
	int partialSum[NUM_DIGIT], i, total;

	/* First pass */
	partialSum[0] = ISBN[0];
	for(i = 1; i < NUM_DIGIT; i++)
		partialSum[i] = partialSum[i - 1] + ISBN[i];

	/* Second pass */
	total = 0;
	for(i = 0; i < NUM_DIGIT; i++)
		total += partialSum[i];

	if(total % CHECK_SUM == 0)
		return 1;
	return 0;
}
