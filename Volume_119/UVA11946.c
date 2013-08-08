#include <stdio.h>
#include <ctype.h>

#define NUM_DIGIT 10

/* Rule: 0 -> O, 1 -> I, 2 -> Z, 3 -> E, 4 -> A,
 *       5 -> S, 6 -> G, 7 -> T, 8 -> B, 9 -> P */
const char CONVERSION_STR[] = "OIZEASGTBP";

#define MAX_LEN 100

void decodeStr(char str[]);

int main(void)
{
	int T;
	char line[MAX_LEN + 2], trash[MAX_LEN + 2];

	scanf("%d", &T);
	fgets(trash, MAX_LEN + 2, stdin);
	

	while(T)
	{
		while(1)
		{
			if(fgets(line, MAX_LEN + 2, stdin) == NULL)
				break;
			if(line[0] == '\n')
				break;

			decodeStr(line);
			printf("%s", line);
		}

		if(T != 1)
			printf("\n");
		T--;
	}
	return 0;
}

void decodeStr(char str[])
{
	int i;

	for(i = 0; str[i] != '\0'; i++)
		if(isdigit(str[i]))
		{
			str[i] = CONVERSION_STR[(int) (str[i] - '0')];
		}
}
