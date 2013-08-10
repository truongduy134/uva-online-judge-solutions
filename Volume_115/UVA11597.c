/*******************************************************************************
 * Author: Nguyen Truong Duy
 ********************************************************************************/

/* Methodology:
 *	+ Let f(n) = the maximum number of spanning trees of the complete graph K(n)
 *		such that no two trees share have a common edge (edge-disjoint 
 *		spanning trees) when n is even (i.e. n = 2k)
 *	  We will show that f(n) = n / 2 = k
 *	
 *	+ A commplete graph K(n) of n vertices has n * (n - 1) / 2 edges.
 *	+ Since each spanning tree of K(n) has exactly n - 1 edges
 *	  There are at most n / 2 = k (since n is even, n = 2k) edge-disjoint
 *		spanning tree.
 *	+ So f(n) <= k
 *	+ Note that a Hamilton path of K(n) is a spanning tree as well.
 *	+ Next we show that when n = 2k, K(n) can be decomposed into k edge-disjoint
 *		Hamilton paths; hence, there exists a construction of k edge-disjoint
 *		spanning trees of K(n)
 *	  Therefore, f(n) = k = n / 2
 *
 *	+ Consider the Hamilton path 
 *		P(0) = 0 n - 1 1 n - 2 2 ... k
 *	  Let P(t) = [(entry in P(t) + 1) % n]
 * 	  For example, P(1) = 1 0 2 n - 1 3 ... k + 1, etc.
 * 	+ Since P(0) is a Hamilton path, P(k) is a Hamilton path for all t = 0, ..., k - 1
 *	+ We see that:
 *	  Let a(i) and a(i + 1) be two consecutive elements on P(0)
 *		Then [a(i) + a(i + 1)] % n = n - 1 if i is even (i starts from 0 to n - 1)
 *		and  [a(i) + a(i + 1)] % n = 0 if i is odd
 *	  Similarly, let b(i) and b(i + 1) be two consecutive elements on P(t) (t = 1 ... k - 1)
 *	  	Then [b(i) + b(i + 1)] % n = t if i is even
 *		and  [b(i) + b(i + 1)] % n = t + 1 if i is odd
 *	  Hence, no two paths among P(t) share a common edge.
 *	+ Therefore, P(0), P(1), ..., P(k - 1) are k edge-disjoint Hamilton paths, hence spanning trees, 
 *	  of K(n) (n = 2k)
 *	+ This complets our proof!
 *
 *	+ Time complexity: O(1)
 */

#include <stdio.h>

int main(void)
{
	int numv, caseid;

	caseid = 1;
	while(1)
	{
		scanf("%d", &numv);
		if(!numv)
			break;

		printf("Case %d: %d\n", caseid, numv >> 1);
		caseid++;
	}

	return 0;
}
