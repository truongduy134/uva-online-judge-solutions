#include <cstdio>
#include <vector>

using namespace std;

const int UPPERBOUND = 1 << 20;

int countNumCompositePrime(int arr[], int mSize, vector<bool> & compositePrimeSieve);
void generateCompositePrimeSieve(vector<bool> & compositePrimeSieve, int upperBound);
void generateCompositeSieve(vector<bool> & compositeSieve, int upperBound);

int main(void)
{
	int mSize, arr[UPPERBOUND];
	vector<bool> compositePrimeSieve;

	generateCompositePrimeSieve(compositePrimeSieve, UPPERBOUND);
	
	while(scanf("%d", &mSize) > 0)
	{
		for(int i = 0; i < mSize; i++)
			scanf("%d", &arr[i]);

		printf("%d\n", countNumCompositePrime(arr, mSize, compositePrimeSieve));
	}
	return 0;
}

int countNumCompositePrime(int arr[], int mSize, vector<bool> & compositePrimeSieve)
{
	int count = 0;

	for(int ind = 0; ind < mSize; ind++)
		if(compositePrimeSieve[arr[ind]])
			count++;

	return count;
}

void generateCompositePrimeSieve(vector<bool> & compositePrimeSieve, int upperBound)
{
	// First, mark all composite numbers to be true
	generateCompositeSieve(compositePrimeSieve, upperBound);

	compositePrimeSieve[0] = compositePrimeSieve[1] = false;

	// The first composite prime is 4
	for(int n = 4; n <= upperBound; n++)
		if(compositePrimeSieve[n] == true)
		{
			// Multiple of n is not a composite prime. Mark it as false
			for(int nextN = n + n; nextN <= upperBound; nextN += n)
				compositePrimeSieve[nextN] = false;
		}
}

void generateCompositeSieve(vector<bool> & compositeSieve, int upperBound)
{
	// Do not consider 0 and 1
	compositeSieve.assign(upperBound + 1, false);

	for(int n = 2; n <= upperBound; n++)
		if(compositeSieve[n] == false)
		{
			for(int nextN = n + n; nextN <= upperBound; nextN += n)
				compositeSieve[nextN] = true;
		}
}


