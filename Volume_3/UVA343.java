/*******************************************************************************
 * Author: Nguyen Truong Duy
 ********************************************************************************/

/* Methodology:
 * + Let S1, S2 be two input strings
 * + The base range is from 2 to 36
 * + Let B1, B2 be the minimum base such that S1, S2 are valid representations.
 + + For each base b1 from B1 to 36, and each base b2 from B2 to 36, calculate the decimal value D1 of S1 corresponding to b1, and
 *      the decimal value D2 of S2 corresponding to b2. If D1 is equal to D2, then (b1, b2) is the answer.
 *
 * + Since there is no specification on the maximum decimal value, it is safer to use Java BigInteger
 */

import java.util.Scanner;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.io.BufferedWriter;
import java.io.OutputStreamWriter;
import java.math.BigInteger;

class Main {
    public static final int MAX_BASE = 36;

    public static void main(String [] args) {
        Scanner scanner = new Scanner(new BufferedReader(new InputStreamReader(System.in)));
        PrintWriter writer = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));

        while (scanner.hasNext()) {
            String strNum1 = scanner.next();
            String strNum2 = scanner.next();

            int minValidBase1 = determineMinValidBase(strNum1);
            int minValidBase2 = determineMinValidBase(strNum2);

            boolean foundSolution = false;
            for (int baseOne = minValidBase1; baseOne <= MAX_BASE && !foundSolution; baseOne++) {
                BigInteger decimal1 = new BigInteger(strNum1, baseOne);

                for (int baseTwo = minValidBase2; baseTwo <= MAX_BASE && !foundSolution; baseTwo++) {
                    BigInteger decimal2 = new BigInteger(strNum2, baseTwo);

                    if (decimal1.equals(decimal2)) {
                        writer.printf("%s (base %d) = %s (base %d)\n", strNum1, baseOne, strNum2, baseTwo);
                        foundSolution = true;
                    }
                }
            }

            if (!foundSolution) {
                writer.printf("%s is not equal to %s in any base 2..36\n", strNum1, strNum2);
            }
        }

        writer.close();
    }

    public static int determineMinValidBase(String strNum) {
        int maxDigitValue = 0;

        for (int i = 0; i < strNum.length(); i++) {
            char digitValue = strNum.charAt(i);
            int value = 0;
            if (Character.isDigit(digitValue)) {
                value = (int)digitValue - (int)'0';
            } else {
                value = (int)digitValue - (int)'A' + 10;
            }

            if (value > maxDigitValue) {
                maxDigitValue = value;
            }
        }

        return Math.max(maxDigitValue + 1, Character.MIN_RADIX);
    }
}