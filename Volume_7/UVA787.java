/*******************************************************************************
 * Author: Nguyen Truong Duy
 ********************************************************************************/

/* Methodology:
 *	+ Let f(i) = the maximum product of all subarrays starting at index i.
 *	  Then f(i) can be computed in O(n) time (where n is the size of the array) by
 *		considering the subarrays A[i ... i], A[i ... i + 1], A[i ... i + 2], ...
 *		consecutively.
 *	+ Then the maximum product of all subarrays of A is max(f(i)) for i = 0, ...,
 *	  n - 1.
 *
 *	+ Therefore, we can have a straight-forward O(n^2) solution.
 *
 *	+ Since the answer exceeds 64-bit integers, we should use Java BigInteger class.
 */

import java.util.Scanner;
import java.io.PrintWriter;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.math.BigInteger;
import java.util.ArrayList;

class Main
{
	public static final int STOP_INT = -999999;

	public static void main(String [] args)
	{
		Scanner scan = new Scanner(new BufferedReader(new InputStreamReader(System.in)));
		PrintWriter writer = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));

		ArrayList<BigInteger> arr = new ArrayList<BigInteger>();
		while(scan.hasNextInt())
		{
			arr.clear();
			while(true)
			{
				int num = scan.nextInt();
				if(num == STOP_INT)
					break;
				arr.add(BigInteger.valueOf(num));
			}

			writer.println(getMaximumSubarrayProduct(arr));
		}

		writer.close();
	}

	public static BigInteger getMaximumSubarrayProduct(ArrayList<BigInteger> arr)
	{
		BigInteger maxProduct = arr.get(0);

		for(int left = 0; left < arr.size(); left++)
		{
			BigInteger product = BigInteger.ONE;

			for(int right = left; right < arr.size(); right++)
			{
				product = product.multiply(arr.get(right));
				if(product.compareTo(maxProduct) > 0)
					maxProduct = product;
				if(product.compareTo(BigInteger.ZERO) == 0)
					break;
			}
		}

		return maxProduct;
	}
}
