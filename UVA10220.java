import java.util.Scanner;
import java.math.BigInteger;

class Main {
	public static final int MAX_VAL = 1000;
	private static BigInteger[] factorialArr = new BigInteger[MAX_VAL + 1];

	public static void main(String[] args)
	{
		Scanner sc = new Scanner(System.in);
		
		precomputeFactorial();

		while(sc.hasNextInt())
		{
			int n = sc.nextInt();
			System.out.println(computeSumDigitOfFactorial(n));
		}
	}

	private static void precomputeFactorial()
	{
		factorialArr[0] = BigInteger.ONE;
		for(int ind = 1; ind <= MAX_VAL; ind++)
			factorialArr[ind] = factorialArr[ind - 1].multiply(BigInteger.valueOf(ind));
	}

	private static int computeSumDigitOfFactorial(int n)
	{
		String numStr = factorialArr[n].toString();

		int digitSum = 0;
		for(int ind = 0; ind < numStr.length(); ind++)
			digitSum += (numStr.charAt(ind) - '0');

		return digitSum;
	}
}
