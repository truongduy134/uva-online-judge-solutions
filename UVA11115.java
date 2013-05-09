import java.util.Scanner;
import java.io.PrintWriter;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.math.BigInteger;

class Main {
	// Problem: Distribute distinct CDs to distinct person.
	// There are N nephews and D CDs.
	// For each cds, there are N ways to distribute it. Therefore, the total
	//	number of different ways of distribution is N^D
	public static void main(String [] args)
	{
		Scanner sc = new Scanner(new BufferedReader(new InputStreamReader(System.in)));
		PrintWriter pr = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));

		while(true)
		{
			int numNephew = sc.nextInt();
			int numCD = sc.nextInt();
			
			if(numNephew == 0 && numCD == 0)
				break;

			pr.println(BigInteger.valueOf(numNephew).pow(numCD));
		}
		
		pr.close();
	}
}
