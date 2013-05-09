import java.util.Scanner;
import java.math.BigInteger;
import java.io.PrintWriter;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;

public class Main {
	public static void main(String[] args)
	{
		Scanner sc = new Scanner(new BufferedReader
				(new InputStreamReader(System.in)));
		PrintWriter pr = new PrintWriter(new BufferedWriter
				(new OutputStreamWriter(System.out)));
		
		int T = sc.nextInt();
		String dash;
		
		while(T > 0)
		{
			BigInteger numer = new BigInteger(sc.next());
			dash = sc.next();
			BigInteger denom = new BigInteger(sc.next());
			
			BigInteger gcd = numer.gcd(denom);
			numer = numer.divide(gcd);
			denom = denom.divide(gcd);
			
			pr.printf("%s / %s\n", numer.toString(), denom.toString());
			
			T--;
		}
		
		pr.close();
	}
}