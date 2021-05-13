import java.util.Scanner;
public class Main {
    public static void main(String[] args) {
        int num = 0;
        Scanner input = new Scanner(System.in);
        num = input.nextInt();
        int apple = 0;
        for(int i = 0; i < num; i++){
            int temp[] = new int[2];
            for(int j = 0; j < 2; j++){
                temp[j] = input.nextInt();
            }
            apple += temp[1] % temp[0];
        }
        System.out.println(apple);
        input.close();
    }
}
