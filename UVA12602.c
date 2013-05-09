#include <stdio.h>

#define MAX_LEN 10
#define MAX_DIFF 100
#define BASE_ALPHA 26
#define LEN_ALPHA_PART 3

int isNicePlate(char plate[]);

int main(void)
{
	char plate[MAX_LEN + 1];
	int T;

	scanf("%d", &T);
	while(T)
	{
		scanf("%s", plate);

		if(isNicePlate(plate))
			printf("nice\n");
		else
			printf("not nice\n");
		T--;
	}
	return 0;
}

int isNicePlate(char plate[])
{
	int i, alphaPart = 0, numPart = 0, diff;

	for(i = 0; i < LEN_ALPHA_PART; i++)
		alphaPart = alphaPart * BASE_ALPHA + plate[i] - 'A';

	for(i = LEN_ALPHA_PART + 1; plate[i] != '\0'; i++)
		numPart = numPart * 10 + plate[i] - '0';

	diff = alphaPart - numPart;
	if(diff < 0)
		diff = -diff;
	if(diff <= MAX_DIFF)
		return 1;
	return 0;
}
