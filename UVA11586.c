#include <stdio.h>
#include <string.h>

#define MAX_LEN 10000
#define MALE 'M'
#define FEMALE 'F'

int canFormLoop(char line[]);

int main(void)
{
	int T;
	char line[MAX_LEN + 1];

	scanf("%d", &T);
	gets(line);
	while(T)
	{
		gets(line);

		if(canFormLoop(line))
			printf("LOOP\n");
		else
			printf("NO LOOP\n");
		T--;
	}
	return 0;
}

/* Tricky case: If there is only 1 piece, then a cycle cannot be formed */
int canFormLoop(char line[])
{
	int numMale = 0, numFemale = 0, i, numPiece = 0;
	char *token, delim[] = " ";

	token = strtok(line, delim);
	while(token != NULL)
	{
		numPiece++;
		for(i = 0; token[i] != '\0'; i++)
			if(token[i] == MALE)
				numMale++;
			else
				numFemale++;

		token = strtok(NULL, delim);
	}

	return (numMale == numFemale) && (numPiece > 1);
}
