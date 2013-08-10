/*******************************************************************************
 * Author: Nguyen Truong Duy
 ********************************************************************************/

/* Methodology:
 *	+ IMPORTANT NOTE: Although M and the left ends and right ends of intervals 
 *		are integers, our job is to cover the whole REAL interval [0, M]
 *		completely.
 *		Therefore, for example, we cannot cover [0, 1] with these two intervals
 *		[-4, 0] and [1, 2]
 *
 *	+ We can use greedy algorithm to solve this problem.
 *	+ Let f([x, y]) = the number of segments needed to cover the REAL interval [x, y]
 *	  Then clearly,
 *		f([x, y]) = min(f[z, y]) + 1 for any interval [t, z] that covers x
 *	  and f([x, y]) = 0 if y < x (i.e. the interval is empty)
 *
 *	+ However, if we are more careful, we will see that
 *		f([x, y]) = f([z, y]) + 1, in which we choose [t, z] that covers x and
 *	  has the largest (or furthest) right ends.
 *	+ And note that [t, z] can covers x if and only if t <= x and z >= x
 *
 *	+ First, sort the list of intervals by their left ends in non-decreasing order. 
 *		If two intervals have the same left end, we sort them by their right
 *		ends in non-decreasing order.
 *	+ Second, let x be the next point we need to cover on the right.
 *	  At the very beginning, x = 0
 *	  Then let S be the set of intervals [y z] with y <= x. Among S, choose the interval
 *		[y zmax] with the largest possible right end.
 *	  If no such segment exists or zmax < x, then the interval [x, M] cannot be covered.
 *	  Otherwise, we choose the segment [y, zmax] to cover x. Then we continue to try to cover
 *	  	the interval [zmax, M] with the REMAINING intervals (EXCLUDING intervals in S)
 *	+ Do it until zmax >= M (i.e. we have covered everything until the left side of M) or
 *		we have no interval left.
 *
 *	+ Time complexity: O(n log n) where n is the number of input intervals used to cover [0 M]
 *		(Step 1, the sorting part, can be done in O(n log n). Step 2 clearly can be done
 *			in O(n))
 */
 
/* This comment block is to prove the correctness of the greedy algorithm (Readers can skip it if
 *	they are not interested)
 * To prove the greedy algorithm correct, we need to show 2 things
 *	1) There is an optimal substructure, i.e.
 *	   Theorem 1: Let S be an optimal coverage of the REAL interval [x, y]. Let [z, t] be
 *		an interval in S that covers x (the right side). Then S \ {[z, t]} is an optimal
 *		coverage of [t, y].
 *	
 *	2) There is an optimal coverage that uses the greedy choice, i.e.
 *	   Theorem 2: Consider the REAL interval [x, y]. Assume there is a coverage of [x, y]. Let Y be 
 *		the set of intervals that covers x. Let [zmax tmax] be in Y such that tmax is maximum
 *		(Among those that have the same right ends tmax, choose zmax to be the minimum).
 *		Then there exists an optimal coverage of [x, y] containing [zmax, tmax] 
 *
 * Proof of Theorem 1:
 *	+ Suppose S \ {[z, t]} is NOT an optimal coverage of [t, y]. Then, there must be an optimal
 *		coverage S' of [t, y] such that
 *			|S'| < |S \ {[z, t]}| < |S| - 1
 *	+ Clearly, adding [z, t] to S' to obtain S'', we have S'' covers [x, y]
 *	+ And |S''| = |S'| + 1 < |S|. This is a contradiction that S is an optimal coverage of
 *		[x, y], which means |S| is minimum.
 *
 * Proof of Theorem 2:
 *	+ Let S be an optimal coverage of [x, y]
 *	+ If [zmax tmax] is in S, we are done.
 *	+ Suppose [zmax tmax] is not in S.
 *	+ Let [z t] be an interval in S that covers x.
 *	+ Clearly, [zmax tmax] covers x (by definition). 
 *	+ Let S' = S \ {[z t]} + {[zmax tmax]}. Clearly S' still covers [x, y] and have
 * 	  the same cardinality. Therefore, S' is optimal as well.
 */

#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

struct Interval
{
	int start_, end_;
};

bool AreCovered(const Interval & interval, int point)
{
	if(point < interval.start_ || point > interval.end_)
		return false;
	return true;
}

bool CompareInterval(const Interval & one, const Interval & two)
{
	if(one.start_ < two.start_)
		return true;
	if(one.start_ > two.start_)
		return false;
	// If left ends are equal, compare right ends
	if(one.end_ < two.end_)
		return true;
	return false;
}

const int MINUS_INF = -1000000000;
void FindMinimalCover(const Interval & covered, vector<Interval> & intervalvect, 
		      vector<Interval> & resultvect);

int main(void)
{
	int numcase;
	vector<Interval> intervalvect, resultvect;
	Interval covered;

	scanf("%d", &numcase);
	while(numcase)
	{
		intervalvect.clear();
		
		covered.start_ = 0;
		scanf("%d", &covered.end_);

		while(1)
		{
			Interval newinterval;
			scanf("%d %d", &newinterval.start_, &newinterval.end_);
			if(newinterval.start_ == 0 && newinterval.end_ == 0)
				break;
			intervalvect.push_back(newinterval);
		}

		FindMinimalCover(covered, intervalvect, resultvect);

		printf("%d\n", (int) resultvect.size());
		for(int i = 0; i < (int) resultvect.size(); i++)
			printf("%d %d\n", resultvect[i].start_, resultvect[i].end_);

		if(numcase > 1)
			printf("\n");
		numcase--;
	}

	return 0;
}

void FindMinimalCover(const Interval & covered, vector<Interval> & intervalvect, 
		      vector<Interval> & resultvect)
{
	int nextrightcover = covered.start_;
	int numsegment = (int) intervalvect.size();
	int curseg = 0;

	// Sort intervals first by their left ends, then secondly by their right ends
	sort(intervalvect.begin(), intervalvect.end(), CompareInterval);

	resultvect.clear();
	
	while(nextrightcover < covered.end_ && curseg < numsegment)
	{
		if(intervalvect[curseg].start_ > nextrightcover)
		{
			resultvect.clear();
			return;
		}

		int maxright = MINUS_INF;
		int maxrightind = -1;
		while(curseg < numsegment && intervalvect[curseg].start_ <= nextrightcover)
		{
			if(intervalvect[curseg].end_ > maxright)
			{
				maxright = intervalvect[curseg].end_;
				maxrightind = curseg;
			}
			curseg++;
		}
		
		if(maxright < nextrightcover)
		{
			resultvect.clear();
			return;	
		}

		resultvect.push_back(intervalvect[maxrightind]);
		nextrightcover = maxright;
	}

	if(nextrightcover < covered.end_)
		resultvect.clear();
}
