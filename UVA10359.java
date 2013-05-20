/*******************************************************
 * Author: Nguyen Truong Duy
 *******************************************************/

/* Methodology:
 *	+ Let f(n) be the number of ways to tile 2 x n rectangle by 2 x 1 or 2 x 2 tiles
 *	+ Base case:
 *		f(0) = 1
 *		f(1) = 1
 *	+ Recurrence relation:
 *		f(n) = f(n - 1)		// Using a 2 x 1 tile
 *		    +  f(n - 2)		// Using two 1 x 2 tiles
 *		    +  f(n - 2)		// Using a 2 x 2 tile
 *	  So f(n) = f(n - 1) + 2 * f(n - 2) for n >= 2
 *
 *	+ Since f(n) can be very large (n <= 250), it is convenient to use Java BigInteger
 */

import java.util.Scanner;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.math.BigInteger;

class Main {
	public final static int MAX_SIZE = 250;
	public final static BigInteger TWO = new BigInteger("2");

	public static void main(String [] args)
	{
		BigInteger [] numTileWay = new BigInteger[MAX_SIZE + 1];

		Scanner sc = new Scanner(new BufferedReader(new InputStreamReader(System.in)));
		PrintWriter pr = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));

		precalculateNumTileWay(numTileWay);	

		while(sc.hasNextInt())
		{
			int n = sc.nextInt();
			System.out.println(numTileWay[n]);
		}	

		pr.close();
	}

	public static void precalculateNumTileWay(BigInteger [] numTileWay)
	{
		numTileWay[0] = BigInteger.ONE;
		numTileWay[1] = BigInteger.ONE;

		for(int i = 2; i <= MAX_SIZE; i++)
			numTileWay[i] = numTileWay[i - 1].add(numTileWay[i - 2].multiply(TWO));
	}
}
