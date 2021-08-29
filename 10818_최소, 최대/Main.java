import java.util.Scanner;

public class Main {
    public static Scanner scanner = new Scanner(System.in);

    public static void main(String[] args) {
        int N = scanner.nextInt();
        int min = 1000000, max = -1000000;
        for(int i = 0, temp; i < N; i++) {
            temp = scanner.nextInt();
            if(temp < min) {
                min = temp;
            }
            if(temp > max) {
                max = temp;
            }
        }

        System.out.printf("%d %d", min, max);
        scanner.close();
    }
}
