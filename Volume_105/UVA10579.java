import java.util.Scanner;
import java.math.BigInteger;

class Main {
	public static final int MAX_FIBO_NUM = 5000;
	private static BigInteger[] fiboArr = new BigInteger[MAX_FIBO_NUM + 1];
	
	public static void main(String[] args)
	{
		Scanner inputSc = new Scanner(System.in);
		int ind;

		precomputeFibo();

		while(inputSc.hasNextInt())
		{
			ind = inputSc.nextInt();
			System.out.println(fiboArr[ind].toString());				}
	}

	private static void precomputeFibo()
	{
		fiboArr[0] = BigInteger.ZERO;
		fiboArr[1] = BigInteger.ONE;
		fiboArr[2] = BigInteger.ONE;

		for(int ind = 3; ind <= MAX_FIBO_NUM; ind++)
			fiboArr[ind] = fiboArr[ind - 1].add(fiboArr[ind - 2]);
	}
}
