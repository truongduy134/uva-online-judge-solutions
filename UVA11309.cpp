/*******************************************************************************
 * Author: Nguyen Truong Duy
 ********************************************************************************/

/* Methodology:
 *	+ Consider HH:MM as a number < 2400 (the largest time is 23:59, corresponding to 2359)
 *	+ We generate all palindromic numbers < 2400 AND have the last two digits <= 59
 *	  (A simple way to do that is to conder all numbers < 10000, and check if it is palindromic
 *	   and if the last two digits are less than or equal to 59)
 *	+ Then we have a sorted list L of all palindromic numbers < 2400 satisfying the above requirements.
 *	+ For a given input, find its supremum using binary search technique
 *	  (We can use C++ upper_bound built-in function)
 *
 *	+ Tricky test cases:
 * 	  Input:
 *		23:59
 *		00:59
 *	  Output:
 *		00:00
 *		01:01
 */

#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int MAX_VAL = 2400;
const int NUM_MINUTE_PER_HOUR = 60;

void generatePalindromeNum(vector<int> & palindromeNumVect, int maxVal);
int reverseNum(int num);

int main(void)
{
	int hour, minute, T;
	vector<int> palindromeNumVect;
	vector<int>::iterator it;

	generatePalindromeNum(palindromeNumVect, MAX_VAL);

	scanf("%d", &T);

	while(T)
	{
		scanf("%d:%d", &hour, &minute);

		it = upper_bound(palindromeNumVect.begin(), palindromeNumVect.end(), hour * 100 + minute);

		if(it != palindromeNumVect.end())
			printf("%02d:%02d\n", (*it) / 100, (*it) % 100);
		else
			printf("00:00\n");
		T--;
	}
	return 0;
}

void generatePalindromeNum(vector<int> & palindromeNumVect, int maxVal)
{
	palindromeNumVect.clear();

	for(int i = 0; i < maxVal; i++)
		if(i == reverseNum(i) && i % 100 < NUM_MINUTE_PER_HOUR)
			palindromeNumVect.push_back(i);
}

int reverseNum(int num)
{
	int reverse = 0;

	while(num)
	{
		reverse = reverse * 10 + num % 10;
		num /= 10;
	}

	return reverse;
} 
