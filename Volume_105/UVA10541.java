import java.util.Scanner;
import java.math.BigInteger;

class Main {
	public static final int MAX_LENGTH = 200;
	private static BigInteger[] factorialArr = new BigInteger[MAX_LENGTH + 1];

	public static void main(String[] args)
	{
		precomputeFactorial();

		Scanner sc = new Scanner(System.in);

		int T = sc.nextInt();
		while(T > 0)
		{
			int length = sc.nextInt();
			int numBlack = sc.nextInt();
			int lengthBlack = 0;

			for(int i = 0; i < numBlack; i++)
			{
				int black = sc.nextInt();
				lengthBlack += black;
			}

			int lengthWhite = length - lengthBlack;

			// This is a problem of asking the number of ways
			// to put lengthWhite white boxes between numBlack
			// black regions with the following constraint:
			// 	+ Between two consecutive black regions,
			//	there must be at least 1 white boxes.
			// There are numBlack + 1 spaces to put the white boxes.
			//
			// Answer: combination(N, K) where N = lengthWhite + 1
			//		and K = numBlack
			System.out.println((computeCombination(lengthWhite + 1, numBlack)).toString());

			T--;
		}
	}

	private static void precomputeFactorial()
	{
		factorialArr[0] = BigInteger.ONE;

		for(int ind = 1; ind <= MAX_LENGTH; ind++)
			factorialArr[ind] = factorialArr[ind - 1].multiply(new BigInteger(Integer.toString(ind)));
	}

	private static BigInteger computeCombination(int n, int k)
	{
		if(n == 0)
		{
			if(k == 0)
				return BigInteger.ONE;
			return BigInteger.ZERO;
		}

		if(k > n)
			return BigInteger.ZERO;
		if(k == n)
			return BigInteger.ONE;

		return factorialArr[n].divide(factorialArr[k].multiply(factorialArr[n - k]));
	}
}
