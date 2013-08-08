import java.util.Scanner;
import java.math.BigInteger;

class Main {
	public static final int MAX_IND_VALUE = 1000;
	private static BigInteger[] factorialArr = new BigInteger[MAX_IND_VALUE + 1];

	public static void main(String[] args)
	{
		Scanner inputSc = new Scanner(System.in);
		int ind;

		precomputeFactorial();

		while(inputSc.hasNextInt())
		{
			ind = inputSc.nextInt();
			System.out.println(Integer.toString(ind) + "!");
			System.out.println(factorialArr[ind].toString());
		}
	}

	private static void precomputeFactorial()
	{
		factorialArr[0] = BigInteger.ONE;
		
		for(int ind = 1; ind <= MAX_IND_VALUE; ind++)
		{
			factorialArr[ind] = factorialArr[ind - 1].multiply(new BigInteger(Integer.toString(ind)));
		}
	}
}
