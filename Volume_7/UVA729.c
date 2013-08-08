#include <stdio.h>

#define BASE_NUM 0
#define MAX_NUM_DIGIT 16

const int MAX_SIZE = 1 << MAX_NUM_DIGIT;

int getNumHamming(int N, int hammingDist, int base, int result[]);
int getHammingDistance(int A, int B);
void getBinaryRepresentation(int num, int numDigit, char str[]);
void reverseStr(char str[], int length);

int main(void)
{
	int T, numDigit, hammingDist, result[MAX_SIZE], numResult, i;
	char binary[MAX_NUM_DIGIT + 1];

	scanf("%d", &T);
	while(T)
	{
		scanf("%d %d", &numDigit, &hammingDist);

		numResult = getNumHamming(numDigit, hammingDist, BASE_NUM, result);

		for(i = 0; i < numResult; i++)
		{
			getBinaryRepresentation(result[i], numDigit, binary);
			printf("%s\n", binary);
		}

		if(T != 1)
			printf("\n");
		T--;
	}
	return 0;
}

/* Get all the number G whose binary representation contains N digits such that
 *	the Hamming distance between G and base is equal to hammingDist
 */
int getNumHamming(int N, int hammingDist, int base, int result[])
{
	int numResult = 0, upperBound = (1 << N), num;

	for(num = BASE_NUM; num < upperBound; num++)
		if(getHammingDistance(num, base) == hammingDist)
		{
			result[numResult] = num;
			numResult++;
		}

	return numResult;	
}
int getHammingDistance(int A, int B)
{
	int xOr = A^B, countOne = 0;

	/* The hamming distance equals to the number of bit 1 in xOr */
	while(xOr)
	{
		countOne++;

		xOr -= (xOr & (-xOr));
	}

	return countOne;
}
void getBinaryRepresentation(int num, int numDigit, char str[])
{
	int lenStr = 0, digit;

	while(num)
	{
		digit = num & 1;
		str[lenStr] = (char) (digit + '0');
		lenStr++;
		num >>= 1;	
	}

	while(lenStr < numDigit)
	{
		str[lenStr] = '0';
		lenStr++;
	}

	str[lenStr] = '\0';

	reverseStr(str, lenStr);	
}

void reverseStr(char str[], int length)
{
	int left = 0, right = length - 1;
	char temp;

	while(left < right)
	{
		temp = str[left];
		str[left] = str[right];
		str[right] = temp;

		left++;
		right--;		
	}
}
