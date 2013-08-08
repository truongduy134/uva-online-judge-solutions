#include <stdio.h>
#include <ctype.h>

#define MAX_LEN 1000000
#define MAX_CHAR 256

void getLettersWithHighestFreq(char line[], char output[], int *maxFreq);

int main(void)
{
	char line[MAX_LEN + 2], output[MAX_CHAR + 1];
	int maxFreq;

	while(fgets(line, MAX_LEN + 2, stdin) != NULL)
	{
		getLettersWithHighestFreq(line, output, &maxFreq);

		printf("%s %d\n", output, maxFreq);
	}
	return 0;
}

void getLettersWithHighestFreq(char line[], char output[], int *maxFreq)
{
	int freqSieve[MAX_CHAR + 1] = {0};
	int ind, indOut;
	
	for(ind = 0; line[ind] != '\0'; ind++)
		if(isalpha(line[ind]))
		{
			freqSieve[(int) line[ind]]++;
		}

	*maxFreq = freqSieve[(int) 'A'];
	for(ind = 'B'; ind <= 'z';)
	{
		if(freqSieve[ind] > *maxFreq)
			*maxFreq = freqSieve[ind];

		if(ind == 'Z')
			ind = 'a';
		else
			ind++;
	}

	indOut = 0;
	for(ind = 'A'; ind <= 'z';)
	{
		if(freqSieve[ind] == *maxFreq)
		{
			output[indOut] = (char) ind;
			indOut++;		
		}

		if(ind == 'Z')
			ind = 'a';
		else
			ind++;
	}
	output[indOut] = '\0';
}
