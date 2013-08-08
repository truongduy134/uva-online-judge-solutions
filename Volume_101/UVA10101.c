#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NUM_UNIT 5
#define MAX_LEN 10000
#define MAX_LEN_NUM 2

const char * unitName[NUM_UNIT] = {"", "shata", "hajar", "lakh", "kuti"};
const int unitNameLength[NUM_UNIT] = {0, 5, 5, 4, 4};
const int unitLength[NUM_UNIT - 1] = {2, 1, 2, 2};

void getBanglaNumStr(char numStr[], char banglaNumStr[]);
int getBanglaNumStrRecursive(char numStr[], int lenNumStr, char banglaNumStr[], int unitType);

int main(void)
{
	char numStr[MAX_LEN + 1], banglaNumStr[MAX_LEN + 1];
	int caseId;

	caseId = 1;
	while(scanf("%s", numStr) > 0)
	{
		getBanglaNumStr(numStr, banglaNumStr);

		printf("%4d. %s\n", caseId, banglaNumStr);

		caseId++;
	}

	return 0;
}

void getBanglaNumStr(char numStr[], char banglaNumStr[])
{
	int lenStr = (int) strlen(numStr);

	/* Special case: the number is 0 */
	if(numStr[0] == '0' && lenStr == 1)
		strcpy(banglaNumStr, numStr);
	else
		getBanglaNumStrRecursive(numStr, lenStr, banglaNumStr, 0);
}

int getBanglaNumStrRecursive(char numStr[], int lenNumStr, char banglaNumStr[], int unitType)
{
	int newLen, numCopy, recurseLen, val;
	char num[MAX_LEN_NUM + 1];

	if(lenNumStr <= 0)
	{
		banglaNumStr[0] = '\0';
		return 0;
	}
	
	if(unitType == NUM_UNIT - 1)
	{
		newLen = getBanglaNumStrRecursive(numStr, lenNumStr, banglaNumStr, 0);
		banglaNumStr[newLen] = ' ';
		newLen++;
		banglaNumStr[newLen] = '\0';

		strcat(banglaNumStr, unitName[unitType]);
		newLen += unitNameLength[unitType];
		return newLen;
	}

	/* Other types */
	recurseLen = lenNumStr - unitLength[unitType];
	if(recurseLen < 0)
		recurseLen = 0;
	newLen = getBanglaNumStrRecursive(numStr, recurseLen, banglaNumStr, unitType + 1);

	/* Get the number of that unit */
	numCopy = lenNumStr - recurseLen;
	strncpy(num, numStr + recurseLen, numCopy);
	num[numCopy] = '\0';
	val = atoi(num);

	/* Do not print 0 */
	if(val == 0)
		return newLen;

	/* Append */
	if(newLen > 0)
	{
		banglaNumStr[newLen] = ' ';
		newLen++;
		banglaNumStr[newLen] = '\0';
	}
	
	sprintf(num, "%d", val);
	strcat(banglaNumStr, num);
	newLen += (int) strlen(num);
	if(unitType != 0)
	{
		banglaNumStr[newLen] = ' ';
		newLen++;		
	}
	banglaNumStr[newLen] = '\0';
	strcat(banglaNumStr, unitName[unitType]);
	newLen += unitNameLength[unitType];

	return newLen;	
}  	
