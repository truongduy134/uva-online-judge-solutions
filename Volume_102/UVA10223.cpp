/*******************************************************************************
 * Author: Nguyen Truong Duy
 ********************************************************************************/

/* Methodology:
 *	+ This is a Catalan number problem.
 *	+ Let C(n) denote the n-th Catalan number
 *	+ Given n nodes (n >= 1), the maximum number of rooted binary tree containing
 *		n nodes is C(n).
 *	+ In this problem, we are given C(n), and then asked to output n.
 *
 *	+ Program flow:
 *		- Since the input fits to 32 bit unsigned integer, we just
 *		need to generate the first 20 Catalan numbers (It is better
 *		to use 64-bit integers).
 *		- We can use the following recurrence relation:
 *			C(0) = 1
 *			C(n + 1) = 2 * (2n + 1) * C(n) / (n + 2)
 *		- For each input number x, binary search on the sorted Catalan
 *			number array to find index i such that C(i) = x	 
 */

#include <cstdio>
#include <algorithm>
#include <map>

using namespace std;

const int NUM_CATALAN_CONSIDERED = 20;

void generateCatalanMap(int numGenerate, map<long long, int> & mapValToIdCatalan);

int main(void)
{
	map<long long, int> mapValToIdCatalan;

	generateCatalanMap(NUM_CATALAN_CONSIDERED, mapValToIdCatalan);
	
	long long numTree;

	while(scanf("%lld", &numTree) > 0)
	{
		map<long long, int>::const_iterator it = mapValToIdCatalan.find(numTree);
		if(it != mapValToIdCatalan.end())
			printf("%d\n", it->second);
	}

	return 0;
}

void generateCatalanMap(int numGenerate, map<long long, int> & mapValToIdCatalan)
{
	mapValToIdCatalan.clear();

	int id = 0;
	long long prev = 1;

	while(id < numGenerate)
	{
		// Generate the (id + 1)-th Catalan number
		prev = 2 * (2 * id + 1) * prev / (id + 2);
		id++;
		mapValToIdCatalan[prev] = id;
	}
} 
