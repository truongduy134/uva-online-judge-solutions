#include <stdio.h>

#define MAX_NUM_DIGIT 1000000

void add(char numOne[], char numTwo[], char numThree[], int len);

int main(void)
{
	int lenNum, T, digitOne, digitTwo, pos;
	char numOne[MAX_NUM_DIGIT + 1 + 1],
	     numTwo[MAX_NUM_DIGIT + 1 + 1],
	     numThree[MAX_NUM_DIGIT + 1 + 1], *startPrint;

	scanf("%d", &T);
	while(T)
	{
		scanf("%d", &lenNum);
		numOne[lenNum + 1] = '\0';
		numTwo[lenNum + 1] = '\0';
		numThree[lenNum + 1] = '\0';
		numOne[0] = '0';
		numTwo[0] = '0';
		
		for(pos = 1; pos <= lenNum; pos++)
		{
			scanf("%d %d", &digitOne, &digitTwo);
			numOne[pos] = (char) (digitOne + '0');
			numTwo[pos] = (char) (digitTwo + '0');
		}

		add(numOne, numTwo, numThree, lenNum + 1);
		
		startPrint = &numThree[0];
		while(startPrint[0] == '0')
			startPrint++;
		printf("%s\n", startPrint);

		if(T != 1)
			printf("\n");
		T--;
	}

	return 0;
}

void add(char numOne[], char numTwo[], char numThree[], int len)
{
	int pos;
	char carry, val;

	carry = 0;
	for(pos = len - 1; pos >= 0; pos--)
	{
		val = numOne[pos] - '0' + numTwo[pos] - '0' + carry;
		
		if(val >= 10)
		{
			val -= 10;
			carry = 1;
		}
		else
			carry = 0;

		numThree[pos] = val + '0';
	}	
}
