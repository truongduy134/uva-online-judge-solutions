#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

#define MAX_SIZE 100001
#define MAX_MOD 501

long long findNumPairWithDivisibleSum(int arr[], int mSize, int mod);
void findAndRemoveDuplicate(int arr[], int mSize, vector<int> & arrAfterRemovingDuplicate, vector<int> & duplicate);

int main(void)
{
	int T, mSize, arr[MAX_SIZE], mod, caseId, i;

	scanf("%d", &T);
	caseId = 1;
	
	while(caseId <= T)
	{
		scanf("%d %d", &mSize, &mod);

		for(i = 0; i < mSize; i++)
			scanf("%d", & arr[i]);

		printf("Case %d: %lld\n", caseId, findNumPairWithDivisibleSum(arr, mSize, mod));
		caseId++;
	}

	return 0;
}

/* Observation:
 *	+ Let n1, n2 be two numbers and a positive integer k.
 *	+ Let r1 = n1 % k >= 0, and r2 = n2 % k >= 0
 *	+ n1 + n2 is divisible by k if and only if r1 = r2 = 0 or r1 + r2 = k
 */
long long findNumPairWithDivisibleSum(int arr[], int mSize, int mod)
{
	/* nuMod[i] = the number of elements k in arr such that k % mod = i */
	long long numMod[MAX_MOD] = {0}, numPair = 0;
	int i, remain, complement, prev, n;
	vector<int> distinctElements, elementsHavingDuplicate;

	findAndRemoveDuplicate(arr, mSize, distinctElements, elementsHavingDuplicate);
	
	for(i = 0; i < (int) elementsHavingDuplicate.size(); i++)
	{
		n = (elementsHavingDuplicate[i]) << 1;
		if(n % mod == 0)
			numPair++;
	}

	for(i = 0; i < (int) distinctElements.size(); i++)
	{
		remain = distinctElements[i] % mod;
		if(remain < 0)
			remain += mod;

		numMod[remain]++;
	}

	/* 2 C n = n * (n - 1) / 2 */
	numPair += (numMod[0] * (numMod[0] - 1)) >> 1;
	
	for(remain = 1; (remain << 1) <= mod; remain++)
		if(numMod[remain])
		{
			complement = mod - remain;
			if(complement == remain)
				numPair += ((numMod[remain] * (numMod[remain] - 1)) >> 1);
			else
				numPair += numMod[remain] * numMod[complement];
		}

	return numPair;
}

void findAndRemoveDuplicate(int arr[], int mSize, vector<int> & arrAfterRemovingDuplicate, vector<int> & duplicate)
{
	sort(arr, arr + mSize);

	arrAfterRemovingDuplicate.clear();
	duplicate.clear();

	if(mSize <= 0)
		return;

	arrAfterRemovingDuplicate.push_back(arr[0]);

	bool isDuplicate = false;
	for(int i = 1; i < mSize; i++)
		if(arr[i] != arr[i - 1])
		{
			if(isDuplicate)
				// arr[i - 1] has a duplicate. So we add it to duplicate Vector
				// Note that we only keep a single copy of elements that has a duplicate.
				duplicate.push_back(arr[i - 1]);
			arrAfterRemovingDuplicate.push_back(arr[i]);
			isDuplicate = false;
		}
		else
			isDuplicate = true;

	if(isDuplicate)
		duplicate.push_back(arr[mSize - 1]);
}
