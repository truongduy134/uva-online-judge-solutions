/*******************************************************************************
 * Author: Nguyen Truong Duy
 ********************************************************************************/

/* Methodology:
 *	+ The answer is 'S' if and only if for all banks,
 *		its monetary reserves + its credits - its debits >= 0.
 */

#include <stdio.h>

const int MAX_NUM_BANK = 20;
const int NUM_COL = 3;
const int MAX_NUM_RELATION = 100000;

int allBankCanPayDebt(int reserve[], int numBank, int relation[][NUM_COL], int numRelation);

int main(void)
{
	int i, numBank, numRelation, reserve[MAX_NUM_BANK], relation[MAX_NUM_RELATION][NUM_COL];

	while(1)
	{
		scanf("%d %d", &numBank, &numRelation);
		if(numBank == 0 && numRelation == 0)
			break;

		for(i = 0; i < numBank; i++)
			scanf("%d", &reserve[i]);
		for(i = 0; i < numRelation; i++)
		{
			scanf("%d %d %d", &relation[i][0], &relation[i][1], &relation[i][2]);
			relation[i][0]--;
			relation[i][1]--;
		}

		if(allBankCanPayDebt(reserve, numBank, relation, numRelation))
			printf("S\n");
		else
			printf("N\n");
	}
	return 0;
}

int allBankCanPayDebt(int reserve[], int numBank, int relation[][NUM_COL], int numRelation)
{
	int surplus[MAX_NUM_BANK], i, amount, debit, credit;

	for(i = 0; i < numBank; i++)
		surplus[i] = reserve[i];

	for(i = 0; i < numRelation; i++)
	{
		debit = relation[i][0];
		credit = relation[i][1];
		amount = relation[i][2];

		surplus[debit] -= amount;
		surplus[credit] += amount;
	}

	for(i = 0; i < numBank; i++)
		if(surplus[i] < 0)
			return 0;
	return 1;
}
