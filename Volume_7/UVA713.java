import java.util.Scanner;
import java.math.BigInteger;
import java.io.PrintWriter;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.BufferedWriter;
import java.io.OutputStreamWriter;

public class Main
{
	public static void main(String [] args)
	{
		Scanner sc = new Scanner(new BufferedReader(new InputStreamReader(System.in)));
		PrintWriter pr = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));

		int T = sc.nextInt();

		while(T > 0)
		{
			BigInteger A = new BigInteger(sc.next());
			A = reverseBigInt(A);
			BigInteger B = new BigInteger(sc.next());
			B = reverseBigInt(B);

			BigInteger C = reverseBigInt(A.add(B));
			pr.println(C.toString());
			T--;
		}

		pr.close();
	}

	public static BigInteger reverseBigInt(BigInteger A)
	{
		return new BigInteger(new StringBuilder(A.toString()).reverse().toString());
	}
}
