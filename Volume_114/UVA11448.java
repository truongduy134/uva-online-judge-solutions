import java.util.Scanner;
import java.math.BigInteger;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;

class Main {
	public static void main(String [] args)
	{
		Scanner sc = new Scanner(new BufferedReader(new InputStreamReader(System.in)));
		PrintWriter pr = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));

		int T = sc.nextInt();
		while(T > 0)
		{
			BigInteger benefit = new BigInteger(sc.next());
			BigInteger cost = new BigInteger(sc.next());

			// balance = benefit - cost
			pr.println(benefit.subtract(cost));

			T--;
		}

		pr.close();
	}
}
