/*******************************************************************************
 * Author: Nguyen Truong Duy
 ********************************************************************************/

/* Methodology:
 *	+ Use greedy algorithm
 *
 *	+ Sort the array of the length of morning routes in non-decreasing order. Then
 *		we obtain
 *		M[0], M[1], ..., M[n]
 *	+ Sort the array of the length of evening routes in non-increasing order. Then 
 *		we obtain
 *		E[0], E[1], ..., E[n]
 *	+ The matching of M[i] with E[i] is optimal
 *	+ The total overtime paid amount is
 *		sum( r * max(0, M[i] + E[i] - d) )
 *
 *	+ Time complexity: O(n log n) where n is the number of drivers (if we use merge sort, etc.)
 *
 *	+ Note: It is not advisable to use counting sort in this case because n <= 100 while
 *		the largest value of length of a route can be 10000.
 */

#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

int computeMinPayExtra(vector<int> & morningRoute, vector<int> & eveningRoute, int maxDist, int extraPayUnit);

int main(void)
{
	int numDriver, maxDist, extraPayUnit;
	vector<int> morningRoute, eveningRoute;

	while(1)
	{
		scanf("%d %d %d", &numDriver, &maxDist, &extraPayUnit);
		if(!(numDriver || maxDist || extraPayUnit))
			break;

		morningRoute.assign(numDriver, 0);
		eveningRoute.assign(numDriver, 0);

		for(int i = 0; i < numDriver; i++)
			scanf("%d", &morningRoute[i]);
		for(int i = 0; i < numDriver; i++)
			scanf("%d", &eveningRoute[i]);

		printf("%d\n", computeMinPayExtra(morningRoute, eveningRoute, maxDist, extraPayUnit));
	}
	return 0;
}

int computeMinPayExtra(vector<int> & morningRoute, vector<int> & eveningRoute, int maxDist, int extraPayUnit)
{
	sort(morningRoute.begin(), morningRoute.end());
	sort(eveningRoute.begin(), eveningRoute.end());
	reverse(eveningRoute.begin(), eveningRoute.end());

	int extraAmount = 0, diffDist;
	int numDriver = (int) morningRoute.size();
	for(int i = 0; i < numDriver; i++)
	{
		diffDist = morningRoute[i] + eveningRoute[i] - maxDist;
		if(diffDist > 0)
			extraAmount += diffDist * extraPayUnit; 
	}

	return extraAmount;
}
