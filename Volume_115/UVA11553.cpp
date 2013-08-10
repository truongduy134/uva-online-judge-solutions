/*******************************************************************************
 * Author: Nguyen Truong Duy
 ********************************************************************************/

/* Methodology:
 *	+ Key observation: 
 *		- In the game, Alice always makes the first move, and Bob reacts to 
 *		  Alice's choice.
 *		- The order in which Alice chooses rows does not matter. From the view
 *		  of Bobs, his strategy is to choose what column with respect to
 *		  the row Alice has chosen.
 *	+ Therefore, a strategy of Bob can represented as an array S
 *	  S[i] = j means that Bob will choose column i if Alice chooses row i
 *	+ Hence, in total, there are N! strategies for Bob (which are permutation of
 *	  {0, ..., N - 1} (there are N rows and N columns)
 *	+ Because N <= 8, we can try all strategies for Bob.
 *	+ For a strategy S of Bob, the number of candies Alice can earn is
 *		f(M, S) = sum M[i][S[i]] for i = 0, ... N - 1
 *	+ The best number Alice can earn Alice can earn is the minimum number
 *		among all results corresponding to all Bob's strategies, i.e.
 *			min f(M, S) for all N! strategies S
 *
 *	+ Time complexity: O(N * N!)
 *
 * NOTE: There is a more efficient algorithm to solve this problem using Dynamic Programming
 *	and bitmask technique. We can achieve O(n * 2^n) solution with the second approach.
 */

#include <algorithm>
#include <cstdio>

using namespace std;

const int MAX_SIZE = 8;
const int INF = 1000000000;

int GetBestAmountCandyAlice(int board[MAX_SIZE][MAX_SIZE], int msize);

int main(void)
{
	int numcase, msize, board[MAX_SIZE][MAX_SIZE];

	scanf("%d", &numcase);
	while(numcase)
	{
		scanf("%d", &msize);
		for(int row = 0; row < msize; row++)
			for(int col = 0; col < msize; col++)
				scanf("%d", &board[row][col]);

		printf("%d\n", GetBestAmountCandyAlice(board, msize));
		numcase--;
	}
	return 0;
}

int GetBestAmountCandyAlice(int board[MAX_SIZE][MAX_SIZE], int msize)
{
	int strategy[MAX_SIZE];

	for(int i = 0; i < msize; i++)
		strategy[i] = i;

	// Because Bob plays perfectly, and we are considering all
 	// possible stragies for Bob to play against Alice, Alice's maximum
	// number of candies is the minimum obtained among all strategies of Bob.
	int maxnumcandy = INF;
	do
	{
		int numcandy = 0;
		for(int alicerow = 0; alicerow < msize; alicerow++)
		{
			int bobcol = strategy[alicerow];
			numcandy += board[alicerow][bobcol];
		}
		if(numcandy < maxnumcandy)
			maxnumcandy = numcandy;
	} while(next_permutation(strategy, strategy + msize));

	return maxnumcandy;
}
