import java.util.Scanner;
import java.math.BigInteger;
import java.io.PrintWriter;
import java.io.InputStreamReader;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.OutputStreamWriter;

class Main {

	public static void main(String [] args)
	{
		Scanner sc = new Scanner(new BufferedReader(new InputStreamReader(System.in)));
		PrintWriter pr = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));

		while(true)
		{
			int base = sc.nextInt();
			if(base == 0)
				break;

			BigInteger divided = new BigInteger(sc.next(), base);
			BigInteger divider = new BigInteger(sc.next(), base);

			pr.println(divided.mod(divider).toString(base));
		}

		pr.close();
	}
}
