/*******************************************************************************
 * Author: Nguyen Truong Duy
 ********************************************************************************/

/* Methodology:
 *	+ Let us consider a simpler problem first: What is the number of rooted
 *		binary trees of n nodes without considering node labeling?
 *	+ The answer is the n-th Catalan number C(n)
 *	
 *	+ Now return to our original problem: What is number of rooted binary trees
 *		of n distinguishable nodes?
 *	+ To solve this problem, note that for each unlabeling binary tree of n nodes,
 *		we can obtain n! ways to label the nodes. How?
 *	  Considering the in-order traversal of the tree, we obtain an ordered sequence
 *	  of n nodes. Then to name n nodes, there are n! ways.
 *	+ Further, since two underlying unlabeled trees have different structures,
 *		the resulted labeled trees from them based on our method are different
 *		as well.
 *
 *	+ Therefore, the number of binary tress of n distinguishable nodes is
 *			D(n) = n! C(n) (where C(n) is the n-th Catalan number)
 *
 *	+ Since the input n is at most 300, we can precompute 300 values of Đ(n)
 *		in linear time.
 *	+ We use the following recurrence to compute all values of C(n) in linear time:
 *		C(0) = 1
 *		C(n + 1) = 2 * (2n + 1) * C(n) / (n + 2)
 *
 *	+ Time complexity: O(n) pre-processing and O(1) querying
 *
 *	+ Since the values of D(n) is extremely huge, we should use Java BigInteger class.
 */

import java.util.Scanner;
import java.io.PrintWriter;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.math.BigInteger;

class Main
{
	public final static int MAX_QUERY_VAL = 300;

	public static void main(String args[])
	{
		Scanner scan = new Scanner(new BufferedReader(new InputStreamReader(System.in)));
		PrintWriter write = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));

		BigInteger numLabeledTree[] = new BigInteger[MAX_QUERY_VAL + 1];
		precomputeNumLabeledTree(numLabeledTree);

		while(true)
		{
			int numNode = scan.nextInt();
			if(numNode == 0)
				break;

			write.println(numLabeledTree[numNode]);
		}

		write.close();
	}

	public static void precomputeNumLabeledTree(BigInteger numLabeledTree[])
	{
		// Compute factorials
		BigInteger factorial[] = new BigInteger[MAX_QUERY_VAL + 1];
		factorial[0] = BigInteger.ONE;
		for(int n = 1; n <= MAX_QUERY_VAL; n++)
			factorial[n] = factorial[n - 1].multiply(BigInteger.valueOf(n));

		// Compute Catalan number
		BigInteger catalan[] = new BigInteger[MAX_QUERY_VAL + 1];
		catalan[0] = BigInteger.ONE;
		for(int n = 1; n <= MAX_QUERY_VAL; n++)
		{
			int prevN = n - 1;
			int numer = ((prevN << 1) + 1) << 1;
			int denom = prevN + 2;
			catalan[n] = catalan[prevN].multiply(BigInteger.valueOf(numer)).divide(BigInteger.valueOf(denom));
		}

		// Compute number of labeled binary trees
		numLabeledTree[0] = BigInteger.ZERO;
		for(int n = 1; n <= MAX_QUERY_VAL; n++)
			numLabeledTree[n] = factorial[n].multiply(catalan[n]);
	}
}
