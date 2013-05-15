/*************************************************************************
 * Author: Nguyen Truong Duy
 *************************************************************************/

import java.util.Scanner;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.math.BigInteger;

class Main {
	final static BigInteger startYear = new BigInteger("2148");

	public static void main(String[] args)
	{
		Scanner sc = new Scanner(new BufferedReader(new InputStreamReader(System.in)));
		PrintWriter pr = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));

		String numStr;
		BigInteger year, distYear;
		boolean isFirst = true, atLeastOne = false;
		while(true)
		{
			atLeastOne = false;
			numStr = sc.next();

			if(numStr.length() == 1 && numStr.charAt(0) == '0')
				break;

			if(isFirst)
				isFirst = false;
			else
				pr.println("");
			pr.println(numStr);

			year = new BigInteger(numStr);
			if(year.compareTo(startYear) < 0)
			{
				pr.println("No ghost will come in this year");
				continue;
			}
	
			distYear = year.subtract(startYear);
						
			if(distYear.mod(BigInteger.valueOf(2)) == BigInteger.ZERO)
			{
				pr.println("Ghost of Tanveer Ahsan!!!");
				atLeastOne = true;
			}

			if(distYear.mod(BigInteger.valueOf(5)) == BigInteger.ZERO)
			{
				pr.println("Ghost of Shahriar Manzoor!!!");
				atLeastOne = true;
			}

			if(distYear.mod(BigInteger.valueOf(7)) == BigInteger.ZERO)
			{
				pr.println("Ghost of Adrian Kugel!!!");
				atLeastOne = true;
			}
			if(distYear.mod(BigInteger.valueOf(11)) == BigInteger.ZERO)
			{
				pr.println("Ghost of Anton Maydell!!!");
				atLeastOne = true;
			}
			if(distYear.mod(BigInteger.valueOf(15)) == BigInteger.ZERO)
			{
				pr.println("Ghost of Derek Kisman!!!");
				atLeastOne = true;
			}
			if(distYear.mod(BigInteger.valueOf(20)) == BigInteger.ZERO)
			{
				pr.println("Ghost of Rezaul Alam Chowdhury!!!");
				atLeastOne = true;
			}
			if(distYear.mod(BigInteger.valueOf(28)) == BigInteger.ZERO)
			{
				pr.println("Ghost of Jimmy Mardell!!!");
				atLeastOne = true;
			}
			if(distYear.mod(BigInteger.valueOf(36)) == BigInteger.ZERO)
			{
				pr.println("Ghost of Monirul Hasan!!!");
				atLeastOne = true;
			}
			if(isLeapYear(year))
			{
				pr.println("Ghost of K. M. Iftekhar!!!");
				atLeastOne = true;
			}

			if(atLeastOne == false)
				pr.println("No ghost will come in this year");
		}
		pr.close();	
	}

	public static boolean isLeapYear(BigInteger bigInt)
	{
		if(bigInt.mod(BigInteger.valueOf(400)) == BigInteger.ZERO)
			return true;
		if(bigInt.mod(BigInteger.valueOf(100)) == BigInteger.ZERO)
			return false;
		if(bigInt.mod(BigInteger.valueOf(4)) == BigInteger.ZERO)
			return true;
		return false;
	}
}
