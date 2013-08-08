/*******************************************************************************
 * Author: Nguyen Truong Duy
 ********************************************************************************/

/* Methodology
 *	+ We define the following function:
 *		f(n) = the number of ways light rays to pass through or be reflected 
 *		       after changing direction n times
 *
 *		a(n) = the number of ways light rays to pass through or be reflected 
 *		       after changing direction n times AND
 *		       the last stroke touches 2 layers
 *		b(n) = the number of ways light rays to pass through or be reflected 
 *		       after changing direction n times AND
 *		       the last stroke touches 3 layers
 *		Clearly, f(n) = a(n) + b(n)
 *
 *	+ Clearly,
 *		b(n + 1) = a(n) (because we can only add 1 more stroke starting from
 *			from the middle layer)
 *		a(n + 1) = b(n) + a(n) (because we can add 1 more stroke starting
 *			from the bottom or top to the opposite from both elements
 *			counted in a(n) and b(n))
 *
 *	+ In summary, we have
 *		b(n + 1) = a(n)		for n >= 0
 *		a(n + 1) = a(n) + b(n)  for n >= 0
 *		f(n) = a(n) + b(n)
 *	+ Base cases: 
 *		b(0) = 1 and a(0) = 0
 *
 *	+ We can precompute all values of f(n) for 0 <= n <= 1000 in linear time.
 *	+ Time complexity: O(n) preprocessing and O(1) querying
 *
 *	+ Note: since the answer is quite big, use Java BigInteger class.
 */

import java.util.Scanner;
import java.io.PrintWriter;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.math.BigInteger;

class Main
{
	public static final int MAX_VAL = 1000;

	public static void main(String args[])
	{
		Scanner scanner = new Scanner(new BufferedReader(new InputStreamReader(System.in)));
		PrintWriter writer = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));

		BigInteger numWayReflect[] = new BigInteger[MAX_VAL + 1];
		precomputeNumWayReflect(numWayReflect);

		while(scanner.hasNextInt())
		{
			int numReflect = scanner.nextInt();
			writer.println(numWayReflect[numReflect]);
		}

		writer.close();
	}

	public static void precomputeNumWayReflect(BigInteger numWayReflect[])
	{
		BigInteger numWayOneLvl[] = new BigInteger[MAX_VAL + 1];
		BigInteger numWayTwoLvl[] = new BigInteger[MAX_VAL + 1];

		numWayOneLvl[0] = BigInteger.ZERO;
		numWayTwoLvl[0] = BigInteger.ONE;
		numWayReflect[0] = BigInteger.ONE;

		for(int numTime = 1; numTime <= MAX_VAL; numTime++)
		{
			numWayOneLvl[numTime] = numWayTwoLvl[numTime - 1];
			numWayTwoLvl[numTime] = numWayOneLvl[numTime - 1].add(numWayTwoLvl[numTime - 1]);
			numWayReflect[numTime] = numWayOneLvl[numTime].add(numWayTwoLvl[numTime]);
		}
	}
}
