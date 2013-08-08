#include <stdio.h>

#define MAX_LEN 10000

int findProductDigitNum(int N, char Q[]);
void reverse(char str[], int len);

int main(void)
{
	int N, T;
	char Q[MAX_LEN + 1];

	scanf("%d", &T);
	while(T)
	{
		scanf("%d", &N);
		
		if(findProductDigitNum(N, Q))
			printf("%s\n", Q);
		else
			printf("-1\n");
		T--;
	}

	return 0;
}

/* Find a number Q such that the product of digits in Q equals N
 *
 * The function returns 1 if such Q exists. Otherwise, it returns 0
 */
int findProductDigitNum(int N, char Q[])
{
	/* Special case */
	if(N < 10)
	{
		Q[0] = (char) (N + '0');
		Q[1] = '\0';
		return 1;
	}

	int len = 0, digit;

	digit = 9;
	while(digit > 1 && N > 1)
	{
		while(N % digit == 0)
		{
			Q[len] = (char) (digit + '0');
			len++;
			N /= digit;
		}

		digit--;
	}

	if(N > 1)
		return 0;

	Q[len] = '\0';
	reverse(Q, len);

	return 1;
}
void reverse(char str[], int len)
{
	int left = 0, right = len - 1;
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
