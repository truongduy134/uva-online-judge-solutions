/*******************************************************************************
 * Author: Nguyen Truong Duy
 ********************************************************************************/

/* Methodology:
 *	+ We can solve this using Dynamic Programming
 *
 *	+ Let f(m, n, t) = the maximum number of burgers Hormer can eat without wasting
 *		any time if it takes m minutes to eat a burger of type I and n minutes
 *		to eat a burger of type II
 *	+ Recurrence relation:
 *		f(m, n, t) = 0 if f(m, n, t - m) = f(m, n, t - n ) = 0
 *		f(m, n, t) = 1 + max(f(m, n, t - m), f(m, n, t - n))
 *	+ Base case:
 *		f(m, n, m) = f(m, n, n) = 1
 *		f(m, n, t) = 0 if t <= 0
 *	
 *	+ In this problem, if f(m, n, t) = 0, we must find the nearest x < t such that
 *	  f(m, n, x) > 0. And the drinking time will be t - x.
 *	  This can be done by a linear scan from t backwards.
 *
 *	+ Time complexity: O(T) where T is the total time.
 */

#include <stdio.h>

#define MAX_TIME 10000

void findMaxNumBurger(int totalTime, int timeTypeOne, int timeTypeTwo, int * maxNumBurger, int * drinkTime);

int main(void)
{
	int totalTime, timeTypeOne, timeTypeTwo, drinkTime, maxNumBurger;

	while(scanf("%d %d %d", &timeTypeOne, &timeTypeTwo, &totalTime) > 0)
	{
		findMaxNumBurger(totalTime, timeTypeOne, timeTypeTwo, &maxNumBurger, &drinkTime);
		
		printf("%d", maxNumBurger);
		if(drinkTime)
			printf(" %d", drinkTime);
		printf("\n");
	}
	return 0;
}

void findMaxNumBurger(int totalTime, int timeTypeOne, int timeTypeTwo, int * maxNumBurger, int * drinkTime)
{
	int numBurger[MAX_TIME + 1] = {0};

	numBurger[timeTypeOne] = 1;
	numBurger[timeTypeTwo] = 1;

	int time;
	int maxPrevNumBurger;
	for(time = 1; time <= totalTime; time++)
	{
		maxPrevNumBurger = 0;
		if(time - timeTypeOne >= 0)
			maxPrevNumBurger = numBurger[time - timeTypeOne];
		if(time - timeTypeTwo >= 0 && maxPrevNumBurger < numBurger[time - timeTypeTwo])
			maxPrevNumBurger = numBurger[time - timeTypeTwo];

		if(maxPrevNumBurger)
			numBurger[time] = 1 + maxPrevNumBurger; 
	}

	for(time = totalTime; time >= 0; time--)
		if(numBurger[time])
		{
			*maxNumBurger = numBurger[time];
			*drinkTime = totalTime - time;
			return;
		}
	
	/* In case he cannot eat any burger */
	*maxNumBurger = 0;
	*drinkTime = totalTime;
}
