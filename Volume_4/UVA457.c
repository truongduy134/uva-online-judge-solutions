/*******************************************************************************
 * Author: Nguyen Truong Duy
 ********************************************************************************/

/* Methodology
 *	+ This is a straight forward problem. Do the simulation as exactly as in
 *		the problem statement.
 *
 *	+ Flow:
 *		- The inital configuration (at day 1) is that the 20th entry is 1,
 *			the rest are 0.
 *		- For each day from 1 to 50, 
 *			+ print the current configuration, after converting the density
 *				to corresponding letter.
 *			+ calculate the new density for each entry.
 */

#include <stdio.h>

#define MAX_DAY 50
#define DISH_SIZE 40
#define DNA_SIZE 10

int main(void)
{
	int dna[DNA_SIZE], dish[DISH_SIZE], day, numcase, i, prev, sumdense;
	char dishstr[DISH_SIZE + 1];

	scanf("%d", &numcase);
	while(numcase)
	{
		/* Reading inputs */
		for(i = 0; i < DNA_SIZE; ++i)
			scanf("%d", &dna[i]);

		/* Initialzing dish structure */
		int halfsize = DISH_SIZE >> 1;
		for(i = 0; i < DISH_SIZE; ++i)
			dish[i] = 0;
		dish[halfsize - 1] = 1;

		/* Simulating */
		for(day = 1; day <= MAX_DAY; ++day)
		{
			/* Convert to string and print */
			for(i = 0; i < DISH_SIZE; i++)
				switch(dish[i])
				{
					case 0:
						dishstr[i] = ' ';
						break;
					case 1:
						dishstr[i] = '.';
						break;
					case 2:
						dishstr[i] = 'x';
						break;
					case 3:
						dishstr[i] = 'W';
				}
			dishstr[DISH_SIZE] = '\0';
			printf("%s\n", dishstr);

			/* Calculating new density */
			prev = dish[0];
			dish[0] = dna[dish[0] + dish[1]];
			for(i = 1; i < DISH_SIZE - 1; i++)
			{
				sumdense = prev + dish[i] + dish[i + 1];
				prev = dish[i];
				dish[i] = dna[sumdense];
			}
			dish[DISH_SIZE - 1] = dna[prev + dish[DISH_SIZE - 1]];
		}

		if(numcase > 1)
			printf("\n");
		numcase--;
	}
	return 0;
}
