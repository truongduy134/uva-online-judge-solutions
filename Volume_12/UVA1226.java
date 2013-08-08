/*******************************************************************************
 * Author: Nguyen Truong Duy
 ********************************************************************************/

/* Methodology:
 *	+ This is a simple problem if we use Java BigInteger class.
 */

import java.util.Scanner;
import java.math.BigInteger;
import java.io.PrintWriter;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.BufferedReader;
import java.io.BufferedWriter;

class Main {
	public static void main(String [] args)
	{
		Scanner scan = new Scanner(new BufferedReader(new InputStreamReader(System.in)));
		PrintWriter writer = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));

		int T = scan.nextInt();
		while(T > 0)
		{
			BigInteger divider = new BigInteger(scan.next());
			BigInteger divided = new BigInteger(scan.next());
			writer.println(divided.mod(divider));

			T--;
		}

		writer.close();		
	}
}
