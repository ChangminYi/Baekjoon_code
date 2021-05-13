import java.util.Scanner;
import java.lang.String;

public class Main {
    public static String stringReverse(String str, int index) {
        char[] temp = new char[index + 1];
        for(int i = 0; i <= index; i++) {
            temp[index - i] = str.charAt(i);
        }
        String reversed = new String(temp);
        return reversed;
    }

    public static boolean isDecal(String str, int index) {
        String reverse = stringReverse(str, index);
        int shorter = reverse.length() < str.length() ? reverse.length() : str.length();
        for(int i = shorter - 1; i > -1; i--) {
            if(str.charAt(i) != reverse.charAt(i)){
                return false;
            }
        }
        return true;
    }

    public static int getShortest(String str) {
        int minLength = 0x7FFFFFF;
        for(int i = 0; i < str.length() - 1; i++) {
            if(isDecal(str, i)) {
                int tempLength = (i + 1 > str.length() - i? i + 1: str.length() - i) * 2;
                if(str.charAt(i + 1) == str.charAt(0)){
                    tempLength--;
                }
                if(minLength > tempLength) {
                    minLength = tempLength;
                }
            }
        }

        return minLength;
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        String str = scanner.nextLine();
        scanner.close();
        System.out.print(getShortest(str));
    }
}
