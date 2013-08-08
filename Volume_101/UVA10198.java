/*******************************************************************************
 * Author: Nguyen Truong Duy
 ********************************************************************************/

/* Methodology:
 *	+ Let f(n) be the number of numbers whose sum of digits equal to n
 *	+ Idea
 *		- Let A be a number whose sum of digits equals to n
 *		- Case 1: The last digit of A is '1'
 *			+ Then A = B '1' where B is a number whose sum of digits is n - 1
 *		- Case 2: The last digit of A is '4'
 *			+ Then A = B '4' where B is a number whose sum of digits is n - 1 (digit '4'
 *			is treated as same as digit '1')
 *		- Case 3: The last digit of A is '2'
 *			+ + Then A = B '2' where B is a number whose sum of digits is n - 2
 *		- Case 4: The last digit of A is '3'
 *			+ + Then A = B '3' where B is a number whose sum of digits is n - 3
 *	+ So we have the recurrence relation:
 *		f(n) = 2 * f(n - 1) + f(n - 2) + f(n - 3)
 *	+ Base cases:
 *		f(0) = 1	// There is 1 way: write nothing
 *		f(1) = 2	// Numbers are either 1 or 4
 *		f(2) = 5	// Numbers are either 11, 14, 41, 44 or 2
 *
 *	+ Time complexity: O(n) (we do not consider the cost of arithmetic operations here)
 *
 *	+ Since f(n) can be very large, we must use Java BigInteger class.
 */

import java.util.Scanner;
import java.math.BigInteger;
import java.io.PrintWriter;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;

class Main {
	public static final int MAX_VAL = 1000;
	public static final BigInteger TWO = new BigInteger("2");

	public static void main(String [] args)
	{
		Scanner scan = new Scanner(new BufferedReader(new InputStreamReader(System.in)));
		PrintWriter print = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));

		BigInteger [] numWay = new BigInteger[MAX_VAL + 1];

		numWay[0] = BigInteger.ONE;
		numWay[1] = new BigInteger("2");
		numWay[2] = numWay[1].multiply(TWO).add(numWay[0]);
		
		for(int n = 3; n <= MAX_VAL; n++)
			numWay[n] = numWay[n - 1].multiply(TWO).add(numWay[n - 2]).add(numWay[n - 3]);

		while(scan.hasNextInt())
		{
			int n = scan.nextInt();

			print.println(numWay[n]);
		}
		print.close();
	}
}
