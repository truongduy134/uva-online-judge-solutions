#include <stdio.h>
#include <string.h>

#define ONE "one"
#define TWO "two"
#define MAX_LEN 10
#define LEN_THREE 5

int calculateDistance(char wordOne[], char wordTwo[]);

int main(void)
{
	int T, result;
	char trash[MAX_LEN + 1], word[MAX_LEN + 1];

	scanf("%d", &T);
	fgets(trash, MAX_LEN + 1, stdin);

	while(T)
	{
		scanf("%s", word);
		if(strlen(word) == LEN_THREE)
			result = 3;
		else
		{
			if(calculateDistance(word, ONE) <= 1)
				result = 1;
			else
				result = 2;
		}

		printf("%d\n", result);	
		T--;
	}

	return 0;
}

int calculateDistance(char wordOne[], char wordTwo[])
{
	int lenOne = strlen(wordOne), lenTwo = strlen(wordTwo), len;
	int i, diff = 0;

	len = lenOne;
	if(lenOne > lenTwo)
		len = lenTwo;
	for(i = 0; i < len; i++)
		if(wordOne[i] != wordTwo[i])
			diff++;

	return diff;
}
