/*******************************************************************************
 * Author: Nguyen Truong Duy
 ********************************************************************************/

/* Methodology
 *	+ Use Java BigInteger class
 *	+ We can generate a Pascal triangle with L rows in O(L^2) time
 *	  Use the identity: n C k = (n - 1) C k + (n - 1) C (k - 1) for 1 <= k < n
 */

import java.io.PrintWriter;
import java.io.BufferedWriter;
import java.io.OutputStreamWriter;
import java.math.BigInteger;

class Main
{
	public static final int MAX_NUM_DIGIT = 60;
	public static final int MAX_NUM_ROW = 1000;
	public static void main(String[] args)
	{
		PrintWriter writer = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));

		// Print Pascal triangles
		BigInteger pascalRow[] = new BigInteger[MAX_NUM_ROW];
		boolean stopFlag = false;

		// Print the first 2 rows
		writer.println("1");
		writer.println("1 1");
		pascalRow[0] = BigInteger.ONE;
		pascalRow[1] = BigInteger.ONE;
		int rowLen = 2;

		BigInteger result, prevCopy;
		while(!stopFlag)
		{
			// Compute the current row
			prevCopy = pascalRow[0];
			for(int i = 1; i < rowLen; i++)
			{
				result = pascalRow[i].add(prevCopy);
				prevCopy = pascalRow[i];
				pascalRow[i] = result;

				if(i == ((rowLen + 1) >> 1))
				{
					if(result.toString().length() > MAX_NUM_DIGIT)
						stopFlag = true;
				}
			}
			pascalRow[rowLen] = BigInteger.ONE;
			rowLen++;
			
			// Print the current row
			writer.print(pascalRow[0]);
			for(int i = 1; i < rowLen; i++)
			{
				writer.print(" ");
				writer.print(pascalRow[i]);
			}
			writer.println("");
		}
		writer.close();
	}

	
}
