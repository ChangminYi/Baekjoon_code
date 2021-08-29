import java.math.BigDecimal;
import java.util.Scanner;

public class Main {
    public static Scanner scanner = new Scanner(System.in);

    public static void main(String[] args) {
        int n = scanner.nextInt(), m = scanner.nextInt();
        scanner.close();
        if(n / 2 < m){
            m = n - m;
        }

        if (m == 0){
            System.out.print("1");
        }
        else {
            BigDecimal res = new BigDecimal("1");
            for (int i = 1; i <= m; i++) {
                res = res.multiply(new BigDecimal(Integer.toString(n + 1- i)));
                res = res.divide(new BigDecimal(Integer.toString(i)));
            }
            System.out.print(res);
        }
    }
}
