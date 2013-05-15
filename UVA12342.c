/***********************************************************
 * Author: Nguyen Truong Duy
 ***********************************************************/
#include <stdio.h>
#include <math.h>

#define NUM_LEVEL 5
const int TAX_MATRIX[NUM_LEVEL][2] = {{180000, 0},
				     {300000, 10},
				     {400000, 15},
				     {300000, 20},
				     {1000000000, 25}};
#define MIN_PAY_TAX 2000
#define EPS 0.000000000001

int main(void)
{
	int caseId, income, T;

	scanf("%d", &T);
	caseId = 1;

	while(caseId <= T)
	{
		scanf("%d", &income);

		printf("Case %d: %d\n", caseId, calculateTax(income));
		caseId++;
	}
	return 0;
}

int calculateTax(int income)
{
	double tax = 0;
	int level, amount, taxInt;

	for(level = 0; level < NUM_LEVEL && income > 0; level++)
	{
		amount = TAX_MATRIX[level][0];
		if(amount > income)
			amount = income;

		tax += (double) amount * TAX_MATRIX[level][1] / 100.0;

		income -= amount;
	}

	if(fabs(tax) < EPS)
		taxInt = 0;
	else
		taxInt = (int) (ceil(tax));

	if(taxInt > 0 && taxInt < MIN_PAY_TAX)
		taxInt = MIN_PAY_TAX;

	return taxInt;
}
