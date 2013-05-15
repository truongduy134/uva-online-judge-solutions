/*************************************************************
 * Author: Nguyen Truong Duy
 *************************************************************/
#include <stdio.h>

/* Methodology:
 *	+ Let g(n) be the number of calls to compute the n-th Fibonacci number if
 *		we follow the recurrence:
 *			f(n) = 0, f(1) = 1, f(n) = f(n - 1) + f(n - 2) for n >= 2
 *	+ Then clearly, we have
 *			g(0) = 1, g(1) = 1, g(n) = g(n - 1) + g(n - 2) + 1 for n >= 2
 *
 *	+ So 
 *		g(n)    =    (1 1 1)  g(n - 1)        
 *              g(n - 1)     (1 0 0)  g(n - 2)        
 *               1           (0 0 1)     1
 *	+ We can compute g(n) in O(log n) using fast binary exponentiation for
 *		3 x 3 matrix
 *
 *	+ The problem requires us to compute g(n) % b
 */

#define MAX_SIZE 3

int computeNumCallFibo(long long int n, int mod);
void fastMatPow(int matFibo[][MAX_SIZE], long long int pow, int mod, int powMat[][MAX_SIZE]);
void copyMat(int original[][MAX_SIZE], int copy[][MAX_SIZE]);
void multiplyMat(int A[][MAX_SIZE], int B[][MAX_SIZE], int C[][MAX_SIZE], int mod);

int main(void)
{
	int caseId, mod;
	long long int n;

	caseId = 1;
	while(1)
	{
		scanf("%lld %d", &n, &mod);
		if(n == 0 && mod == 0)
			break;

		printf("Case %d: %lld %d %d\n", caseId, n, mod,
				computeNumCallFibo(n, mod));

		caseId++;
	}
	return 0;
}

int computeNumCallFibo(long long int n, int mod)
{
	if(n < 2)
		return 1;

	int matFibo[MAX_SIZE][MAX_SIZE] = {{1, 1, 1}, {1, 0, 0}, {0, 0, 1}}, 
 	    powMat[MAX_SIZE][MAX_SIZE];

	fastMatPow(matFibo, n - 1, mod, powMat);

	return (powMat[0][0] + powMat[0][1] + powMat[0][2]) % mod;
}

void fastMatPow(int matFibo[][MAX_SIZE], long long int pow, int mod, int powMat[][MAX_SIZE])
{
	int identity[MAX_SIZE][MAX_SIZE] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};

	if(pow == 0)
	{
		copyMat(identity, powMat);
		return;	
	}

	if(pow == 1)
	{
		copyMat(matFibo, powMat);
		return;
	}

	int root[MAX_SIZE][MAX_SIZE], temp[MAX_SIZE][MAX_SIZE];
	
	fastMatPow(matFibo, pow >> 1, mod, root);
	multiplyMat(root, root, temp, mod);

	if(pow & 1)
		multiplyMat(matFibo, temp, powMat, mod);
	else
		multiplyMat(identity, temp, powMat, mod);
}

void copyMat(int original[][MAX_SIZE], int copy[][MAX_SIZE])
{
	int row, col;

	for(row = 0; row < MAX_SIZE; row++)
		for(col = 0; col < MAX_SIZE; col++)
			copy[row][col] = original[row][col];
}

void multiplyMat(int A[][MAX_SIZE], int B[][MAX_SIZE], int C[][MAX_SIZE], int mod)
{
	int i, j, k;

	for(i = 0; i < MAX_SIZE; i++)
		for(j = 0; j < MAX_SIZE; j++)
		{
			C[i][j] = 0;
			for(k = 0; k < MAX_SIZE; k++)
				C[i][j] = (C[i][j] + (A[i][k] * B[k][j]) % mod) % mod;
		}
}
