#include <stdio.h>
#include <ctype.h>

#define MAX_LEN 13

int convertHexToDec(char hex[]);
void convertDecToBin(int decVal, char bin[]);

int main(void)
{
	int T, decimalOne, decimalTwo;
	char hexOne[MAX_LEN + 1], hexTwo[MAX_LEN + 1],
	     binaryOne[MAX_LEN + 1], binaryTwo[MAX_LEN + 1], 
	     operator[MAX_LEN + 1];

	scanf("%d", &T);
	while(T)
	{
		scanf("%s %s %s", hexOne, operator, hexTwo);
		decimalOne = convertHexToDec(hexOne);
		decimalTwo = convertHexToDec(hexTwo);
		convertDecToBin(decimalOne, binaryOne);
		convertDecToBin(decimalTwo, binaryTwo);

		if(operator[0] == '+')
			printf("%s + %s = %d\n", binaryOne, binaryTwo, decimalOne + decimalTwo);
		else
			printf("%s - %s = %d\n", binaryOne, binaryTwo, decimalOne - decimalTwo);

		T--;
	}

	return 0;
}

int convertHexToDec(char hex[])
{
	int ind, decVal = 0, base = 16;

	for(ind = 0; hex[ind] != '\0'; ind++)
		if(isdigit(hex[ind]))
			decVal = decVal * base + (hex[ind] - '0');
		else
			decVal = decVal * base + (hex[ind] - 'A' + 10);

	return decVal;
}

void convertDecToBin(int decVal, char bin[])
{
	int ind;

	bin[MAX_LEN] = '\0';
	for(ind = 0; ind < MAX_LEN; ind++)
		bin[ind] = '0';

	ind = MAX_LEN - 1;
	while(decVal)
	{
		bin[ind] = (char) ('0' + (decVal & 1));
		decVal >>= 1;
		ind--;
	}
}
