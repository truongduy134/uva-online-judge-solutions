/*******************************************************************************
 * Author: Nguyen Truong Duy
 ********************************************************************************/

/* Methodology:
 *	+ This problem can be solved by the brute-force solution.
 *	
 *	+ Program flow:
 *		- Generate the sorted list L of all Fibonacci number less than or
 *		  equal to 10^100. After some experiment, the 480-th Fibonacci
 *		  number is larger than 10^100.
 *		- For each interval [a, b], find the lowest index i in L such
 *		  that L[i] >= a (i = size(L) if such an index does not exist),
 *		  and the largest index j in L such that L[j] <= b (j = -1 if
 *		  such an index does not exist). The values of i and j can be
 *		  found using linear search or binary search.
 *		- Then the number of Fibonacci numbers in [a, b] is
 *				max(0, j - i + 1)
 *	+ Because the integers are very largest, exceeding 2^64 - 1, it is
 *		convenient to use Java BigInteger class.
 */

import java.util.Scanner;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.PrintWriter;
import java.math.BigInteger;

class Main
{
	public static final int MAX_NUM_FIBO = 480;

	public static void main(String args[])
	{
		/* IO intilization */
		Scanner scan = new Scanner(new BufferedReader(new InputStreamReader(System.in)));
		PrintWriter writer = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));

		BigInteger fiboArr[] = new BigInteger[MAX_NUM_FIBO];

		generateFibo(fiboArr, MAX_NUM_FIBO);

		while(true)
		{
			BigInteger lowerBound = new BigInteger(scan.next());
			BigInteger upperBound = new BigInteger(scan.next());
			if(lowerBound.equals(BigInteger.ZERO) &&
			   upperBound.equals(BigInteger.ZERO))
				break;

			writer.println(countNumFibo(fiboArr, lowerBound, upperBound));
		}

		writer.close();
	}

	public static void generateFibo(BigInteger fiboArr[], int numFibo)
	{
		fiboArr[0] = BigInteger.ONE;
		fiboArr[1] = new BigInteger("2");
		for(int fiboId = 2; fiboId < numFibo; fiboId++)
			fiboArr[fiboId] = fiboArr[fiboId - 1].add(fiboArr[fiboId - 2]);
	}

	public static int countNumFibo(BigInteger fiboArr[], BigInteger lowerBound, BigInteger upperBound)
	{
		int lowerInd = 0, upperInd = 0;
		int numFibo = fiboArr.length;

		for(lowerInd = 0; lowerInd < numFibo; lowerInd++)
			if(fiboArr[lowerInd].compareTo(lowerBound) >= 0)
				break;
		if(lowerInd >= numFibo)
			return 0;

		for(upperInd = numFibo - 1; upperInd >= 0; upperInd--)
			if(fiboArr[upperInd].compareTo(upperBound) <= 0)
				break;
		
		int numFiboInterval = upperInd - lowerInd + 1;
		if(numFiboInterval < 0)
			numFiboInterval = 0;
		return numFiboInterval; 
	}
}
