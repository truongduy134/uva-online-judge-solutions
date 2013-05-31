/*******************************************************************************
 * Author: Nguyen Truong Duy
 ********************************************************************************/

/* Methodology:
 *	+ Because the length of the input string is at most 80, we can use a simple
 *	  brute force approach.
 *	+ Consider all nC2 + n substrings S of the input string L.
 *	  Check if S is a palindrome and if there is no duplicate of S (this can be
 *		done using C++ STL set)
 *	+ Time complexity: O(L^2 log L) where L is the length of the input string
 */

#include <cstdio>
#include <set>
#include <string>
#include <cstring>

using namespace std;

const int MAX_LEN_LINE = 80;

int countUniquePalinSubstr(char str[]);
bool isPalindrome(char str[], int start, int end);

int main(void)
{
	char line[MAX_LEN_LINE + 1];
	
	while(gets(line) != NULL)
	{
		if(line[0] == '\0')
			continue;

		printf("The string '%s' contains %d palindromes.\n", line,
				countUniquePalinSubstr(line));
	}

	return 0;
}

int countUniquePalinSubstr(char str[])
{
	int count = 0, len = (int) strlen(str);

	set<string> distinctStr;

	for(int start = 0; start < len; start++)
		for(int end = start; end < len; end++)
			if(isPalindrome(str, start, end))
				distinctStr.insert(string(str + start, str + end + 1));

	return (int) distinctStr.size();
}

bool isPalindrome(char str[], int start, int end)
{
	int left = start, right = end;

	while(left <= right)
	{
		if(str[left] != str[right])
			return false;
		left++;
		right--;
	}

	return true;
}

