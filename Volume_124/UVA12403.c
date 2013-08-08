#include <stdio.h>
#include <string.h>

#define DONATE "donate"
#define REPORT "report"
#define MAX_LEN 50

int main(void)
{
	char operation[MAX_LEN + 1];
	int numOp, amount, totalAmount;

	scanf("%d", &numOp);

	totalAmount = 0;
	while(numOp)
	{
		scanf("%s", operation);
		if(strcmp(operation, REPORT) == 0)
		{
			printf("%d\n", totalAmount);
		}
		else
		{
			scanf("%d", &amount);
			totalAmount += amount;
		}
		numOp--;
	}
	return 0;
}
