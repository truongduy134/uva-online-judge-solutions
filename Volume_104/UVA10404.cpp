/*******************************************************************************
 * Author: Nguyen Truong Duy
 ********************************************************************************/

/* Methodology:
 *	+ This problem can be solved using Dynamic Programming.
 *	+ Suppose each player can only remove stones with amount
 *		specified in the set X of size k.
 *
 *	+ Let f(n) = true if the first player who plays an instance
 *		of the bachet game with n stones and k kinds of removing rules
 *		wins
 *	  And f(n) = false otherwise
 *
 *	+ Then we have:
 *		f(n) = OR (NOT f(n - X[i])) for i = 0, ..., k
 *	+ Base case:
 *		f(0) = false (because if there is no stone left, the first
 *		/ current player will lose)
 *
 *	+ Time complexity: O(n * k)
 */

#include <cstdio>

const int STAN_WIN = 1;
const int OLLIE_WIN = 0;
const int MAX_NUM_KIND = 10;

int determineWinner(int numStone, int stoneTaken[], int numKind);

int main(void)
{
	int numStone, numKind;
	int stoneTaken[MAX_NUM_KIND];

	while(scanf("%d", &numStone) > 0)
	{
		scanf("%d", &numKind);
		for(int i = 0; i < numKind; i++)
			scanf("%d", &stoneTaken[i]);

		int result = determineWinner(numStone, stoneTaken, numKind);
		if(result == STAN_WIN)
			printf("Stan wins\n");
		else
			printf("Ollie wins\n");
	}
	return 0;
}

int determineWinner(int numStone, int stoneTaken[], int numKind)
{
	bool fistPlayerWin[numStone + 1];

	fistPlayerWin[0] = false;

	for(int n = 1; n <= numStone; ++n)
	{
		bool result = false;
		for(int id = 0; id < numKind; ++id)
		{
			int numLeft = n - stoneTaken[id];
			if(numLeft >= 0)
			{
				if(!fistPlayerWin[numLeft])
				{
					// There exists a move that
					// makes Ollie lose
					result = true;
					break;
				}
			}
		}
		fistPlayerWin[n] = result;
	}

	if(fistPlayerWin[numStone])
		return STAN_WIN;
	return OLLIE_WIN;
}
