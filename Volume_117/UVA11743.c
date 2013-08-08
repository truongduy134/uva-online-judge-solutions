/*******************************************************************************
 * Author: Nguyen Truong Duy
 ********************************************************************************/

#include <stdio.h>

#define MAX_LEN 4
#define NUM_GROUP 4

int isValidLuhnAlgo(char creditStr[NUM_GROUP][MAX_LEN + 1]);

int main(void)
{
	int T, i;
	char creditStr[NUM_GROUP][MAX_LEN + 1];

	scanf("%d", &T);
	while(T)
	{
		for(i = 0; i < NUM_GROUP; i++)
			scanf("%s", creditStr[i]);

		if(isValidLuhnAlgo(creditStr))
			printf("Valid\n");
		else
			printf("Invalid\n");

		T--;
	} 

	return 0;
}

int isValidLuhnAlgo(char creditStr[NUM_GROUP][MAX_LEN + 1])
{
	int doubleSum = 0, noDoubleSum = 0, i, j, temp;

	for(i = 0; i < NUM_GROUP; i++)
	{
		noDoubleSum += (creditStr[i][1] - '0') + (creditStr[i][3] - '0');
		for(j = 0; j <= 2; j += 2)
		{
			temp = (creditStr[i][j] - '0') << 1;
			if(temp >= 10)
				doubleSum += (temp - 10) + 1;
			else
				doubleSum += temp;
		}
	}

	if((doubleSum + noDoubleSum) % 10 == 0)
		return 1;
	return 0;
}
