#include <cstdio>
#include <bitset>

using namespace std;

#define UPPER_BOUND 2000000

void computeAccumDepthEulerTotient(int depthEulerTotient[]);
void computeEulerTotientVal(int eulerTotient[]);

int main(void)
{
	int accumDepthEulerTotient[UPPER_BOUND + 1];

	computeAccumDepthEulerTotient(accumDepthEulerTotient);

	int T, low, high;

	scanf("%d", &T);
	while(T)
	{
		scanf("%d %d", &low, &high);
		printf("%d\n", accumDepthEulerTotient[high] - accumDepthEulerTotient[low - 1]);

		T--;
	}

	return 0;
}

void computeEulerTotientVal(int eulerTotient[])
{
	for(int n = 0; n <= UPPER_BOUND; n++)
		eulerTotient[n] = n;

	bitset<UPPER_BOUND + 1> isPrime;
	isPrime.set();
	isPrime.set(0, 0);
	isPrime.set(1, 0);

	for(int n = 2; n <= UPPER_BOUND; n++)
		if(isPrime[n])
		{
			eulerTotient[n] = n - 1;

			int nextN = n;
			while(nextN <= UPPER_BOUND - n)
			{
				nextN += n;
				isPrime.set(nextN, 0);

				eulerTotient[nextN] = (eulerTotient[nextN] / n) * (n - 1);
			}
		}
}

void computeAccumDepthEulerTotient(int depthEulerTotient[])
{
	computeEulerTotientVal(depthEulerTotient);

	for(int n = 1; n <= UPPER_BOUND; n++)
		if(depthEulerTotient[n] != 1)
			depthEulerTotient[n] = depthEulerTotient[depthEulerTotient[n]] + 1;


	for(int n = 1; n <= UPPER_BOUND; n++)
		depthEulerTotient[n] += depthEulerTotient[n - 1]; 
}
