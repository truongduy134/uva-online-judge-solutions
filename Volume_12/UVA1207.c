/*******************************************************************************
 * Author: Nguyen Truong Duy
 ********************************************************************************/

/* Methodology:
 *	+ This is a classical Global Alignment Problem. It can be solved using Dynamic Programming.
 *
 *	+ Let f(n, m) = the minimum of transformation operation to transform the string X[0 ... n]
 *		to the string Y[0 ... m]
 *	+ Then:
 *		f(n, m) = min { 1 + f(n - 1, m),	// Delete the character X[n]
 *				1 + f(n, m - 1),	// Insert the character Y[m] after X[n]
 *				delta + f(n - 1, m - 1)	// Update X[n] := Y[m] if they are different
 *			      }
 *	  where delta = 0 if X[n] = Y[m] and delta = 1 otherwise
 *
 *	+ Base case:
 *		f(n, m) = 0 if n < 0 and m < 0 (Both X and Y equal empty string)
 *		f(n, m) = m + 1 if n < 0 and m >= 0 (Insert m + 1 characters of Y[0 ... m] into X)
 *		f(n, m) = n + 1 if m < 0 and n >= 0 (Delete n + 1 characters of X[0 ... n])
 *
 *	+ Time complexity: O((n + 1) * (m + 1)) = O(nm)
 */

#include <stdio.h>
#include <string.h>

#define MAX_LEN 1000

int getMinTransformOp(char strX[], int indX, char strY[], int indY, int memoTable[][MAX_LEN]);

int main(void)
{
	int memoTable[MAX_LEN][MAX_LEN];
	int lenX, lenY;
	char strX[MAX_LEN + 1], strY[MAX_LEN + 1];

	while(scanf("%d %s", &lenX, strX) > 0)
	{
		scanf("%d %s", &lenY, strY);
	
		memset(memoTable, -1, MAX_LEN * MAX_LEN * sizeof(int));
		
		printf("%d\n", getMinTransformOp(strX, lenX - 1, strY, lenY - 1, memoTable));		
	}

	return 0;
}

int getMinTransformOp(char strX[], int indX, char strY[], int indY, int memoTable[][MAX_LEN])
{
	if(indX < 0 && indY < 0)
		return 0;
	if(indX < 0)
		/* Insert indY + 1 characters into the empty string X */
		return indY + 1;
	if(indY < 0)
		/* Delete indX + 1 characters from X */
		return indX + 1;
	
	if(memoTable[indX][indY] >= 0)
		return memoTable[indX][indY];

	int minOp = 0, op;

	minOp = getMinTransformOp(strX, indX - 1, strY, indY - 1, memoTable);
	if(strX[indX] != strY[indY])
		/* Change 1 letter */
		minOp += 1;

	/* Insert a letter */
	op = 1 + getMinTransformOp(strX, indX, strY, indY - 1, memoTable);
	if(op < minOp)
		minOp = op;

	/* Delete a letter */
	op = 1 + getMinTransformOp(strX, indX - 1, strY, indY, memoTable);
	if(op < minOp)
		minOp = op;

	memoTable[indX][indY] = minOp;
	return minOp;
}
