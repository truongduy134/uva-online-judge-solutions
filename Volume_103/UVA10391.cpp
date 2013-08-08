/*******************************************************************************
 * Author: Nguyen Truong Duy
 ********************************************************************************/

/* Methodology
 *	+ From the input, we build a set S of words (using C++ STL set, which is
 *		basically a balanced search tree)
 *	+ We traverse the words in the set S in alphabetical order.
 *	+ For each word w in S, we split it into w = ab (where a is a prefix of w and
 *	  b is the remaining non-empty part of w).
 *	  We check if a is in S. If it is, we continue to check if b is in S. If it is,
 *	  w is a compound word.
 *
 *	+ Time complexity: A very loose analysis gives us the performance:
 *		O(n * W^2 * logn) where n is the size of S and W is the maximum
 *		length among words in S.
 */

#include <cstdio>
#include <set>
#include <string>
#include <cstring>

using namespace std;

const int MAX_LEN = 100;

bool IsCompoundWord(const string & word, const set<string> & wordset);

int main(void)
{
	set<string> wordset;
	char word[MAX_LEN + 1];

	while(scanf("%s", word) > 0)
		wordset.insert(word);

	for(set<string>::const_iterator it = wordset.begin(); it != wordset.end(); ++it)
	{
		if(IsCompoundWord(*it, wordset))
			printf("%s\n", it->c_str());
	}

	return 0;
}

bool IsCompoundWord(const string & word, const set<string> & wordset)
{
	int wordlen = word.length();
	if(wordlen < 2)
		return false;

	char tempword[MAX_LEN + 1];

	strcpy(tempword, word.c_str());
	
	for(int ind = 0; ind < wordlen - 1; ind++)
	{
		char backupchar = tempword[ind + 1];
		tempword[ind + 1] = '\0';
		
		if(wordset.find(tempword) != wordset.end())
		{
			tempword[ind + 1] = backupchar;
			if(wordset.find(tempword + ind + 1) != wordset.end())
				return true;
		}

		// Restore original content
		tempword[ind + 1] = backupchar;
	}

	return false; 
}
