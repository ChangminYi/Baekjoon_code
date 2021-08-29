import java.util.Scanner;

public class Main {
    public static Scanner scanner = new Scanner(System.in);

    public static int getCost(int phoneTime, int unitTime, int unitCost) {
        return ((phoneTime / unitTime) + 1) * unitCost;
    }

    public static int getSum(int[] call, int unitTime, int unitCost) {
        int sum = 0;
        for(int i = 0; i < call.length; i++){
            sum += getCost(call[i], unitTime, unitCost);
        }
        return sum;
    }

    public static void main(String[] args) {
        int num = scanner.nextInt();

        int[] calls = new int[num];
        for(int i = 0; i < num; i++) {
            calls[i] = scanner.nextInt();
        }

        int Y = getSum(calls, 30, 10);
        int M = getSum(calls, 60, 15);

        if(Y < M) {
            System.out.print("Y " + Y);
        }
        else if(Y > M) {
            System.out.print("M " + M);
        }
        else{
            System.out.print("Y M " + Y);
        }

        scanner.close();
    }
}
