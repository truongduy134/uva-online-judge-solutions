/******************************************************
 * Author: Nguyen Truong Duy
 ******************************************************/

/* Methodology:
 *	+ Input is an integer which can be as large as 10^20 ( which does not fit into 64-bit integer).
 *	+ Hence, we will use BigInteger Java built-in class.
 */

import java.util.Scanner;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.math.BigInteger;

class Main {
	public static void main(String[] args)
	{
		Scanner sc = new Scanner(new BufferedReader(new InputStreamReader(System.in)));
		PrintWriter pr = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));

		int numItem, numFriend, caseId;
		BigInteger sum, average, itemPrice;

		caseId = 1;
		while(true)
		{
			numItem = sc.nextInt();
			numFriend = sc.nextInt();
			if(numItem == 0 && numFriend == 0)
				break;

			sum = BigInteger.ZERO;

			for(int i = 0; i < numItem; i++)
			{
				itemPrice = new BigInteger(sc.next());
				sum = sum.add(itemPrice);
			}

			average = sum.divide(BigInteger.valueOf(numFriend));

			pr.printf("Bill #%d costs %s: each friend should pay %s\n\n", caseId, sum.toString(), average.toString());

			caseId++;
		}

		pr.close();
	}
}
