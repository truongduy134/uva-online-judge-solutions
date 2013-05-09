#include <cstdio>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

bool compareStrByLength(const string & one, const string & two)
{
	return one.length() < two.length();
}

#define MAX_LEN 1000

bool isImmediatelyDecodable(vector<string> & codeVect);
bool isPrefix(const string & one, const string & two);

int main(void)
{
	vector<string> codeVect;
	char str[MAX_LEN + 1];
	bool endProgram = false;
	int caseId = 1;

	while(1)
	{
		codeVect.clear();
		while(1)
		{
			if(scanf("%s", str) <= 0)
			{
				endProgram = true;
				break;
			}
			
			if(str[0] == '9')
				break;

			codeVect.push_back(str);
		}

		if(endProgram)
			break;

		if(isImmediatelyDecodable(codeVect))
			printf("Set %d is immediately decodable\n", caseId);
		else
			printf("Set %d is not immediately decodable\n", caseId);

		caseId++;
	}
	return 0;
}

bool isImmediatelyDecodable(vector<string> & codeVect)
{
	sort(codeVect.begin(), codeVect.end(), compareStrByLength);

	for(int i = 0; i < (int) codeVect.size(); i++)
		for(int j = i + 1; j < (int) codeVect.size(); j++)
			if(isPrefix(codeVect[i], codeVect[j]))
				return false;

	return true;
}
bool isPrefix(const string & one, const string & two)
{
	if(one.length() > two.length())
		return false;
	for(int ind = 0; ind < one.length(); ind++)
		if(one[ind] != two[ind])
			return false;
	return true;
}
