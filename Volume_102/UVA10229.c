#include <stdio.h>

long long int computeFibonacciMod(int n, int mod);
void computeMatPowMod(long long int mat[][2], int pow, int mod, long long int powerMat[][2]);
void multiplyMat(long long int A[][2], long long int B[][2], long long int C[][2], int mod);

int main(void)
{
	int n, m;

	while(scanf("%d %d", &n, &m) > 0)
	{
		/* Print Fibo(n) % 2^m */
		printf("%lld\n", computeFibonacciMod(n, 1 << m));
	}
	return 0;
}

long long int computeFibonacciMod(int n, int mod)
{
	if(n == 1)
		return 1;
	if(n == 0)
		return 0;

	long long int fiboMat[2][2] = {{1, 1}, {1, 0}}, powerFiboMat[2][2];

	computeMatPowMod(fiboMat, n - 1, mod, powerFiboMat);

	return powerFiboMat[0][0]; 
}

void computeMatPowMod(long long int mat[][2], int pow, int mod, long long int powerMat[][2])
{
	int i, j;

	if(pow == 0)
	{
		powerMat[0][0] = 1;
		powerMat[0][1] = 0;
		powerMat[1][0] = 0;
		powerMat[1][1] = 1;
		return;
	}

	if(pow == 1)
	{
		for(i = 0; i < 2; i++)
			for(j = 0; j < 2; j++)
				powerMat[i][j] = mat[i][j] % mod;
		return;		
	}

	long long int rootMat[2][2], temp[2][2];

	computeMatPowMod(mat, pow >> 1, mod, rootMat);

	multiplyMat(rootMat, rootMat, temp, mod);

	if(pow & 1)
	{
		multiplyMat(temp, mat, powerMat, mod);
	}
	else
	{
		for(i = 0; i < 2; i++)
			for(j = 0; j < 2; j++)
				powerMat[i][j] = temp[i][j];
	}
}

void multiplyMat(long long int A[][2], long long int B[][2], long long int C[][2], int mod)
{
	C[0][0] = ((A[0][0] * B[0][0]) % mod + (A[0][1] * B[1][0]) % mod) % mod;
	C[0][1] = ((A[0][0] * B[0][1]) % mod + (A[0][1] * B[1][1]) % mod) % mod;
	C[1][0] = ((A[1][0] * B[0][0]) % mod + (A[1][1] * B[1][0]) % mod) % mod;
	C[1][1] = ((A[1][0] * B[0][1]) % mod + (A[1][1] * B[1][1]) % mod) % mod;
}
