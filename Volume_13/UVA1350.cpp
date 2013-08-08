/*******************************************************************************
 * Author: Nguyen Truong Duy
 ********************************************************************************/

/* Methodology:
 *	+ Key observation: The pinary string of K relates to the Zeckendorf representation of K.
 *
 *	+ We can find the Zeckendorf representation of K using greedy algorithm in O(i) time where
 *		F(i) is the largest Fibonacci number less than or equal to K.
 *
 *	+ First, generate the increasing-ordered list L of all Fibonacci numbers less than or equal to 90,000,000
 *	+ Let S be the pinary string of K. Initially, let S be empty.
 *	+ Find the largest index I such that L(I) <= K
 *	  Let n = K.
 *	+ For j = I down to 0
 *		If L(j) > n
 *			Push 0 to S
 *		Else
 *			Push 1 to S
 *			Let n = n - L(j)
 *	+ At the end of the loop, S is the pinary string of K.
 */

#include <cstdio>
#include <vector>
#include <string>

using namespace std;

const int MAX_VAL = 90000000;

void generateFiboList(vector<int> & fiboList, int upperBound);
void getFiboRepresentation(int n, string & fiboRep, const vector<int> & fiboList);

int main(void)
{
	vector<int> fiboList;

	generateFiboList(fiboList, MAX_VAL);

	int T, n;
	scanf("%d", &T);

	while(T)
	{
		scanf("%d", &n);

		string fiboRep;

		getFiboRepresentation(n, fiboRep, fiboList);

		printf("%s\n", fiboRep.c_str());

		T--;
	}
	return 0;
}

void generateFiboList(vector<int> & fiboList, int upperBound)
{
	fiboList.clear();

	if(upperBound >= 1)
		fiboList.push_back(1);
	if(upperBound >= 2)
		fiboList.push_back(2);

	int prev = 1, cur = 2;
	while(cur < upperBound)
	{
		int next = prev + cur;
		prev = cur;
		cur = next;
		fiboList.push_back(next);
	}
}

void getFiboRepresentation(int n, string & fiboRep, const vector<int> & fiboList)
{
	fiboRep.clear();

	int startInd = (int) fiboList.size() - 1;

	// Find the start point: The largest Fibonacci number that less than or equal to n
	while(fiboList[startInd] > n)
		startInd--;


	while(startInd >= 0)
	{
		if(fiboList[startInd] > n)
			fiboRep.push_back('0');
		else
		{
			n -= fiboList[startInd];
			fiboRep.push_back('1');
		}
		startInd--;
	}
}
