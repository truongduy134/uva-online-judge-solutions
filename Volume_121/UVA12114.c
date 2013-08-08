#include <stdio.h>

/*
 * If S >= B, then min(S / B, 1) = min ((S - 1) / (B - 1), 1)
 * If S < B, then S / B > (S - 1) / (B - 1)
 */
int main(void)
{
	int S, B, caseId;

	caseId = 1;
	while(1)
	{
		scanf("%d %d", &B, &S);
		if(S == 0 && B == 0)
			break;

		printf("Case %d: ", caseId);
		if(B == 1)
			printf(":-\\\n");
		else
		{
			if(S < B)
				printf(":-(\n");
			else
				printf(":-|\n");		
		}

		caseId++;
	}
	return 0;	
}
