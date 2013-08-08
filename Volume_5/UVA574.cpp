#include <cstdio>
#include <vector>
#include <set>
using namespace std;

#define MAX_SIZE 14

bool compareListSum(const vector<int> & listOne, const vector<int> & listTwo)
{
	int minSize = (int) listOne.size();
	if(minSize > (int) listTwo.size())
		minSize = (int) listTwo.size();

	for(int i = 0; i < minSize; i++)
		if(listOne[i] > listTwo[i])
			return true;

	return false;
}

void findAllSum(set<vector<int>, bool(*)(const vector<int> &, const vector<int> &)> & result, const vector<int> & arr, int num, int ind, int sumLeft, vector<int> partialResult)
{
	if(sumLeft < 0 || (ind >= num && sumLeft != 0))
		return;
	if(sumLeft == 0)
	{
		result.insert(partialResult);
		return;
	}
	// Not take this element
	findAllSum(result, arr, num, ind + 1, sumLeft, partialResult);

	// Take this element
	partialResult.push_back(arr[ind]);
	findAllSum(result, arr, num, ind + 1, sumLeft - arr[ind], partialResult);
}

int main(void)
{
	vector<int> arr;
	set<vector<int>, bool(*)(const vector<int> &, const vector<int> &)> result(compareListSum);
	set<vector<int>, bool(*)(const vector<int> &, const vector<int> &)>::iterator it;
	int sum, n;
	vector<int> empty;
	vector<int> hasTaken;

	while(1)
	{
		scanf("%d %d", &sum, &n);
		if(!(sum || n))
			break;

		arr.assign(n, 0);
		result.clear();
		hasTaken.assign(1 << MAX_SIZE + 1, 0);
 
		for(int i = 0; i < n; i++)
			scanf("%d", &arr[i]);
		
		findAllSum(result, arr, n, 0, sum, empty);
		
		printf("Sums of %d:\n", sum);
		if(result.size() == 0)
			printf("NONE\n");
		else
		{
			for(it = result.begin(); it != result.end(); it++)
			{
				printf("%d", (*it)[0]);
				for(int j = 1; j < (int) (*it).size(); j++)
					printf("+%d", (*it)[j]);
				printf("\n");
			}
		}
	}

	return 0;
}
