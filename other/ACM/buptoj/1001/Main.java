import java.io.*;
import java.util.*;
import java.math.BigInteger;

public class Main {
    static final Scanner in = new Scanner(System.in);
    public static void main(String args[]) {
        String num1 = in.next();
        String num2 = in.next();
        BigInteger n1 = new BigInteger(num1);
        BigInteger n2 = new BigInteger(num2);
        System.out.println(n1.subtract(n2));
    }
}
