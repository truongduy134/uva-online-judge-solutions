import java.util.Scanner;
import java.math.BigDecimal;

public class Main {
	
	public static void main(String [] args)
	{
		Scanner sc = new Scanner(System.in);
		
		while(sc.hasNext())
		{
			BigDecimal bigNum = new BigDecimal(sc.next());
			int expo = sc.nextInt();
			
			BigDecimal powerNum = bigNum.pow(expo);
			powerNum = powerNum.stripTrailingZeros();
			
			String printStr = powerNum.toPlainString();
			
			if(printStr.indexOf('.') < 0)
				printStr += ".0";
			
			int indFrom;
			for(indFrom = 0; indFrom < printStr.length() && printStr.charAt(indFrom) == '0'; indFrom++)
			{
				// Do nothing
			}
			
			int indTo = printStr.length() - 1;
			while(printStr.charAt(indTo) == '0' && printStr.charAt(indTo - 1) != '.')
				indTo--;
			
			printStr = printStr.substring(indFrom, indTo + 1);
			
			System.out.println(printStr);
		}
	}
}