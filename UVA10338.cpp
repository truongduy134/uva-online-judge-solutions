#include <cstdio>
#include <cstring>
using namespace std;

#define MAX_LEN 20
#define MAX_NUM_ALPHA 26

void generateFactorial(unsigned long long factorialArr[], int n)
{
	factorialArr[0] = 1;

	for(int i = 1; i <= n; i++)
		factorialArr[i] = factorialArr[i - 1] * (unsigned long long) i;
}
int main(void)
{
	unsigned long long factorialArr[MAX_LEN + 1], numArrange;
	char word[MAX_LEN + 1], trash[MAX_LEN];
	int T, freqArr[MAX_NUM_ALPHA], wordLen, caseId;
	
	generateFactorial(factorialArr, MAX_LEN + 1);

	scanf("%d", &T);
	gets(trash);

	caseId = 1;
	while(caseId <= T)
	{
		memset(freqArr, 0, MAX_NUM_ALPHA * sizeof(int));
		
		gets(word);
		
		wordLen = 0;
		for(int i = 0; word[i] != '\0'; i++)
		{
			freqArr[word[i] - 'A']++;
			wordLen++;
		}
		
		numArrange = factorialArr[wordLen];
		for(int i = 0; i < MAX_NUM_ALPHA; i++)
			if(freqArr[i] > 1)
				numArrange /= factorialArr[freqArr[i]];

		printf("Data set %d: %llu\n", caseId, numArrange);
		
		caseId++;
	}
}
