/*********************************************************
 * Author: Nguyen Truong Duy
 **********************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_DEGREE 1000
#define MAX_LEN_LINE 10000
#define MAX_SIZE 10000

int evaluatePoly(int coeff[], int polyDegree, int input);
int parseLineToGetNumArr(char line[], int numArr[]);

int main(void)
{
	int coeff[MAX_DEGREE + 1], input[MAX_SIZE], value[MAX_SIZE],
	    polyDegree, numInput, i;
	char line[MAX_LEN_LINE];

	while(gets(line) != NULL)
	{
		polyDegree = parseLineToGetNumArr(line, coeff);
		polyDegree--;

		gets(line);
		numInput = parseLineToGetNumArr(line, input);

		for(i = 0; i < numInput; i++)
			value[i] = evaluatePoly(coeff, polyDegree, input[i]);

		for(i = 0; i < numInput; i++)
		{
			if(i > 0)
				printf(" ");
			printf("%d", value[i]);
		}
		printf("\n");
	}	
	return 0;
}

int parseLineToGetNumArr(char line[], int numArr[])
{
	int mSize = 0;
	char *token, delim[] = " ";

	token = strtok(line, delim);
	while(token != NULL)
	{
		numArr[mSize] = atoi(token);
		mSize++;
		token = strtok(NULL, delim);
	}

	return mSize;
}

int evaluatePoly(int coeff[], int polyDegree, int input)
{
	int value = 0, i;

	for(i = 0; i < polyDegree; i++)
		value = (value + coeff[i]) * input;
	value += coeff[polyDegree];

	return value;
}
