#include <stdio.h>
#include <ctype.h>

#define MAX_NUM_CHAR 30

int getLoveValue(char name[]);
int getDigitSum(int n);

int main(void)
{
	char nameOne[MAX_NUM_CHAR + 1], nameTwo[MAX_NUM_CHAR + 1];
	int valOne, valTwo;
	double ratio;

	while(gets(nameOne) != NULL)
	{
		gets(nameTwo);

		valOne = getLoveValue(nameOne);
		valTwo = getLoveValue(nameTwo);

		if(valOne < valTwo)
			ratio = valOne / (double) valTwo;
		else
			ratio = valTwo / (double) valOne;
		ratio *= 100;

		printf("%.2f %%\n", ratio);				
	}
	return 0;
}

int getLoveValue(char name[])
{
	int loveVal = 0, ind;

	for(ind = 0; name[ind] != '\0'; ind++)
		if(isalpha(name[ind]))
		{
			loveVal += (tolower(name[ind]) - 'a' + 1);
		}

	while(loveVal >= 10)
	{
		loveVal = getDigitSum(loveVal);
	}

	return loveVal;
}

int getDigitSum(int n)
{
	int sumDigit = 0;

	while(n)
	{
		sumDigit += n % 10;
		n /= 10;
	}

	return sumDigit;
}
