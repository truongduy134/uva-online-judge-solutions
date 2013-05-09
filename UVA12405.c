#include <stdio.h>

#define MAX_LEN 100
#define INFERTILE '#'
#define COVER 'C'

int main(void)
{
	char field[MAX_LEN + 1];
	int T, len, caseId;

	scanf("%d", &T);
	caseId = 1;
	while(caseId <= T)
	{
		scanf("%d", &len);
		scanf("%s", field);

		printf("Case %d: %d\n", caseId, getMinNumScarecrow(field, len));

		caseId++;
	}

	return 0;
}

int getMinNumScarecrow(char field[], int len)
{
	int ind = 0, numScarecrow = 0, placePos, i;

	while(ind < len)
	{
		if(field[ind] == COVER || field[ind] == INFERTILE)
			ind++;
		else
		{
			/* Must find a place to cover this region. The best one 
			 * is at index ind + 1 */
			numScarecrow++;
		
			placePos = ind + 1;
			if(placePos == len)
				placePos = ind;
			for(i = placePos - 1; i <= placePos + 1; i++)
				if(i < len)
					field[i] = COVER;
		}
	}

	return numScarecrow;
}
