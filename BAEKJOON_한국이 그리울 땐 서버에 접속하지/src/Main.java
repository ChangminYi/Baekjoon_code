import java.util.Scanner;

public class Main {
    public static Scanner scanner = new Scanner(System.in);

    public static boolean isRight(String[] parse, String str) {
        if(parse[0].length() + parse[1].length() > str.length()) {
            return false;
        }


        for(int i = 0; i < parse[0].length(); i++) {
            if(str.charAt(i) != parse[0].charAt(i)) {
                return false;
            }
        }
        for(int i = 0; i < parse[1].length(); i++) {
            if(str.charAt(str.length() - 1 - i) != parse[1].charAt(parse[1].length() - 1 - i)) {
                return false;
            }

        }
        return true;
    }

    public static void main(String[] args) {
        int num = scanner.nextInt();
        String pattern = scanner.next();
        String[] parsed = pattern.split("\\*");
        for(int i = 0; i < num; i++) {
            if (isRight(parsed, scanner.next())) {
                System.out.print("DA\n");
            }
            else {
                System.out.print("NE\n");
            }
        }

        scanner.close();
    }
}
