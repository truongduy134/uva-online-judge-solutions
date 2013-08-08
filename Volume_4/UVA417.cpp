/*******************************************************************************
 * Author: Nguyen Truong Duy
 ********************************************************************************/

/* Methodology:
 *	+ Because there are totally 83681 valid strings, we can use the brute-force approach
 *		to solve this problem.
 *	+ First, generate all valid strings of length 1, 2, 3, 4, 5 in order. Strings of equal
 *		length are again generated in lexicographical order. Each string should follows
 *		strict lexicographical order.
 *	  This can be done recursively (for a particular length).
 *	+ Map each string to a number indicating the order it is generated.
 *	+ For a query string S, if it is not in the map, output 0.
 *	  Otherwise, output the integer that S is mapped to.
 */

#include <cstdio>
#include <map>
#include <string>

using namespace std;

const int MAX_LEN = 5;

void generateWordInd(map<string, int> & mapStrToInd);
void generateIncreasingWord(int lenLeft, string & curStr, map<string, int> & mapStrToInd, int * curInd);

int main(void)
{
	map<string, int> mapStrToInd;

	generateWordInd(mapStrToInd);

	char str[MAX_LEN + 1];
	while(scanf("%s", str) > 0)
	{
		map<string, int>::iterator it = mapStrToInd.find(str);

		int result = -1;
		if(it != mapStrToInd.end())
			result = it->second;
		printf("%d\n", result + 1);
	}
	return 0;
}

void generateWordInd(map<string, int> & mapStrToInd)
{
	int curInd = 0;

	for(int len = 1; len <= MAX_LEN; len++)
	{
		string emptyStr;
		generateIncreasingWord(len, emptyStr, mapStrToInd, &curInd);
	} 
}

void generateIncreasingWord(int lenLeft, string & curStr, map<string, int> & mapStrToInd, int * curInd)
{
	if(lenLeft == 0)
	{
		mapStrToInd[curStr] = *curInd;
		(*curInd)++;
		return;
	}

	char prevChar = 'a' - 1;
	if(curStr.length() > 0)
		prevChar = curStr[curStr.length() - 1];

	for(char nextChar = prevChar + 1; nextChar <= 'z'; ++nextChar)
	{
		curStr.push_back(nextChar);
		generateIncreasingWord(lenLeft - 1, curStr, mapStrToInd, curInd);

		// Backtrack
		curStr.erase(curStr.length() - 1, 1);
	}
}
