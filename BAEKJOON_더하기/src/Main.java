import java.util.Scanner;
public class Main {
    public static boolean isNum(char c){
        if('0' <= c && c <= '9') { return true; }
        return false;
    }

    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        String s = input.nextLine();
        int sum = 0;
        input.close();

        for(int i = 0; i < s.length(); i++){
            if(isNum(s.charAt(i))) {
                String newString = "";
                int skip = i;
                while(skip < s.length() && isNum(s.charAt(skip))){
                    newString += s.charAt(skip);
                    skip++;
                }
                sum += Integer.parseInt(newString);
                i = skip;
            }
        }

        System.out.println((sum));
    }
}
