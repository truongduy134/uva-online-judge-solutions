/***********************************************************************************
 * Author: Nguyen Truong Duy
 ***********************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN_LINE 1000000
#define MAX_SIZE 1000000

int parseLineToGetNumArr(char line[], int numArr[]);
int evaluateDerivative(int coeff[], int polyDegree, int input);

/* Note:
 *	+ In the judge test cases, there is a polynomial of degree 0.
 *	  Its derivative is 0.
 *	+ The degree of the polynomial can be as large as 1000000.
 */
int main(void)
{
	int coeff[MAX_SIZE], input, polyDegree;
	char line[MAX_LEN_LINE + 1];

	while(scanf("%d", &input) > 0)
	{
		gets(line);	/* Get rid of trailing \n */

		gets(line);
		polyDegree = parseLineToGetNumArr(line, coeff);
		polyDegree--;

		printf("%d\n", evaluateDerivative(coeff, polyDegree, input));
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

int evaluateDerivative(int coeff[], int polyDegree, int input)
{
	if(polyDegree == 0)
		return 0;

	int value = 0, i, degree;

	for(i = 0, degree = polyDegree; i < polyDegree - 1; i++, degree--)
		value = (value + coeff[i] * degree) * input;
	value += coeff[polyDegree - 1];

	return value;
}


