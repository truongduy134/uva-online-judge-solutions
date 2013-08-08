import java.util.Scanner;
import java.math.BigInteger;
 
class Main {
    
    // Formula: a + 2 * a^2 + ... + n * a^n = (n * a^(n + 2) - (n + 1) * a^(n + 1) + a) / (a - 1)^2
    public static void main(String[] args)
    {
        Scanner sc = new Scanner(System.in);
        int a, n;
        
        while(sc.hasNextInt())
        {
            n = sc.nextInt();
            a = sc.nextInt();
            
			if(a <= 1)
			{
				if(a == 0)
					System.out.println(0);
				else
					System.out.println((n * (n + 1)) >> 1);
			}
			else
			{
				BigInteger powNPlusOne = BigInteger.valueOf(a).pow(n + 1);
				BigInteger powNPlusTwo = powNPlusOne.multiply(BigInteger.valueOf(a));
            
				BigInteger result = powNPlusTwo.multiply(BigInteger.valueOf(n)).subtract(
					powNPlusOne.multiply(BigInteger.valueOf(n + 1))).add(BigInteger.valueOf(a)).divide(
						BigInteger.valueOf((a - 1) * (a - 1)));
                    
				System.out.println(result.toString());
			}
        }
    }
}