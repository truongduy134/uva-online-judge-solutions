import java.util.Scanner;
import java.math.BigInteger;
 
class Main {
    public static void main(String[] args)
    {
        Scanner sc = new Scanner(System.in);
        
        String strOp;
        
        while(sc.hasNext())
        {
            BigInteger numOne = new BigInteger(sc.next());
            strOp = sc.next();
            BigInteger numTwo = new BigInteger(sc.next());
            
            if(strOp.charAt(0) == '/')
                System.out.println(numOne.divide(numTwo).toString());
            else
                System.out.println(numOne.mod(numTwo).toString());
        }
    }
}