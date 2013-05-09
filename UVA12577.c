#include <stdio.h>
#include <string.h>

#define MAX_LEN 100
#define STOP '*'
#define HAJJ "Hajj"
#define HAJJ_OUTPUT "Hajj-e-Akbar"
#define UMRAH_OUTPUT "Hajj-e-Asghar"

int main(void)
{
	int caseId;
	char input[MAX_LEN];

	caseId = 1;
	while(1)
	{
		scanf("%s", input);
		if(input[0] == STOP)
			break;

		if(strcmp(input, HAJJ) == 0)
			printf("Case %d: %s\n", caseId, HAJJ_OUTPUT);
		else
			printf("Case %d: %s\n", caseId, UMRAH_OUTPUT);

		caseId++;
	}

	return 0;
}
