import java.util.Scanner;
import static java.lang.Math.abs;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int num = scanner.nextInt();
        int[] argi = new int[num];
        for(int i=0; i<num; i++) {
            argi[i] = scanner.nextInt();
        }
        scanner.close();

        for(int i = 0; i < num - 1; i++) {
            for(int j = i + 1; j < num; j++) {
                for(int k = 0; k < num; k++) {
                    if(k == i || k == j) {
                        continue;
                    }
                    else {
                        if(abs(argi[i] - argi[j]) % argi[k] != 0) {
                            System.out.print("no");
                            return;
                        }
                    }
                }
            }
        }

        System.out.print("yes");
    }
}
