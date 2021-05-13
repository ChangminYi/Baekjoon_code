import java.util.Scanner;
import java.math.BigDecimal;

public class Main {
    static Scanner scanner = new Scanner(System.in);

    public static BigDecimal gcd(BigDecimal a, BigDecimal b){
        if(a.remainder(b) == BigDecimal.ZERO){
            return b;
        }
        else{
            return gcd(b, a.remainder(b));
        }
    }

    public static void main(String[] args) {
        int N = scanner.nextInt(), temp;
        BigDecimal A = BigDecimal.ONE;
        BigDecimal B = BigDecimal.ONE;
        for(int i = 0; i < N; i++){
            temp = scanner.nextInt();
            A = A.multiply(new BigDecimal(temp));
        }

        int M=scanner.nextInt();
        for(int i = 0; i < M; i++){
            temp= scanner.nextInt();
            B = B.multiply(new BigDecimal((temp)));
        }

        String lo = gcd(A, B).toString();

        if(lo.length() > 9){
            for(int i = lo.length() - 9; i < lo.length(); i++){
                System.out.print(lo.charAt(i));
            }
        }
        else{
            System.out.print(lo);
        }
    }
}
