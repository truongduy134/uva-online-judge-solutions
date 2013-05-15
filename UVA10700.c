/************************************************************************
 * Author: Nguyen Truong Duy
 ************************************************************************/

/* Methodology:
 *	+ Since the operators are only + and *, we can use the greedy approach
 *		to get the maxmium and minimum values.
 *	+ To get the maximum values, group and perform all the additions first.
 *	  To get the minimu values, group and perform all the multiplication first.
 */

#include <stdio.h>
#include <string.h>

const int MAX_LEN_LINE = 10000;
const int MAX_NUM_NUM = 12;
const char ADD = '+';
const char MUL = '*';

int performGreedyCalculation(int numArr[], char operatorArr[], int numNum,
			     char firstOp, char secondOp);
int parseExpression(char line[], int numArr[], char operatorArr[]);

int main(void)
{
	int T, numArr[MAX_NUM_NUM], numNum;
	char line[MAX_LEN_LINE + 1], operatorArr[MAX_NUM_NUM - 1];

	scanf("%d", &T);
	gets(line);

	while(T)
	{
		gets(line);
		numNum = parseExpression(line, numArr, operatorArr);

		printf("The maximum and minimum are %d and %d.\n",
			performGreedyCalculation(numArr, operatorArr, numNum, ADD, MUL),
			performGreedyCalculation(numArr, operatorArr, numNum, MUL, ADD));
		T--;
	}		
	return 0;
}

int parseExpression(char line[], int numArr[], char operatorArr[])
{
	int i, num, numOp;

	for(i = 0, num = 0, numOp = 0; line[i] != '\0'; i++)
	{
		if(line[i] != ADD && line[i] != MUL)
			num =  num * 10 + (line[i] - '0');
		else
		{
			operatorArr[numOp] = line[i];
			numArr[numOp] = num;
			numOp++;
			num = 0;
		}
	}

	numArr[numOp] = num;
	operatorArr[numOp] = '\0';

	return numOp + 1;
}

/* Group and perform all operators of type firstOp first. */
int performGreedyCalculation(int numArr[], char operatorArr[], int numNum,
			     char firstOp, char secondOp)
{
	int i, val, numInd, opInd, resultArr[MAX_NUM_NUM], sizeArr;

	sizeArr = 0;
	resultArr[sizeArr] = numArr[0];
	sizeArr++;
	for(i = 0; operatorArr[i] != '\0'; i++)
	{
		if(operatorArr[i] == firstOp)
		{
			if(firstOp == ADD)
				resultArr[sizeArr - 1] += numArr[i + 1];
			else
				resultArr[sizeArr - 1] *= numArr[i + 1];
		}
		else
		{
			resultArr[sizeArr] = numArr[i + 1];
			sizeArr++;
		}
	}

	if(secondOp == ADD)
		val = 0;
	else
		val = 1;
	for(i = 0; i < sizeArr; i++)
		if(secondOp == ADD)
			val += resultArr[i];
		else
			val *= resultArr[i];

	return val;
}
