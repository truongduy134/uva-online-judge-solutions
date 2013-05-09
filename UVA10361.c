#include <stdio.h>
#include <string.h>

#define MAX_LEN 200000

/* Copy originStr to destStr until encountering the first ocurrence of stopChar */
char * cpyStr(char originStr[], char destStr[], char stopChar)
{
	int indOrigin, indDest;

	for(indOrigin = 0, indDest = 0; originStr[indOrigin] != '\0'; indOrigin++)
		if(originStr[indOrigin] == stopChar)
			break;
		else
		{
			destStr[indDest] = originStr[indOrigin];
			indDest++;
		}

	destStr[indDest] = '\0';

	return originStr + indOrigin;
}

/* line would be in the form of s1<s2>s3<s4>s5 */
void parseFirstLine(char line[], char s1[], char s2[], char s3[], char s4[], char s5[])
{
	int ind;
	char *linePtr = (char *) line;

	linePtr = cpyStr(linePtr, s1, '<');
	linePtr = cpyStr(linePtr + 1, s2, '>');
	linePtr = cpyStr(linePtr + 1, s3, '<');
	linePtr = cpyStr(linePtr + 1, s4, '>');
	cpyStr(linePtr + 1, s5, '\0');
}

int main(void)
{
	char s1[MAX_LEN + 1], s2[MAX_LEN + 1], s3[MAX_LEN + 1],
	     s4[MAX_LEN + 1], s5[MAX_LEN + 1], line[5 * MAX_LEN + 1];
	char *token, delim[] = "...", trash[10];
	int numCase;

	scanf("%d", &numCase);
	gets(trash);
	while(numCase)
	{
		gets(line);
		parseFirstLine(line, s1, s2, s3, s4, s5);
		
		gets(line);
		token = strtok(line, delim);

		printf("%s%s%s%s%s\n", s1, s2, s3, s4, s5);
		if(token != NULL)
			printf("%s%s%s%s%s\n", token, s4, s3, s2, s5);
		else
			printf("%s%s%s%s\n", s4, s3, s2, s5);

		numCase--;
	}

	return 0;
}
