import java.util.Scanner;
import java.math.BigDecimal;
 
class Main {
    public static void main(String[] args)
    {
        int T;
        Scanner sc = new Scanner(System.in);
        String result;
        T = sc.nextInt();
        
        while(T > 0)
        {
            BigDecimal one = new BigDecimal(sc.next());
            BigDecimal two = new BigDecimal(sc.next());
            
            BigDecimal three = one.add(two);
            three = three.stripTrailingZeros();
            
            result = three.toPlainString();
                if(result.indexOf('.') == -1)
                                result += ".0";
                        
            boolean allZero = true;
            for(int i = 0; i < result.length(); i++)
                if(result.charAt(i) != '0' && result.charAt(i) != '.')
                {
                    allZero = false;
                    break;
                }
            if(allZero)
                result = "0.0";
                
            System.out.println(result);
            
            T--;
        }
    }
}