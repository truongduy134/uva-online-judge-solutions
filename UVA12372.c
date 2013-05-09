#include <stdio.h>

#define MAX_SIZE 20

int main(void)
{
	int T, caseId, length, height, width;

	scanf("%d", &T);
	caseId = 1;

	while(caseId <= T)
	{
		scanf("%d %d %d", &length, &width, &height);

		printf("Case %d: ", caseId);
		if(length <= MAX_SIZE && width <= MAX_SIZE && height <= MAX_SIZE)
			printf("good\n");
		else
			printf("bad\n");
		caseId++;
	}
	return 0;
}
