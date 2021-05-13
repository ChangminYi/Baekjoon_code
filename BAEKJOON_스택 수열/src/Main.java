import java.util.Scanner;
import java.util.Stack;
import java.util.Vector;

public class Main {
    public static void main(String[] args) {
        Vector<Character> expr = new Vector<>();
        Stack<Integer> stack = new Stack<>();
        Scanner input = new Scanner(System.in);
        int num = input.nextInt();

        int[] arg = new int[num];
        for(int i = 0; i < num; i++) {
            arg[i] = input.nextInt();
        }
        input.close();

        for(int i = 1, j = 0; i <= num; i++){
            stack.push(i);
            expr.add('+');

            while(!stack.isEmpty() && stack.peek() == arg[j]){
                stack.pop(); j++; expr.add('-');
            }
        }

        if(!stack.isEmpty()) {
            System.out.print("NO");
        }
        else {
            for(char c: expr) {
                System.out.println(c);
            }
        }
    }
}
