/*******************************************************************************
 * Author: Nguyen Truong Duy
 ********************************************************************************/

/* Methodology:
 *	+ Use STL map to count the frequency of all substrings of the original string S.
 *
 *	+ Time complexity: O(L * N * log L) where L is the length of S, N is the length
 *		of the substrings. 
 */

#include <cstdio>
#include <map>
#include <string>
#include <cstring>

using namespace std;

const int MAX_LEN_TEXT = 1000000;

void findPassword(char encodeText[], int lenPassword, string & password);

int main(void)
{
	char encodeText[MAX_LEN_TEXT + 1];
	int lenPassword;
	string password;

	while(scanf("%d %s", &lenPassword, encodeText) > 0)
	{
		findPassword(encodeText, lenPassword, password);
		printf("%s\n", password.c_str());
	}

	return 0;
}

void findPassword(char encodeText[], int lenPassword, string & password)
{
	map<string, int> mapSubstrToFreq;

	int lenText = (int) strlen(encodeText);

	for(int ind = 0; ind + lenPassword <= lenText; ind++)
	{
		string subStr(encodeText + ind, encodeText + ind + lenPassword);
		
		map<string, int>::iterator it = mapSubstrToFreq.find(subStr);
		if(it == mapSubstrToFreq.end())
			mapSubstrToFreq[subStr] = 0;
		else
			(it->second)++;
	}

	int maxFreq = 0;
	map<string, int>::iterator maxSubstrIt;
	for(map<string, int>::iterator it = mapSubstrToFreq.begin(); it != mapSubstrToFreq.end(); it++)
	{
		if(it->second > maxFreq)
		{
			maxFreq = it->second;
			maxSubstrIt = it;
		}
	}

	password = maxSubstrIt->first;
}
