#include <cstdio>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

#define MAX_LEN 100

// Return true if (numOne concat numTwo) > (numTwo concat numOne)
bool myNumCompare(const string & numOne, const string & numTwo)
{
	string oneTwo = numOne + numTwo, twoOne = numTwo + numOne;

	return oneTwo > twoOne;
}

int main(void)
{
	int N;
	vector<string> numStrVect;
	char numStr[MAX_LEN + 1];

	while(1)
	{
		scanf("%d", &N);
		if(N == 0)
			break;

		numStrVect.clear();
		for(int i = 0; i < N; i++)
		{
			scanf("%s", numStr);
			numStrVect.push_back(numStr);
		}

		sort(numStrVect.begin(), numStrVect.end(), myNumCompare);

		for(int i = 0; i < N; i++)
			printf("%s", numStrVect[i].c_str());
		printf("\n");
	}

	return 0;
}
